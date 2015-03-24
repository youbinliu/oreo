/*
 
 * ============================================================
 
 *       Filename:  oreo_lock.h
 *    Description:  
 *         Author:  liuyoubin@baidu.com
 *        Company:  Baidu.com, Inc
 *        Created:  2015-03-24 14:54:06
 
 * ============================================================
 
 */

#ifndef __OREO_LOCK_H_
#define __OREO_LOCK_H_

#include <pthread.h>

namespace oreo{

	class OreoLock{
		public:
			OreoLock();
			~OreoLock();
			void lock();
			void unlock();
			bool islocked();
			pthread_mutex_t * mutex(){
				return &_mutex;
			}
		private:
			bool _locked;
			pthread_mutex_t _mutex;
	};

	class OreoMutexLock{
		public:
			OreoMutexLock(OreoLock *lock);
			~OreoMutexLock();

		private:
			OreoLock *_lock;
	};

	class OreoCondLock{
		public:
			OreoCondLock(OreoLock *lock);
			~OreoCondLock();
			void wait();
			void notify();
			void notifyAll();

		private:
			OreoLock *_lock; 
			pthread_cond_t _cond;

	};
}

#endif


