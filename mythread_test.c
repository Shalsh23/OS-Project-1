#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <linux/module.h>
// #include <linux/kernel.h>
// #include <linux/init.h>
#include "mythread.h"
#include "mythread_queueg.h"

/* Number of threads to start */
#define NTHREADS	1

/* This function will first increment count by 50, yield. When it gets the 
 * control back, it will increment count again and then exit
 */
// void *thread_func(void *arg)
// {
// 	int *count = (int *)arg;

// 	*count = *count + 50;
// 	printf("Thread %ld: Incremented count by 50 and will now yield\n", (unsigned long)mythread_self()->tid);
// 	//mythread_yield();
// 	*count = *count + 50;
// 	printf("Thread %ld: Incremented count by 50 and will now exit\n", (unsigned long)mythread_self()->tid);
// 	//mythread_exit(NULL);
// 	return NULL;
// }

void *thread_func(void *arg)
{
	int *x = (int*) arg;
	printf("abcd%d", *x);
	mythread_exit(NULL);
}
/* This is a simple demonstration of how to use the mythread library.
 * Start NTRHEADS number of threads, collect count value and exit
 */
int main()
{
	printf("entering test program\n");
	mythread_t* threads[NTHREADS];
	//int count[NTHREADS];
	int i;
	char *status;

	for (i = 0; i < NTHREADS; i++) {
		//count[i] = i;
		
		mythread_create(threads[i], NULL, thread_func, &i);
		printf("creating thread \n" );
	}
	for (i = 0; i < NTHREADS; i++) {
		printf("Main: Will now wait for thread %d. Yielding..\n", i);
		mythread_join(threads[i], (void **)&status);
		printf("Main: Thread %d exited and increment count to \n",i);
	}
	//mythread_yield();
	 //sleep(120);
// 	printf("Main: All threads completed execution. Will now exit..\n");
mythread_exit(NULL);
// 
	return 0;
}