/*
 
 * ============================================================
 
 *       Filename:  tcp_server.cpp
 *    Description:  
 *         Author:  liuyoubin@baidu.com
 *        Company:  Baidu.com, Inc
 *        Created:  2015-03-24 14:53:08
 
 * ============================================================
 
 */

#include "oreo_tcp_server.h"
namespace oreo{

void OreoTcpServer::setSocketNonblock(int socket_fd){
	int flags = fcntl(socket_fd, F_GETFL, 0);

	if (flags < 0){
		perror("fcntl get flags failed");
		exit(EXIT_FAILURE);
	}

	if (fcntl(socket_fd, F_SETFL, flags| O_NONBLOCK) < 0){
		perror("fcntl set flags failed");
		exit(EXIT_FAILURE);
	}
}

void OreoTcpServer::createSocket(int port, int backlog,int &socket_fd){
	if ( (socket_fd = socket(PF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket create failed");
		exit(-1);
	} 

	int yes = 1;
	if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes))){
		perror("setsocketopt failed");
		exit(-1);
	}

	setSocketNonblock(socket_fd);
	struct sockaddr_in bind_addr;
	memset(&bind_addr, 0, sizeof(bind_addr));

	bind_addr.sin_family = AF_INET;
	bind_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind_addr.sin_port = htons(port);

	if ((bind(socket_fd, (struct sockaddr *) &bind_addr, sizeof(bind_addr)) == -1)){
		perror("bind socket failed");
		exit(-1);
	}

	if (listen(socket_fd, backlog) == -1){
		perror("listen socket failed");
		exit(-1);
	}
}

void OreoTcpServer::connectionCallback(void *){
	printf("get connection\n");
}

int OreoTcpServer::init(){
	_backlog = 1024;
	_loop_timeintval = 100;
	_net_queue_size = 10240;
	_net_work_threads_size = 10;
	_server_status = SERVER_INIT;
	_max_event_size = 10240;
	
	signal(SIGPIPE, SIG_IGN);

	_lock = new OreoLock();
	_cond = new OreoCondLock(_lock);

	_net_queue = new OreoEventQueue(_net_queue_size);

	createSocket(_port,_backlog,_server_fd);

	_server_event = new OreoEvent(_server_fd);
	_server_event->careRead();

	_server_epoll = new OreoEpoll(_max_event_size);
	_server_epoll->init();
	_server_epoll->addEvent(_server_event);

	for(int i = 0; i <= _net_work_threads_size; ++i){
		pthread_t p;
		_threads.push_back(p);
	}
	return 0;
}
void * netWorkLoop(void *serv){
	OreoTcpServer *_serv = (OreoTcpServer *) serv;
	OreoEventQueue *_queue = _serv->getNetQueue();
	pid_t tid = static_cast<pid_t>(::syscall(SYS_gettid));

	while(_serv->getServerStatus() == SERVER_RUNNING){

		if(_queue->count() > 0){
			OreoEvent *oe = _queue->pop();
			if(oe != NULL){
				int conn_sock_fd = oe->getEventFd();
				char req[1024];
				char res[1024];
				memset(req, 0, sizeof(req));
				memset(res, 0, sizeof(res));
				int recv_size = 0;
				if ((recv_size = recv(conn_sock_fd, req, sizeof(req), 0)) < 0){
					perror("recv failed");
					continue;
				}

				

				callback cbfunc = oe->getCallback();
				cbfunc(req, res);
				//printf("tid:%d,recv %d, req:%s, res:%s\n", tid, conn_sock_fd, req, res);
				if (send(conn_sock_fd, res, strlen(res), 0) == -1 && (errno != EAGAIN) && (errno != EWOULDBLOCK) ){
					perror("send failed");
					continue;
				}

				delete oe;
				close(conn_sock_fd);
			}
		}else{
			_serv->getCondLock()->wait();
		}
	}
	return NULL;
}

void * mainLoop(void *serv){
	OreoTcpServer *_serv = (OreoTcpServer *) serv;
	OreoEventQueue *_queue = _serv->getNetQueue();
	pid_t tid = static_cast<pid_t>(::syscall(SYS_gettid));
	std::vector<OreoEvent *> events;

	while(_serv->getServerStatus() == SERVER_RUNNING){

		_serv->getPoll()->loop(_serv->_loop_timeintval, events);

		if(!events.empty()){

			for(size_t i = 0; i < events.size(); ++i){

				OreoEvent * oe = events[i];

				if(oe->getEventType() == NET_EVENT){
					printf("put one event\n");
					oe->registerReadCallback(_serv->_cb);
					_queue->put(oe);
					
					_serv->getCondLock()->notify();

				}
			}

			events.clear();
		}
	}	

	return NULL;
}

int OreoTcpServer::run(){
	_server_status = SERVER_RUNNING;

	for(int i = 0; i < _net_work_threads_size; ++i){
		pthread_create(&_threads[i], NULL, &netWorkLoop,this);
	}

	pthread_create(&_threads[_net_work_threads_size], NULL, &mainLoop,this);
	
	return 0;
}

int OreoTcpServer::join(){
	for(int i = 0; i < _net_work_threads_size; ++i){
        void *retval;
	    int ret_thrd = pthread_join(_threads[i], &retval);
	    if(ret_thrd != 0){
		    printf("join thread %d failed",i+1);
		    return -1;
	    }
    }
    return 0;
}

}
