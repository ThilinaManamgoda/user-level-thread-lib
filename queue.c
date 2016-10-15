//
// Created by maanadev on 7/11/16.
//
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


Queue *createQueue(void) {

    Queue *ptr = (Queue *) malloc(sizeof(Queue));
    if (ptr == NULL) {
        printf("no memory\n");
	exit(0);	
    } 
        return ptr;
    
}

void enque(Queue *queue, nodeElement element) {





    if(queue->rear==NULL){
        Node * tmp = (Node *)malloc(sizeof(Node));
        if(tmp==NULL){    printf("no memory\n");exit(0);}
        tmp->value = element;
        tmp->next=NULL;
        queue->rear=tmp;
        queue->front=tmp;

    }else{
        Node * tmp = (Node *)malloc(sizeof(Node));
        tmp->value = element;
        tmp->next=NULL;
        queue->rear->next = tmp;
        queue->rear=tmp;
    }

}

nodeElement dequeu(Queue * queue){


    if(queue->front==NULL){
        printf("queue is empty\n");
        exit(0) ;
    }else{
        Node * tmp = queue->front;
        queue->front = tmp->next;
        return  tmp->value;
    }

}
int isempty(Queue * queue){
    if(queue->front==NULL) return 1;
    else return 0;


}
