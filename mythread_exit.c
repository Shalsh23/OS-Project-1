#include <mythread.h>
#include <futex.h>
#include <sys/syscall.h>
mythread_queue_t globalq;
void mythread_exit(void *retval)
{
	mythread_t current;

	/* Get pointer to our TCB structure */
	current = mythread_self();
	//mythread_linked_pid_t i;
	/* Don't remove the node from the list yet. We still have to collect the return value */
	current->state = DEAD;
	current->returnValue = retval;
	mythread_linked_node_t temp;
	/* Change the state of any thread waiting on us. FIFO dispatcher will do the 
	 * needful
	 */
	if (current->joinq != NULL)
	{
		temp = current->joinq->head;
		do{		
			temp->data->state = READY;	
			//mythread_t a = mythread_q_search(i->data,globalq);
			//a->state = READY;
			futex_up(&temp->data->futex);
			temp = temp->next;
		}while (temp->next != current->joinq->head);
	} 
	mythread_t next = mythread_q_next(current,globalq);
	
	while (next->state != READY)
		next = mythread_q_next(next,globalq);

	
	if (next == current)
		return 0;
	else 
		futex_up(&next->futex);
	
	syscall(SYS_exit, 0);
}