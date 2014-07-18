#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct node* left;
typedef struct node* right;
typedef struct node{
	int data;
	left l;
	right r;
}node;
node* root=NULL;
int node_count=0;
bool makenode(node* newnode,int d){
	if(!newnode)
	{
		newnode=(node*)malloc(sizeof(node));
		newnode->data=d;
		newnode->l=NULL;
		newnode->r=NULL;
		return true;
	}
	newnode->data=d;
	newnode->l=NULL;
	newnode->r=NULL;
	return true;
}
bool maketree(int* a,int n){
	if(!a || n<=0){
		printf("Please enter valid inputs array of intgers and its size to make tree\n");
		return false;
	}
	root=(node*)malloc(sizeof(node));
	makenode(root,a[0]);
	node_count++;
	int i;
	for(i=1;i<n;i++){
		node* tmp=root;
		while(tmp){
			if(a[i]<=tmp->data){
				if(tmp->l){
					tmp=tmp->l;
					continue;
				}
				else{
					tmp->l=(node*)malloc(sizeof(node));
					makenode(tmp->l,a[i]);
					node_count++;
					break;
				}
			}		
			if(a[i]>tmp->data){
				if(tmp->r){
					tmp=tmp->r;
					continue;
				}
				else{
					tmp->r=(node*)malloc(sizeof(node));
					makenode(tmp->r,a[i]);
					node_count++;
					break;
				}		
			}
		}
	}
	return true;
}
bool preorder(node* root){
	if(root){
	int l=root->l?root->l->data:-1;
	int r=root->r?root->r->data:-1;
	printf("element is %d left child is %d right child is %d\n",root->data,l,r);
	preorder(root->l);
	preorder(root->r);
	return true;
	}
return false;
}
bool inorder(node* root){
	if(root){
		inorder(root->l);
		int l=root->l?root->l->data:-1;
		int r=root->r?root->r->data:-1;
		printf("element is %d left child is %d right child is %d\n",root->data,l,r);
		inorder(root->r);
		return true;
	}
return false;
}
int main(){
	int* a=(int*)malloc(sizeof(int));
	printf("Enter the sequence of integers to make bst\n");
	int i=0,el;
	do{
	   scanf("%d",&el);
	if(el!=-1){
		a[i]=el;
		i++;
		a=(int*)realloc(a,(i+1)*sizeof(int));
		}
	}while(el!=-1);
	printf("You entered:\n");
	for(el=0;el<i;el++)
		printf("%d\t",a[el]);
	printf("\n");
	maketree(a,i);
	printf("Preorder walk:\n");
	preorder(root);
	printf("Inorder walk:\n");
	inorder(root);
return 0;
}
