#include "futex.h"
#include "mythread.h"
#include "myatomic.h"

int wrapper (void *thread)
{
	mythread_t a = (struct mythread *) thread;
	a = mythread_self();
	//printf("wrapper\n");
	futex_down(&a->futex); 
	a->start_func(a->arg);
	return 0;
}