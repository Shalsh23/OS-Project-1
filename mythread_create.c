#define _GNU_SOURCE
#define CLONE_SIGNAL (CLONE_SIGHAND | CLONE_THREAD)
#include <signal.h>
#include <sched.h>
#include <string.h>
#include <stdlib.h>
#include "futex.h"
#include "mythread.h"
#include <malloc.h>
#include <features.h>
//#include "mythread_queue.h"
#include <sys/syscall.h>
#include <sys/types.h>
#include <error.h>
#include "mythread_queueg.h"
static pid_t gettid(void) {
return (pid_t) syscall(SYS_gettid);
}


mythread_t mythread_q_head;
int wrapper (void *);
extern int flag=0;
extern mythread_queue_t globalq;
extern struct futex globalfutex;
mythread_t *idle_thread;
int mythread_create(mythread_t *new_thread_ID, mythread_attr_t *attr, void * (*start_func)(void *), void *arg)
{
	printf("entering create\n");

 	char *child_stack;
 	int ssize;
 	struct mythread *node;
 	pid_t tid;

	int cloneflags = (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGNAL | CLONE_CHILD_CLEARTID | CLONE_SYSVSEM);

 
	if (flag==0) {
			globalq = (mythread_queue_t) malloc(sizeof(struct mythread_queue));
		globalq->head = NULL;
		printf("making main\n");
 	mythread_t main1 = (mythread_t) malloc(sizeof(struct mythread));
 
	main1->start_func = NULL;
	main1->arg = NULL;
	main1->joinq = NULL;
	main1->returnValue = NULL;
	main1->state = READY;	

	/* Get the main's tid and put it in its corresponding tcb. */
	main1->tid = gettid();

	/* Initialize futex to one since the main thread executes first */
	 futex_init(&main1->futex, 0);

	//  Put it in the Queue of thread blocks 
	 mythread_q_add(main1,globalq);
	
	 futex_init(&globalfutex, 1);
	 printf("dahvbsj\n");
	 flag = 1;
	mythread_create(idle_thread, NULL, mythread_idle, NULL);
	}

node = (struct mythread*) malloc(sizeof(struct mythread));
 	if (attr == NULL)
 		ssize = SIGSTKSZ;
	else
		ssize = attr->stacksize;
		posix_memalign((void **)&child_stack, 8, ssize);
		child_stack = child_stack + ssize - sizeof(sigset_t);
		node->start_func = start_func;
	node->arg = arg;
	node->state = READY;
	node->returnValue = NULL;
	node->joinq = NULL;
	futex_init(&node->futex, 0);
	mythread_q_add(node,globalq);
	printf("main ho raha hu\n");
	if ((tid =
	     clone(wrapper, (char *)child_stack, cloneflags,
		   node)) == -1) {
		write(1,"clone failed!\n",15);
		return -1;
	}
	(*(*new_thread_ID)).tid = tid;
	node->tid = tid;

	printf("create: Finished initialising new thread: \n");
// 		     //(unsigned long)new_thread_ID->tid);
	return 0;
}