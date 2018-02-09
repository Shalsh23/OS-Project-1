#include <futex.h>
#include <mythread.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include "mythread_queueg.h"
#include "mythread.h"
struct futex globalfutex;
mythread_queue_t globalq;
int mythread_yield()
{
	mythread_t next;
	mythread_t current = mythread_self();
	futex_down(&globalfutex);

	next = mythread_q_next(current,globalq);
	
	while (next->state != READY)
		next = mythread_q_next(next,globalq);

	
	if (next == current)
	{
		futex_up(&globalfutex);
		return 0;
	}
	else {
		futex_up(&next->futex);
	}
	if (current->futex.count > 0)
		futex_down(&current->futex);

	futex_up(&globalfutex);

	futex_down(&current->futex);

	return 0;
}
