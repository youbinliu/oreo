/*
 
 * ============================================================
 
 *       Filename:  mutex_lock.cpp
 *    Description:  
 *         Author:  liuyoubin@baidu.com
 *        Company:  Baidu.com, Inc
 *        Created:  2015-03-24 14:54:11
 
 * ============================================================
 
 */
#include <pthread.h>
#include "oreo_lock.h"

OreoLock::OreoLock():_locked(false){
	pthread_mutex_init(&_mutex, NULL);
}

OreoLock::~OreoLock(){
	pthead_mutex_destroy(&_mutex);
}

OreoLock::lock(){
	_locked = true;
	pthread_mutex_lock(&_mutex);
}

OreoLock::unlock(){
	_locked = false;
	pthread_mutex_unlock(&_mutex);
}

OreoLock::islocked(){
	return _locked;
}

OreoMutexLock::OreoMutexLock(OreoLock *lock):_lock(lock){
	_lock.lock();
}

OreoMutexLock::~OreoMutexLock(){
	_lock.unlock();
}

OreoCondLock::OreoCondLock(OreoLock *lock):_lock(lock){
	pthread_cond_init(&_cond);
}

OreoCondLock::~OreoCondLock(){
	pthread_cond_destroy(&_cond);
}

OreoCondLock::wait(){
	OreoMutexLock(_lock);
	pthread_cond_wait(&_cond, _lock->mutex());	
}

OreoCondLock::notify(){
	pthread_cond_signal(&_cond);
}

OreoCondLock::notifyAll(){
	pthread_cond_broadcast(&_cond);
}

