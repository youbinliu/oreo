/*
 
 * ============================================================
 
 *       Filename:  tcp_server.h
 *    Description:  
 *         Author:  liuyoubin@baidu.com
 *        Company:  Baidu.com, Inc
 *        Created:  2015-03-24 14:53:03
 
 * ============================================================
 
 */

#ifndef __OREO_TCP_SERVER_H_
#define __OREO_TCP_SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
 
#include "oreo_lock.h"
#include "oreo_queue.h"
#include "oreo_event.h"
#include "oreo_epoll.h"

namespace oreo{
	enum OreoTcpServerStatus {  
		SERVER_INIT,
		SERVER_RUNNING,
		SERVER_STOP
	};

	class OreoTcpServer{
		public:
			OreoTcpServer(int port):_port(port){}
			int init();
			int run();
			int join();

			void registerReadCallback(callback cb){
				_cb = cb;
			}

			int getServerStatus(){
				return _server_status;
			}

			OreoEventQueue * getNetQueue(){
				return _net_queue;
			}

			OreoEpoll *getPoll(){
				return _server_epoll;
			}

			OreoCondLock * getCondLock(){
				return _cond;
			}


		private:
			void setSocketNonblock(int socket_fd);
			void createSocket(int port,int backlog, int &socket_fd);
			void connectionCallback(void *data);
			

		public:
			int _loop_timeintval;
			int _port;
			int _backlog;
			int _server_status;
			int _server_fd;
			int _net_queue_size;
			int _net_work_threads_size;
			int _max_event_size;
			std::vector<pthread_t> _threads;
			OreoLock *_lock;
			OreoCondLock *_cond;
			callback _cb;
		private:
			
			OreoEpoll *_server_epoll;
			OreoEventQueue *_net_queue;
			OreoEvent *_server_event;

	};
}

#endif

