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
bool enqueue(int* q,int* tail,int v,int node_count){
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
}
#endif
