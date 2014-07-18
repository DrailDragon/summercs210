#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#define maxsize 10
bool enqueue(int* q,int* head,int* tail,int max_size,int element){
	if(*tail==(*head-1) || (*tail==max_size-1 && *head==0)){
		printf("Queue full\n");
		return false;
	}
	q[*tail]=element;
	printf("%d\t",q[*tail]);
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
bool printq(int* q,int* head,int* tail,int max_size){
	if(*tail==*head){
		printf("Queue empty\n");
		return false;
	}
	int i;
	printf("Queue elements are:\n");
	if(*head<*tail){
		for(i=*head;i<*tail;i++)
			printf("%d\t",q[i]);
		printf("\n");
		}
	if(*head>*tail){
		for(i=*head;i<max_size;i++)
			printf("%d\t",q[i]);
		for(i=0;i<*tail;i++)
			printf("%d\t",q[i]);
		printf("\n");
	}
	return true;
}
int main(){
	int q[maxsize],head=1,tail=1,i;
	srand(time(NULL));
	printf("enqueue 5:\n");
	for(i=0;i<5;i++)
	enqueue(q,&head,&tail,maxsize,rand()%100);
	printf("\nhead is %d tail is %d\n",head,tail);
	printf("dequeue 6:\n");
	for(i=0;i<6;i++)
	printf("%d\t",dequeue(q,&head,&tail,maxsize));
	printf("\nhead is %d tail is %d\n",head,tail);
	printf("enqueue 10:\n");
	for(i=0;i<10;i++)
	enqueue(q,&head,&tail,maxsize,rand()%100);
	printf("\nhead is %d tail is %d\n",head,tail);
	printf("dequeue 4:\n");
	for(i=0;i<4;i++)
	printf("%d\t",dequeue(q,&head,&tail,maxsize));
	printf("\nhead is %d tail is %d\n",head,tail);
	printf("dequeue 1:\n");
	printf("%d\t",dequeue(q,&head,&tail,maxsize));
	printf("\nhead is %d tail is %d\n",head,tail);
	printf("enqueue 10:\n");
	for(i=0;i<10;i++)
	enqueue(q,&head,&tail,maxsize,rand()%100);
	printf("\nhead is %d tail is %d\n",head,tail);
	printf("dequeue 10:\n");
	for(i=0;i<10;i++)
	printf("%d\t",dequeue(q,&head,&tail,maxsize));
	printf("\nhead is %d tail is %d\n",head,tail);
	printf("enqueue 10:\n");
	for(i=0;i<10;i++)
	enqueue(q,&head,&tail,maxsize,rand()%100);
	printq(q,&head,&tail,maxsize);
	printf("\nhead is %d tail is %d\n",head,tail);
	printf("dequeue 10:\n");
	for(i=0;i<10;i++)
	printf("%d\t",dequeue(q,&head,&tail,maxsize));
	printq(q,&head,&tail,maxsize);
	printf("\nhead is %d tail is %d\n",head,tail);
return 0;
}
