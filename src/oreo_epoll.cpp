/*
 
 * ============================================================
 
 *       Filename:  epoll.cpp
 *    Description:  
 *         Author:  liuyoubin@baidu.com
 *        Company:  Baidu.com, Inc
 *        Created:  2015-03-24 14:49:11
 
 * ============================================================
 
 */

#include "oreo_epoll.h"

namespace oreo{

int OreoEpoll::init(){
	_epoll_fd = epoll_create(_events_size);
	if (_epoll_fd < 0){
		perror("epoll create failed\n");
		exit(-1);
	}

	for(int i = 0; i < _events_size ; ++i){
		struct epoll_event ee;
		_epoll_events.push_back(ee);
	}

	return 0;
}

int OreoEpoll::addEvent(OreoEvent *o_event){
	struct epoll_event event;
	event.events = o_event->getCareEventType();
	event.data.fd = o_event->getEventFd();
	event.data.ptr = (void *)o_event;
	if (epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, o_event->getEventFd(), &event) == -1){
		perror("epoll_ctl add failed");
		exit(-1);
	}
	return 0;
}
int OreoEpoll::deleteEvent(int o_event_fd){

	if (epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, o_event_fd, NULL) == -1){
		perror("epoll_ctl del failed");
		exit(-1);
	}

	return 0;

}
int OreoEpoll::loop(int timeintval, std::vector<OreoEvent*> &ready_events){
	
	int event_num = epoll_wait(_epoll_fd, &(_epoll_events[0]), _events_size, timeintval);

	if (event_num < 0){
		printf("epoll_wait failed,event_num:%d\n", event_num);
		return -1;
	}

	for (int i = 0; i < event_num; ++i){
		if ((_epoll_events[i].events & EPOLLERR) || (_epoll_events[i].events & EPOLLHUP) || !(_epoll_events[i].events & EPOLLIN)){
			printf("find other event which is not EPOLLIN\n");
			continue;
		}

		OreoEvent *event = (OreoEvent*) _epoll_events[i].data.ptr;

		if (event->getEventType() == MAIN_EVENT){

			struct sockaddr_in client_addr;
			socklen_t client_addr_len = sizeof(client_addr);
			char client_ip_str[128];
			int conn_sock = accept(event->getEventFd(), (struct sockaddr *) &client_addr, &client_addr_len);
			if (conn_sock < 0){
				if (errno == EAGAIN || errno == EWOULDBLOCK){
					printf("accept failed errno:%d\n", errno);
					continue;
				}else{
					perror("accept failed");
					continue;
				}
			}

			if (!inet_ntop(AF_INET, &(client_addr.sin_addr), client_ip_str, sizeof(client_ip_str))){
				perror("inet_ntop failed");
			}

			int flags = fcntl(conn_sock, F_GETFL, 0);

			fcntl(conn_sock, F_SETFL, flags| O_NONBLOCK);

			OreoEvent *oe = new OreoEvent(conn_sock);
			oe->setEventType(NET_EVENT);
			oe->careRead();
			addEvent(oe);

		}else if (event->getEventType() == NET_EVENT){

			event->setCurrentEvent(_epoll_events[i].events);
			ready_events.push_back(event);
			//deleteEvent(_epoll_events[i].data.fd);

		}else if (event->getEventType() == CPU_EVENT){

		}else{

		}

	}

	return 0;
}

}
