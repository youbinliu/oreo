/*
 
 * ============================================================
 
 *       Filename:  blocking_queue.h
 *    Description:  
 *         Author:  liuyoubin@baidu.com
 *        Company:  Baidu.com, Inc
 *        Created:  2015-03-24 14:51:50
 
 * ============================================================
 
 */

#ifndef __OREO_QUEUE_H_
#define __OREO_QUEUE_H_

#include <deque>
#include "oreo_lock.h"
#include "oreo_event.h"

namespace oreo{

	class OreoEventQueue{
		public:
			OreoEventQueue(uint32_t size):_put_count(0),_queue(size){}
			~OreoEventQueue(){}
			OreoEvent * pop();
			void put(OreoEvent *event);
			uint32_t count();

		private:
			uint64_t _put_count;
			OreoLock _lock; 
			std::deque<OreoEvent *> _queue;
	};
}

#endif

