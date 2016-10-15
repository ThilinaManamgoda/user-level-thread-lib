#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "threadlib.h"
#include "queue.h"
//#define DEBUG
/* uncomment when you are done! */

//#ifdef DEBUG
// #define PRINT   printf
//#else 
// #define PRINT(...)
//#endif


/**
 * assembly code for switching 
 * @sp -- new stack to switch 
 * return sp of the old thread
 * 
 * Switching 
*/
void machine_switch(tcb_t *newthread /* addr. of new TCB */, 
		    tcb_t *oldthread /* addr. of old TCB */
			);

void switch_threads(tcb_t *newthread /* addr. of new TCB */, 
		    tcb_t *oldthread /* addr. of old TCB */);
		    
void delete(tcb_t *nextThread);/*Restore the regs of the thread and run it*/
/** Data structures and functions to support thread control box */ 



	TCB currentThread; 
	TCB mainThread;  
	Queue *queue ;
    int firstTime=1;
/** end of data structures */



void switch_threads(tcb_t *newthread /* addr. of new TCB */, tcb_t *oldthread /* addr. of old TCB */) {

  /* This is basically a front end to the low-level assembly code to switch. */
 
	assert(!printf("Implement %s",__func__));

}


/*********************************************************
 *                 Thread creation etc 
 *********************************************************/

/* Notes: make sure to have sufficient space for the stack
 * also it needs to be aligned 
 */

#define STACK_SIZE (sizeof(void *) * 1024)
#define FRAME_REGS 48 // is this correct for x86_64?

#include <stdlib.h>
#include <assert.h>

/*
 * allocate some space for thread stack.
 * malloc does not give size aligned memory 
 * this is some hack to fix that.
 * You can use the code as is. 
 */
void * malloc_stack(void); 

void * malloc_stack() 
{
  /* allocate something aligned at 16
   */
   void *ptr = malloc(STACK_SIZE + 16);
   if (!ptr) return NULL;
   ptr = (void *)(((long int)ptr & (-1 << 4)) + 0x10);
   ptr = ptr + (STACK_SIZE - sizeof(void *) *FRAME_REGS);/*make space for frame regs*/
   return ptr;
}

int create_thread(void (*ip)(void)) {

	long int  *stack; 
	stack =(long int  *) malloc_stack();
	if(!stack) return -1; /* no memory? */
	TCB  newThread = malloc(sizeof(tcb_t));
        *stack =(long int)ip;
	/*Running for the first time threads don't have anything to popup. Since 9 regs are saved we make 9 offset in the thread's stack*/
        if(firstTime) { 

		newThread->sp=stack;
		firstTime=0;
	}else{

		newThread->sp=stack-9;	
	}
        if(queue==NULL){
            queue=createQueue();
        }

        enque(queue,newThread);
  /**
   * Stack layout: last slot should contain the return address and I should have some space 
   * for callee saved registers. Also, note that stack grows downwards. So need to start from the top. 
   * Should be able to use this code without modification Basic idea: C calling convention tells us the top 
   * most element in the stack should be return ip. So we create a stack with the address of the function 
   * we want to run at this slot. 
   */

	return 0;
}

void yield(){
  /* thread wants to give up the CPUjust call the scheduler to pick the next thread. */

   TCB old=currentThread;
    enque(queue,currentThread);//put thread to queue
    if(!isempty(queue)) currentThread = dequeu(queue);//get the next thread to run
    else exit(0);

 
   machine_switch(currentThread,old);
	
}


void delete_thread(void){
	  
 	if(!isempty(queue)) {currentThread = dequeu(queue);
		delete(currentThread);}
	else exit(0);
  /* When a user-level thread calls this you should not 
   * let it run any more but let others run
   * make sure to exit when all user-level threads are dead */ 
  
	   
  //assert(!printf("Implement %s",__func__));
}


void stop_main(void)
{ 
  /* Main function was not created by our thread management system. 
   * So we have no record of it. So hijack it. 
   * Do not put it into our ready queue, switch to something else.*/

       
       if(!isempty(queue)) currentThread = dequeu(queue);
        else exit(0);
        machine_switch(0,currentThread);//calling the switch for the first time with 0 as the first argument since there is no old thread

	
 // assert(!printf("Implement %s",__func__));

}
