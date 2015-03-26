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

namespace oreo{

OreoLock::OreoLock():_locked(false){
	pthread_mutex_init(&_mutex, NULL);
}

OreoLock::~OreoLock(){
	pthread_mutex_destroy(&_mutex);
}

void OreoLock::lock(){
	_locked = true;
	pthread_mutex_lock(&_mutex);
}

void OreoLock::unlock(){
	_locked = false;
	pthread_mutex_unlock(&_mutex);
}

bool OreoLock::islocked(){
	return _locked;
}

OreoMutexLock::OreoMutexLock(OreoLock *lock):_lock(lock){
	_lock->lock();
}

OreoMutexLock::~OreoMutexLock(){
	_lock->unlock();
}

OreoCondLock::OreoCondLock(OreoLock *lock):_lock(lock){
	pthread_cond_init(&_cond,NULL);
}

OreoCondLock::~OreoCondLock(){
	pthread_cond_destroy(&_cond);
}

void OreoCondLock::wait(){
	OreoMutexLock mutexLock(_lock);
	pthread_cond_wait(&_cond, _lock->mutex());	
}

void OreoCondLock::notify(){
	pthread_cond_signal(&_cond);
}

void OreoCondLock::notifyAll(){
	pthread_cond_broadcast(&_cond);
}

}
