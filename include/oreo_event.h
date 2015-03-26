/*
 
 * ============================================================
 
 *       Filename:  oreo_event.h
 *    Description:  
 *         Author:  liuyoubin@baidu.com
 *        Company:  Baidu.com, Inc
 *        Created:  2015-03-24 15:50:59
 
 * ============================================================
 
 */

#ifndef __OREO_EVENT_H_
#define __OREO_EVENT_H_

#include <stdio.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <errno.h>
 
namespace oreo{
	typedef void (*callback)(void *);
	enum OreoEventType {  
		MAIN_EVENT,
		NET_EVENT,
		CPU_EVENT,
	};
	class OreoEvent{
		
		public:
			OreoEvent(int event_fd):_care_event_type(0),_current_event_type(0),_event_fd(event_fd),_cb(NULL),_event_data(NULL){};
			~OreoEvent(){};
			int registerReadCallback(callback cb);
			void careRead();
			int careEventType();
			bool isReadEvent();
			void fireCallback();

			int getEventType(){
				return _event_type;
			}

			void setEventType(int event_type){
				_event_type = event_type;
			}

			int getEventFd(){
				return _event_fd;
			}

			void setCurrentEvent(int re){
				_current_event_type = re;
			}

			int getCareEventType(){
				return _care_event_type;
			}

		private:
			int _event_type;
			int _care_event_type;
			int _current_event_type;
			int _event_fd;
			callback _cb;
			void * _event_data;
			
	};

}

#endif
