/*
 
 * ============================================================
 
 *       Filename:  event.cpp
 *    Description:  
 *         Author:  liuyoubin@baidu.com
 *        Company:  Baidu.com, Inc
 *        Created:  2015-03-24 15:51:41
 
 * ============================================================
 
 */

#include "oreo_event.h"

namespace oreo{

int OreoEvent::registerReadCallback(callback cb){
	_cb = cb;
	return 0;
}
void OreoEvent::careRead(){
	_care_event_type = _care_event_type | EPOLLIN | EPOLLET;
}
bool OreoEvent::isReadEvent(){
	return _current_event_type & EPOLLIN;
}
void OreoEvent::fireCallback(){
	_cb(_event_data);
}
}
