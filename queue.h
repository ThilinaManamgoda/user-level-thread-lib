//
// Created by maanadev on 7/11/16.
//
#ifndef OS_LABS_QUEUE_H
#define OS_LABS_QUEUE_H
/* information about threads */
struct tcb { 
  void *sp;  /* Address of stack pointer. 
	      * Keep this as first element would ease switch.S 
	      * You can do something else as well. 
	      */  
  /* you will need others stuff */ 

 
};
typedef struct tcb tcb_t;
typedef struct tcb *TCB;
typedef TCB nodeElement;

typedef struct QueueNode {
    nodeElement value;
    struct QueueNode *next;
} Node;
typedef struct queue {
    Node *front;
    Node *rear;
} Queue;

Queue *createQueue(void);

void enque(Queue * queue ,nodeElement element);

nodeElement dequeu(Queue * queue);

int isempty(Queue * queue);

#endif //OS_LABS_QUEUE_H
