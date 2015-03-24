/*
 
 * ============================================================
 
 *       Filename:  mutex_lock.cpp
 *    Description:  
 *         Author:  liuyoubin@baidu.com
 *        Company:  Baidu.com, Inc
 *        Created:  2015-03-24 14:54:11
 
 * ============================================================
 
 */

#include "oreo_lock.h"

OreoLock::OreoLock():locked(false){
	pthread_mutex_init(&_mutex, NULL);
}

OreoLock::~OreoLock(){
	pthead_mutex_destroy(&_mutex);
}

OreoLock::lock(){
	locked = true;
	pthread_mutex_lock(&_mutex);
}

OreoLock::unlock(){
	locked = false;
	pthread_mutex_unlock(&_mutex);
}

OreoMutexLock::OreoMutexLock(){
	_lock.lock();
}

OreoMutexLock::~OreoMutexLock(){
	_lock.unlock();
}