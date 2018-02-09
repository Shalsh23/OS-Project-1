#include "mythread.h"
#include "mythread_queueg.h"
#include <malloc.h>

/* The global extern pointer defined in mythread.h which points to the head node in
   Queue of the Thread Control Blocks.
*/
  

/* This function initializes the Queue with a single node.
*/
int flag;
mythread_linked_node_t GetNewNode(mythread_t x) 
{
	mythread_linked_node_t newNode
		= (struct mythread_linked_node*)malloc(sizeof(struct mythread_linked_node));
	newNode->data = x;
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
}

void mythread_q_addh(mythread_t x,mythread_queue_t q) 
{
	mythread_linked_node_t newNode = GetNewNode(x);
	if(q->head == NULL) {
		q->head = newNode;
		return;
	}
	q->head->prev = newNode;
	newNode->next = q->head; 
	q->head = newNode;
}

void mythread_q_add(mythread_t x,mythread_queue_t q) 
{
	mythread_linked_node_t temp = q->head;
	mythread_linked_node_t newNode = GetNewNode(x);
	if(q->head == NULL) {
		q->head = newNode;
		return;
	}
	while(temp->next != NULL) temp = temp->next; // Go To last Node
	temp->next = newNode;
	newNode->prev = temp;
	newNode->next = q->head;
}

mythread_t mythread_q_next (mythread_t x, mythread_queue_t q)
{
	mythread_linked_node_t temp = q->head;
	mythread_linked_node_t newNode = GetNewNode(x);
	if(q->head == NULL) {
		return;
	}
	while(temp->data->tid != newNode->data->tid) temp = temp->next; // Go To last Node
	return temp;
}

/*mythread_t mythread_q_search (pid_t x, mythread_queue_t q)
{
	mythread_linked_node_t traverse;
	if(q->head !=NULL)
	{
		traverse = q->head;
		do
		{
			if(traverse->data->tid == x) return traverse->data; 
			traverse = traverse->next;
		}while(traverse->data->tid != q->head->data->tid);
	}
}
*/
/*mythread_t mythread_q_nextpid (pid_t x, mythread_queue_t q)
{
	mythread_linked_node_t traverse;
	if(q->head !=NULL)
	{
		traverse = q->head;
		do
		{
			if(traverse->data->tid == x) return traverse->next->data; 
			traverse = traverse->next;
		}while(traverse->data->tid != q->head->data->tid);
	}
}
void mythread_q_init(mythread_t node, mythread_queue_g_t q)
{

	q->head->data = node;
	q->head->next = head;
	q->head->prev = head;
}


void mythread_q_add(mythread_t node, mythread_queue_g_t q)
{

	if (q->head == NULL) {
		//Q is not initiazed yet. Create it.
		mythread_q_init(node,q);
		return;
	}
	//Insert the node at the end of Q
	mythread_linked_node_t a;
	a->data = node;
	a->next = q->head;
	a->prev = q->head->prev;
	q->head->prev->next = a;
	a->head->prev = a;

	return;

}
mythread_t mythread_q_next (mythread_t node, mythread_queue_g_t q)
{
	//pid_t node_tid = node -> tid;
	mythread_linked_node_t a;
	if(q->head != NULL)
	{
		a->data->tid = q->head->data->tid;
		do
		{
			if (a->data->tid == node->tid) return  a->next->data;
				a = a->next;
		}while(a->head->tid!=q->head->data->tid);	
	}
	
}

*/

