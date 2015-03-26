/*
 
 * ============================================================
 
 *       Filename:  oreo_epoll.h
 *    Description:  
 *         Author:  liuyoubin@baidu.com
 *        Company:  Baidu.com, Inc
 *        Created:  2015-03-24 16:02:59
 
 * ============================================================
 
 */

#ifndef __OREO_EPOLL_H_
#define __OREO_EPOLL_H_

#include <sys/epoll.h>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "oreo_event.h"
#include <errno.h>
#include <fcntl.h>

namespace oreo{
	
	class OreoEpoll{
		public:
			OreoEpoll(int max_event_size):_events_size(max_event_size){}
			~OreoEpoll(){}
			int init();
	 		int addEvent(OreoEvent *o_event);
	 		int deleteEvent(int o_event_fd);
	 		int loop(int loop_intval, std::vector<OreoEvent *> &ready_events);


	 	private:
	 		int _events_size;
	 		int _epoll_fd;
	 		std::vector<epoll_event> _epoll_events;
	};
}

#endif
