#ifndef AUX_H
#define AUX_H
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
bool push(int* stk,int* top,int v,int node_count){
	if(*top>=node_count-1){
	return false;
	}
	*top+=1;
	stk[*top]=v;
	return true;
}
int pop(int* stk,int* top,int node_count){
 	if(*top==-1)
	return -1;
	*top-=1;
	return stk[(*top)+1];
}
/*****start tail=head=1 in the driver function****************/
bool enqueue(int* q,int* head,int* tail,int element,int max_size){
	if(*tail==(*head-1) || (*tail==max_size-1 && *head==0)){
		printf("Queue full\n");
		return false;
	}
	q[*tail]=element;
	++(*tail);
	if(*tail==max_size)
		*tail=0;
	return true;
}
int dequeue(int* q,int* head,int* tail,int max_size){
	if(*tail==*head){
		printf("Queue empty\n");
		return -1;
	}
	int tmp=q[*head];
	++(*head);
	if(*head==max_size)
		*head=0;
	return tmp;
}
/*bool enqueue(int* q,int* tail,int v,int node_count){
	if(*tail>=node_count)
	return false;
	q[*tail]=v;
	*tail+=1;
	return true;
}
int dequeue(int* q,int* tail,int node_count){
	if(*tail==0)
	return -1;
	int h=q[0],i;
	for(i=0;i<*tail-1;i++)
		q[i]=q[i+1];
	*tail-=1;
	return h;
}*/
#endif
