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

 #include "oreo_event.h"

 namespace oreo{
 	
 	class OreoEpoll{
 		public:
 			int init();
	 		int add(OreoEvent *o_event);
	 		int delete(int o_event_fd);
	 		int loop();

	 	private:
	 		int _events_size;
	 		int _epoll_fd;

 	};
 }

 #endif