#include "mythread.h"
#include <syscall.h>
#include "mythread_queueg.h"
mythread_queue_t globalq;
mythread_t mythread_self(){

	pid_t ptid = (pid_t) syscall(SYS_gettid);
	mythread_linked_node_t t;
	if (globalq->head != NULL) {

		t = globalq->head;
		do {
			if (t->data->tid == ptid)
				return t;
			t = t->next;
		} while (t != globalq->head);

	}
	return t->data;
}