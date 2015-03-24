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

 namespace oreo{

 	class OreoLock{
 		public:
 			OreoLock();
 			~OreoLock(){
 				pthread_mutex_destroy(&_mutex);
 			}
 			void lock();
 			void unlock();
 		private:
 			bool locked;
 			pthread_mutex_t _mutex;
 	};

 	class OreoMutexLock{
 		public:
 			OreoMutexLock();
 			~OreoMutexLock();

 		private:
 			OreoLock _lock;
 	};

 	class OreoCondtionLock{

 	};
 }

 #endif


