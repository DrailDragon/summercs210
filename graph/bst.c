#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct node{
	int left;
	int right;
}node;
node* bst=NULL;
int node_count;
bool makenode(node* newnode){
	if(!newnode)
		return false;
	newnode->left=-1;
	newnode->right=-1;
	return true;
}
bool maketree(int* a,int n){
	if(!a || n<=0){
		printf("Please enter valid inputs array of intgers and its size to make tree\n");
		return false;
	}
	bst=(node*)malloc(n*sizeof(node));
	if(!bst){
		printf("Error allocating memory for bst of size:%d\n",n);
		return false;
	}
	int i;
	for(i=0;i<n;i++)
		makenode(&bst[i]);
	node_count=1;
	for(i=1;i<n;i++){
		int j=0;
		while(j<=node_count){
			if(a[i]<=a[j]){
				if(bst[j].left==-1){
					bst[j].left=i;
					node_count++;
					break;
				}
				else{
					j=bst[j].left;
					continue;
				}
			}
			if(a[i]>a[j]){
				if(bst[j].right==-1){
					bst[j].right=i;
					node_count++;
					break;
				}
				else{
					j=bst[j].right;
					continue;
				}
			}
		}/******end while**********/
	}/****end for*****/
	return true;
}
bool preorder(int* a,int root){
	if(root>=0){
	int l=bst[root].left>=0?a[bst[root].left]:-1;
	int r=bst[root].right>=0?a[bst[root].right]:-1;
	printf("element is:%d left child is:%d right child is:%d\n",a[root],l,r);
	preorder(a,bst[root].left);
	preorder(a,bst[root].right);
	return true;
}
return false;
}
int main(){
	/*printf("Enter the number of integers \n");*/
	printf("Enter the sequence of numbers,enter -1 to stop\n");
	int* a=(int*)malloc(sizeof(int));
	int i=0,el;
	do{
	   scanf("%d",&el);
	if(el!=-1){
		a[i]=el;
		i++;
		a=(int*)realloc(a,(i+1)*sizeof(int));
		}
	}while(el!=-1);
	for(el=0;el<i;el++)
		printf("%d\t",a[el]);
	printf("\n");
	maketree(a,i);
	preorder(a,0);
return 0;
}
