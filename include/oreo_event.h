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

namespace oreo{

	class OreoEvent{

		public:
			int registerConnectionCallback();
			int registerReadCallback();
			void careRead();
			void careConnection();
			bool isReadEvent();
			bool isCPUEvent();
			bool isNETEvent();

		private:
			int _care_event_type;
			int _current_event_type;
			int _event_fd;
			void * _event_data;
			int _event_type;
	};

}

#endif