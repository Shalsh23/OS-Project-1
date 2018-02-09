#include "mythread.h"
#include "futex.h"
#include "mythread_queueg.h"

struct futex globalfutex;
 mythread_queue_t globalq;
/* Idle thread implementation. 
 * The thread checks whether it is the only one alive, if yes, exit()
 * else keep scheduling someone.
 */
  void mythread_idle()
 {
	mythread_t t;
	pid_t idle_tid;
 
 	while (1) {
		t = mythread_self();
		idle_tid = t->tid;
		t = mythread_q_next(t,globalq);
		while (t->tid != idle_tid) {
			if (t->state == READY) 
				break;
			t = mythread_q_next(t,globalq);
		}

		if (t->tid == idle_tid)
			exit(0);
		mythread_yield();
	}
}