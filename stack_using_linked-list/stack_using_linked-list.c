#include<stdio.h>
#include<stdlib.h>
typedef struct node* node_ptr;
typedef struct element{
	int data;
}element;
typedef struct node {
	element* elem;
	node_ptr next;
}node;
node* top;

int node_count=0;/****node-count can't be used*************/
enum boolean{false,true};
enum boolean push(element* el){
	if(node_count==0){
	top=(node*)malloc(sizeof(node));
	top->elem=el;/******instead of -> . can't be used********/
	top->next=NULL;
	}else{  
		node* temp;
		temp=(node*)malloc(sizeof(node));
		temp->elem=el;
		temp->next=top;
		top=temp;
		}
node_count++;
return true;
}
enum boolean is_empty(){
	if(node_count==0)
		return true;
	else
		return false;
}
node* pop(){
	if(is_empty()){
		printf("Stack is empty\n");
		return NULL;
	}
	else{
	    node* tmp;
	    tmp=top;
	    top=top->next;
	    tmp->next=NULL;
	    node_count--;
	    return tmp;
	   }
}
enum boolean display_contents(){
	if(is_empty()){
		printf("Stack is empty\n");
		return false;
	}
	else{
		node* t=top;
		while(t){
		printf("%d\t",t->elem->data);
		t=t->next;
		}
	return true;
	}
}
int main(){
int choice;
int new_el;
element* el_node;
node* popped_el;
do{printf("Choose the option: \n");
printf("1.Push  \n");
printf("2.Pop \n");
printf("3.Check if stack is empty \n");
printf("4.Display stack-contents \n");
printf("Any other option to Exit \n");
printf("Enter your choice: \n");
scanf("%d",&choice);
printf("You entered:%d \n",choice);
switch(choice){
	case 1:
	printf("Enter the integer: \n");
	scanf("%d",&new_el);
	el_node=(element*)malloc(sizeof(element));
	el_node->data=new_el;
	if(push(el_node)){
		printf("Successfully pushed\t%d\n",top->elem->data);
		break;
	}else{
		printf("Error pushing the integer \t%d\n",new_el);
		break;
		}
	case 2:	
	popped_el=pop();
	if(popped_el){
	printf("Popped %d \n",popped_el->elem->data);
	break;
		}else{
	break;
	}
	case 3:
	if(is_empty())
	printf("Stack is empty\n");
	else
	printf("Stack has \t%d\t elements\n",node_count);
	break;
	case 4:
	if(display_contents()){
		printf("\nStack-contents are displayed from top to bottom\n");
		}
	break;
	default:
	printf("Exiting\n");
	return 0;
	}}while(true);
	return 0;
}
