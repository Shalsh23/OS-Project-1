#include "mythread.h"
#include "mythread_queueg.h"
#include <sys/syscall.h>

int mythread_join(mythread_t target_thread, void **status)
{
	mythread_t target, current;

	current = mythread_self();
	if (target_thread->state == DEAD) {
		*status = target_thread->returnValue;
		return 0;
	}
	
	mythread_q_add(current,target_thread->joinq);
	
	current->state = BLOCKED;

	/* Schedule another thread */
	mythread_yield();

	/* Target thread died, collect return value and return */
	*status = target_thread->returnValue;
	return 0;
}