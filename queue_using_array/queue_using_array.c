#include<stdio.h>
#include<stdlib.h>
typedef struct element{
	int data;
}element;
element** q;
int q_size;
int head=0,tail=0;/******tail points to one index more than last element's index************************/
int i,j;
enum boolean{false,true};
enum boolean enqueue(element* el){
	if(tail==q_size){
		printf("queue is full, incrementing queue-size by 10\n");
		q=(element**)realloc(q,(q_size+10)*sizeof(element*));
		q[tail++]=el;
		q_size+=10;
		}else{
			q[tail++]=el;
			}
return true;
}
enum boolean is_empty(){
	if(head==tail){
		return true;
		}else{
			return false;
			}
}
element* dequeue(){
	if(is_empty()){
		printf("Queue is empty\n");
		return 0;
		}else{
			element* temp=q[head];
			for(i=0;i<tail-1;i++){
				q[i]=q[i+1];
				}
				tail--;
			return temp;
			}
}
enum boolean display(){
	if(is_empty()){
		printf("Queue is empty\n");
		return false;
		}else{
		for(i=0;i<tail;i++)
			printf("%d\t",q[i]->data);
		return true;
		}
}
int main(int argc,char* argv[]){
	int new_el,choice;
	element* new_node;
	printf("Eneter the initial size of the queue you want to implement:\n");
	scanf("%d",&q_size);
	printf("You entered\t%d\n",q_size);
	q=(element**)malloc(q_size*sizeof(element*));
	do{
		printf("1.Enqueue an element\n");
		printf("2.Dequeue an element\n");
		printf("3.Check if queue is empty\n");
		printf("4.Display elements of the queue\n");
		printf("Eneter any other option to exit\n");
		printf("Choose the option:\n");
		scanf("%d",&choice);
		printf("You entered\t%d\n",choice);
		switch(choice){
		case 1:
		printf("Enter the integer to enqueue into the queue:\n");
		scanf("%d",&new_el);
		new_node=(element*)malloc(sizeof(element));
		new_node->data=new_el;
		if(enqueue(new_node))/*****another choice element new_el enqueue(&new_el)********/
		printf("Enqueued\t%d\n",q[tail-1]->data);
		break;
		case 2:
		new_node=dequeue();
		if(new_node->data!=0){
			printf("Dequeued\t%d \n",new_node->data);
			}
		break;
		case 3:
		if(is_empty()){
		printf("Queue is empty\n");
		
		}else{
			printf("Queue has \t%delements\n",tail);
			}	
		break;
		case 4:
		if(display())
		printf("\nQueue contents are displayed from head to tail\n");
		break;
		default:
		printf("Exiting\n");
		return 0;
		}
	}while(true);
	return 0;
	
}
