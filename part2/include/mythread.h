#ifndef THREAD_H
#define THREAD_H

#include<stdio.h>
#include<stdlib.h>
#include<ucontext.h>
#include<signal.h>
#include<sys/time.h>
#include<unistd.h>
#include"../include/list.h"

struct list* threadlist;
static ucontext_t ctx;

void mythread_init()
{
	threadlist = (struct list*)malloc(sizeof(struct list));
	// printf("Initialized thread list\n");
};      // Initialize threads list

ucontext_t* mythread_create(void func(void*), void* arg)
{
	// printf("%d\n",is_empty(threadlist));
	// printf("Hello is this working\n");
	ucontext_t* c = (ucontext_t*)malloc(sizeof(ucontext_t));  
	getcontext(c);
	c->uc_stack.ss_sp = (char*)malloc(4096*sizeof(char));
	c->uc_stack.ss_size = 4096*sizeof(char);
	c->uc_link = &ctx;
	void* arg_ptr = (void*) arg; 
	makecontext(c,(void (*)(void))func,1,arg_ptr);
	list_add(threadlist,c);
	return c;
};  // Create a new thread

void mythread_join()
{
	// printf("Hello check 1234\n");
	if(is_empty(threadlist)) return;
	ucontext_t* head = (ucontext_t*)(threadlist->head)->data;
	getcontext(&ctx);
	swapcontext(&ctx,head);
	// printf("Return ho rha hai kya?\n");
	list_rm(threadlist,threadlist->head);
	mythread_join();
};  // Waits for other thread to complete. It is used in case of dependent threads.

void mythread_yield()
{

};  // Perform context switching here

struct lock {
	ucontext_t* ctx;
};
struct lock* lock_new();   // return an initialized lock object
void lock_acquire(struct lock* lk);   // Set lock. Yield if lock is acquired by some other thread.
int lock_release(struct lock* lk);   // Release lock

#endif
