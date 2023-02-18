#ifndef THREAD_H
#define THREAD_H

#include<stdio.h>
#include<stdlib.h>
#include<ucontext.h>
#include<signal.h>
#include<sys/time.h>
#include<unistd.h>

/*! 
	Initialises threadlist pointer to a dynamically allocated Linked List.
*/
void mythread_init();

/*! 
    @brief Creates a new thread.
	@param func : The function to be linked to the newly created thread.
	@param arg : The argument to be given when calling "func".
	@return Returns the pointer to the context created. 

	Creates a new thread with the function func and adds it to the existing threadlist.
*/
void* mythread_create(void func(void*), void* arg);

/*! 
    Waits for other threads to complete. Used in case of dependent threads. 
*/
void mythread_join();

/*! 
    Performs context switching. Used while yielding from one context to another without completing the current context.
*/
void mythread_yield();

/*! 
	@brief Lock object.
*/
struct lock {
	void* c; ///< Contains the thread which has acquired the lock
};

/*! 
	@return Returns a pointer to a dynamically allocated lock object.
*/
struct lock* lock_new();

/*! 
	Sets lock for a key, and yields if the key is already locked.
*/
void lock_acquire(struct lock* lk);

/*! 
	Releases lock for a key.
*/
int lock_release(struct lock* lk);

#endif
