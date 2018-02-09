#include "mythread.h"
#include "mythread_queue.h"
//#include "mythread_queue.h"


void mythread_q_init_joinq(mythread_t node, mythread_queue_t q)
{

	q->head->data = node->tid;
	q->head->next = head;
	q->head->prev = head;

/*	mythread_linked_node a;
	a->data = node;
	a->prev = &a;
	a->next = &a;
	head = &a;
*/	//head = node;
}

/* This function adds a node to the Queue, at the end of the Queue. 
   This is equivalent to Enque operation.
 */
void mythread_q_add_joinq(mythread_t node, mythread_queue_t q)
{

	if (q->head == NULL) {
		//Q is not initiazed yet. Create it.
		mythread_q_init_joinq(node,q);
		return;
	}
	//Insert the node at the end of Q
	mythread_linked_pid_t a;
	a->data = node->tid;
	a->next = q->head;
	a->prev = q->head->prev;
	q->head->prev->next = a;
	a->head->prev = a;

	return;

}