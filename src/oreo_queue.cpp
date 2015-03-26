/*
 
 * ============================================================
 
 *       Filename:  blocking_queue.cpp
 *    Description:  
 *         Author:  liuyoubin@baidu.com
 *        Company:  Baidu.com, Inc
 *        Created:  2015-03-24 14:51:56
 
 * ============================================================
 
 */

#include "oreo_queue.h"

namespace oreo{

void OreoEventQueue::put(OreoEvent * event){
	OreoMutexLock mutexlock(&_lock);
	_queue.push_back(event);
}

OreoEvent* OreoEventQueue::pop(){
	OreoMutexLock mutexlock(&_lock);
	if(_queue.size() == 0){
		return NULL;
	}
	OreoEvent *event = _queue.front();
	_queue.pop_front();
	return event;
}

uint32_t OreoEventQueue::count(){
	OreoMutexLock mutexlock(&_lock);
	return _queue.size();
}

}
