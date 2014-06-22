#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<ctime>
#include<stdio.h>
#include<fstream>
#include "stack1.h"
using namespace std;
struct element{
	char* str;
	int count;
	};

struct btree{
	element* elem;
	int lindex;
	int rindex;
	int lheight;
	int rheight;
	};

btree* bt=NULL;
int total_count=0;
int tree_size=0;
int ar_size=100;
int tree_root=0;
bool maketree(element* el){
	bt[tree_size].elem=el;
	bt[tree_size].lindex = -1;
	bt[tree_size].rindex = -1;
	bt[tree_size].lheight = 0;
        bt[tree_size].rheight = 0;
	return true;
	}
int get_height(int root){
	if(tree_size == 0 || root == -1 )
		return 0;
	else{
		int h=1;
	if(bt[root].rheight>bt[root].lheight)
	h+=bt[root].rheight;
	else
	h+=bt[root].lheight;
	return h;
	}
}
bool ll_rotate(int index,stack1* st_p){
	if(index<0 || index>=tree_size){
		 cout<<"Enter an index between 0 and\t"<<tree_size-1<<"(inclusive)"<<endl;
		return false;
		}
	if((bt[index].lheight-bt[index].rheight) != 2)
		/*{cout<<"Skipping ll_rotation due to lheight-rheight!=2"<<"\tlheight:\t"<<bt[index].lheight<<"\trheight\t"<<bt[index].rheight<<endl;
		return false;}*/
		return false;
	int l = bt[index].lindex;
	if(l==-1){
		//cout<<"Skipping ll_rotation since l==-1"<<endl;
		return false;}
	if((bt[l].lheight-bt[l].rheight)!=1)
		{
		//cout<<"Skipping ll_rotation due to lheight-rheight!=1"<<"\tlheight:\t"<<bt[l].lheight<<"\trheight\t"<<bt[l].rheight<<endl;
		return false;}
	//cout<<"ll rotation started:"<<endl;
	int lr = bt[l].rindex;
	bt[l].rindex = index;
	bt[index].lindex = lr;
	bt[index].lheight=get_height(lr);
	bt[l].rheight =get_height(index);
	/****assign parent of *index to l*****/
	if(!st_p->if_empty()){
		int parent = st_p->pop();
		if(bt[parent].lindex == index)
			bt[parent].lindex=l;
		else
			bt[parent].rindex=l;
	}else
		tree_root = l;
	//cout<<"ll rotation finished:"<<endl;
	return true;
}
bool rr_rotate(int index,stack1* st_p){
	if(index<0 || index>=tree_size){
		cout<<"Enter an index between 0 and\t"<<tree_size-1<<"inclusive"<<endl;
		return false;
		}else{
	if((bt[index].lheight-bt[index].rheight )!= -2)
		{//cout<<"Skipping rr_rotation due to lheight-rheight!=-2"<<"\tlheight:\t"<<bt[index].lheight<<"\trheight\t"<<bt[index].rheight<<endl;
		return false;}
	int r = bt[index].rindex;
	if(r == -1)
		return false;
	if((bt[r].lheight-bt[r].rheight)!=-1)
		return false;
	//cout<<"rr rotation started:"<<endl;
	int rl = bt[r].lindex;
	bt[r].lindex = index;
	bt[index].rindex = rl;
	bt[index].rheight =get_height(rl);
	bt[r].lheight =get_height(index);
	if(!st_p->if_empty()){
		int parent = st_p->pop();
		if(bt[parent].lindex == index)
			bt[parent].lindex=r;
		else
			bt[parent].rindex=r;
	}else {
		tree_root = r;
		}
	//cout<<"rr rotation finished:"<<endl;
	return true;
	}
}
bool lr_rotate(int index,stack1* st_p){
	if(index<0 || index>=tree_size){
		cout<<"Enter an index between 0 and\t"<<tree_size-1<<"(inclusive)"<<endl;
		return false;
		}
	if((bt[index].lheight-bt[index].rheight) != 2)
		return false;
	int l = bt[index].lindex;
	if(l==-1)
		return false;
	if((bt[l].lheight-bt[l].rheight )!= -1)
		return false;
	//cout<<"lr rotation started:"<<endl;
	int lr= bt[l].rindex;
	int lrl=bt[lr].lindex;
	bt[l].rindex = bt[lr].lindex;
	bt[index].lindex=lr;
	bt[lr].lindex=l;
	bt[l].rheight =get_height(lrl);
	bt[lr].lheight =get_height(l);
	//cout<<bt[l].elem->str<<"bt[l].rheight\t"<<bt[l].rheight<<"lheight of \t"<<bt[lr].elem->str<<bt[lr].lheight<<"going further for ll rotation :"<<endl;
	return ll_rotate(index,st_p);
}
bool rl_rotate(int index,stack1* st_p){
	if(index<0 || index>=tree_size){
		cout<<"Enter an index between 0 and\t"<<tree_size-1<<"(inclusive)"<<endl;
		return false;
		}
	if((bt[index].lheight-bt[index].rheight)!=-2)
		return false;
	int r = bt[index].rindex;
	if(r == -1)
		return false;
	if((bt[r].lheight-bt[r].rheight)!=1)
		return false;
	//cout<<"rl rotation started:"<<endl;
	int rl = bt[r].lindex;
	int rlr=bt[rl].rindex;
	bt[r].lindex = bt[rl].rindex;
	bt[index].rindex = rl;
	bt[rl].rindex = r;
	bt[r].lheight =get_height(rlr);
	bt[rl].rheight =get_height(r);
	//cout<<"going further for rr rotation:"<<endl;
	return rr_rotate(index,st_p); 
}
bool insert_elem(element* el){
	int i = tree_root;
	if(ar_size==tree_size){
		cout<<"Tree full, incrementing the size by 100\n";
		bt=(btree*)realloc(bt,(ar_size+100)*sizeof(btree));
		if(bt==NULL){
		cout<<"Error allocating memory for avltree"<<endl;
		return 0;
		}
		ar_size+=100;
	}
	if(tree_size==0){
		maketree(el);
		total_count+=el->count;
		cout<<"Inserted\t"<<bt[tree_size].elem->str<<"\ttotal count:\t"<<total_count<<"\ttree_size:\t"<<tree_size+1<<endl;
		tree_size++;
		return true;
	}else{
		stack1* p_stack = new stack1(tree_size);
	while(i<=tree_size){
		if(strcmp(bt[i].elem->str,el->str)>0){
			if(bt[i].lindex==-1){
				p_stack->push(i);
				bt[i].lindex = tree_size;
				maketree(el);
				total_count+=el->count;
				cout<<"Inserted\t"<<bt[tree_size].elem->str<<"\ttotal count:\t"<<total_count<<"\ttree_size:\t"<<tree_size+1<<endl;
				tree_size++;
				int p =p_stack->if_empty()?-1:p_stack->pop();
				if(p==-1)
					return true;
				bt[p].lheight +=1;
				//if(strcmp(bt[p].elem->str,"australia")==0)
				//cout<<bt[p].elem->str<<"lheight\t"<<bt[p].lheight<<endl;
				int p1=p_stack->if_empty()?-1:p_stack->pop();
					if(p1==-1)
						return true;
				while(p1!=-1){
					if(bt[p1].lindex == p){
						bt[p1].lheight =get_height(p);
						//bt[p1].lheight+=1;
						//cout<<bt[p1].elem->str<<"lheight\t"<<bt[p1].lheight<<endl;
						}
					else{
						bt[p1].rheight =get_height(p);
						//bt[p1].lheight+=1;
						//cout<<bt[p1].elem->str<<"rheight\t"<<bt[p1].rheight<<endl;
					}
					if((bt[p1].lheight-bt[p1].rheight)==2){
							if((bt[p].lheight-bt[p].rheight)==1)
								ll_rotate(p1,p_stack);
							else
								lr_rotate(p1,p_stack);
						break;
						}
					else if((bt[p1].lheight-bt[p1].rheight)==-2){
							if(bt[p].lheight-bt[p].rheight==-1)
								rr_rotate(p1,p_stack);
							else
								rl_rotate(p1,p_stack);	
						break;
						}
					
						p=p1;
						p1=p_stack->if_empty()?-1:p_stack->pop();
						if(p1==-1)
							break;
						
					}
				delete p_stack;
				return true;
			}else{
				p_stack->push(i);
				i=bt[i].lindex;
				continue;
			}
		}else if(strcmp(bt[i].elem->str,el->str)<0){
			if(bt[i].rindex==-1){
				bt[i].rindex = tree_size;
				maketree(el);
				p_stack->push(i);
				total_count+=el->count;
				cout<<"Inserted\t"<<bt[tree_size].elem->str<<"\ttotal count:\t"<<total_count<<"\ttree_size:\t"<<tree_size+1<<endl;
				tree_size++;
				int p =p_stack->if_empty()?-1:p_stack->pop();
				if(p==-1)
					return true;
				bt[p].rheight +=1;
				//cout<<bt[p].elem->str<<"rheight\t"<<bt[p].rheight<<endl;
				int p1=p_stack->if_empty()?-1:p_stack->pop();
					if(p1==-1)
						return true;
				while(p1!=-1){
					if(bt[p1].lindex == p){
						bt[p1].lheight =get_height(p);
						//bt[p1].lheight+=1;
						//cout<<bt[p1].elem->str<<"lheight\t"<<bt[p1].lheight<<endl;
						}
					else{
						bt[p1].rheight =get_height(p);
						//bt[p1].lheight+=1;
						//cout<<bt[p1].elem->str<<"rheight\t"<<bt[p1].rheight<<endl;
					}
					if((bt[p1].lheight-bt[p1].rheight)==2){
							if((bt[p].lheight-bt[p].rheight)==1)
								ll_rotate(p1,p_stack);
							else
								lr_rotate(p1,p_stack);
						break;
						}
					else if((bt[p1].lheight-bt[p1].rheight)==-2){
							if((bt[p].lheight-bt[p].rheight)==-1)
								rr_rotate(p1,p_stack);
							else
								rl_rotate(p1,p_stack);	
						break;
						}
					
						p=p1;
						p1=p_stack->if_empty()?-1:p_stack->pop();
						
					}
				
				delete p_stack;
				return true;
			}else{
				p_stack->push(i);
				i=bt[i].rindex;
				continue;
			}
			
		}else if (strcmp(bt[i].elem->str,el->str)==0){
			cout<<"Duplicate exists\n";/****duplicate in the sense same string with similar or different repetition count******/
			return false;
			}
		}
	}
   return false;
}
stack1* search_elem(char* s){
	if(tree_size == 0){
		cout<<"No elements in the tree"<<endl;
		return NULL;
		}
	int i=tree_root;
	stack1* stk = new stack1(tree_size);
	while(i<tree_size && i!=-1){
		if(strcmp(bt[i].elem->str,s)==0){
		stk->push(i);
		return stk;
		}else if(strcmp(bt[i].elem->str,s)>0){
			if(bt[i].lindex>=0){
					stk->push(i);
					i=bt[i].lindex;
					continue;
			}else if(bt[i].lindex==-1){
			if(stk!=NULL)
			delete stk;
			return NULL;
			}
		
		}else if(strcmp(bt[i].elem->str,s)<0){
			if(bt[i].rindex>=0){
				stk->push(i);
				i=bt[i].rindex;
				continue;
			}else if(bt[i].rindex==-1){
			if(stk!=NULL)
			delete stk;
			return NULL;
			}	
			}
		}
	if(stk!=NULL)
	delete stk;
	return NULL;
}

int find_successor(char* s){
	stack1* st1 = search_elem(s);
	if(st1==NULL){
		return -1;/********string not found*********/
	}else{	
		int index = st1->pop();
		int r = bt[index].rindex;
		if (r != -1){
			int l = bt[r].lindex;
			if(l == -1){
				delete st1;
				return r;
			}else{
			while(l!=-1 && bt[l].lindex != -1){
				l = bt[l].lindex;
			}
				delete st1;
				return l;
			}
		}else{
			int p = st1->if_empty()?-1:st1->pop();
			if(p==-1){
				delete st1;
				return -2;/*****No successor**********/
			}else{
				if(bt[p].lindex == index){
				delete st1;
				return p;
				}
				else{
					int p1 = st1->if_empty()?-1:st1->pop();
						if(p1 == -1){
						delete st1;
						return -2;}
						else{
						while(p1!=-1 && bt[p1].rindex == p){
								p = p1;
								p1 = st1->if_empty()?-1:st1->pop();
							}
					        if(p1 == -1){
						delete st1;
						return -2;}
						else{
						delete st1;
							return p1;}
						}
					}
				}
			}
		}
}
char* find_kth_string_lexicographic(int k){
	if(k <= 0 || k>tree_size){
		cout<<"Please enter an index between 1 and \t"<<tree_size<<"\n";
		return NULL;
	}else{
	int i = tree_root;
	int t_k =1;
	while(i>=0 && bt[i].lindex>=0 && i<tree_size){
		i=bt[i].lindex;
		}
	while(t_k!= k && i>=0 && i<tree_size){
		i = find_successor(bt[i].elem->str);
		if(i>=0)
		t_k++; 
		}
		if(i>=0)
		return bt[i].elem->str;
		else 
		return NULL;
	}
}
int find_no_of_occurences(char* s){
	int i = tree_root;
	while(i<tree_size){
		if(strcmp(bt[i].elem->str,s)==0)
		return bt[i].elem->count;
		else if(strcmp(bt[i].elem->str,s)>0){
			if(bt[i].lindex>=0){
					i=bt[i].lindex;
					continue;
			}else
			return -1;
		
		}else if(strcmp(bt[i].elem->str,s)<0){
			if(bt[i].rindex>=0){
				i=bt[i].rindex;
				continue;
			}else
			return -1;	
			}
		}
	return -1;
}
bool print_tree(){
	for(int i=0;i<tree_size;i++){
		string l = bt[i].lindex>=0?bt[bt[i].lindex].elem->str:"NULL";
		string r = bt[i].rindex>=0?bt[bt[i].rindex].elem->str:"NULL";
		cout<<"string\t"<<bt[i].elem->str<<"leftchild\t"<<l<<"right child\t"<<r<<endl;
		}
	return true;
}
void Inorder_Traversal(int root){
	if(root>=0){
	
	Inorder_Traversal(bt[root].lindex);
	string l = bt[root].lindex>=0?bt[bt[root].lindex].elem->str:"NULL";
	string r = bt[root].rindex>=0?bt[bt[root].rindex].elem->str:"NULL";
	cout<<bt[root].elem->str<<"\tleft\t"<<l<<"\tright\t"<<r<<endl;
	
	Inorder_Traversal(bt[root].rindex);
	}
}
void Preorder_traversal(int root){
	if(root>=0){
	string l = bt[root].lindex>=0?bt[bt[root].lindex].elem->str:"NULL";
	string r = bt[root].rindex>=0?bt[bt[root].rindex].elem->str:"NULL";
	cout<<bt[root].elem->str<<"\tleft\t"<<l<<"\tright\t"<<r<<endl;
	
	Preorder_traversal(bt[root].lindex);
	
	Preorder_traversal(bt[root].rindex);
	}
}
void PostOrder_Traversal(int root){
	if(root>=0){
	
	PostOrder_Traversal(bt[root].lindex);
	
	PostOrder_Traversal(bt[root].rindex);
	string l = bt[root].lindex>=0?bt[bt[root].lindex].elem->str:"NULL";
	string r = bt[root].rindex>=0?bt[bt[root].rindex].elem->str:"NULL";
	cout<<bt[root].elem->str<<"\tleft\t"<<l<<"\tright\t"<<r<<endl;
	}
}
char* randomStrGen(int length) {
    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char* result;
  //resize(result,length);
   result=(char*)malloc(length*sizeof(char));
   
    for (int i = 0; i < length; i++)
        result[i] = charset[rand() % strlen(charset)];

    return result;
}

int main(){
	bt=(btree*)malloc(100*sizeof(btree));
	if(bt==NULL){
	cout<<"Error allocating memory for avltree"<<endl;
	return 0;
	}
	char* st=NULL;
	int n;
	int x,k=11;
	 char* tmp=NULL;
	stack1* stk1=NULL;
	element* el_node=NULL;
//Remove comment bellow if you wish to generate new input file 
	/*FILE* fp;
	fp=fopen("input_gen.txt","w");
	 srand(time(NULL));
	for(int i=0;i<200;i++){
	st=randomStrGen(10);
	fprintf(fp,"%s",st);
	fprintf(fp," ");
	n = 1+rand()%10;
	fprintf(fp,"%d",n);
	fprintf(fp," ");
	
}
fclose(fp);*/
		FILE* fin=fopen("input_gen.txt","r");
		char line[2621];
		  fgets(line, 2621, fin);
		  
			
			 const char* tok;
			       tok = strtok(line, " ");
			 while(tok && *tok){
				tmp=(char*)malloc(11*sizeof(char));
				strcpy(tmp,tok);
				el_node = new element;
				el_node->str=tmp;
				tok = strtok(NULL, " ");
				x=atoi(tok);
				el_node->count=x;
				insert_elem(el_node);
				// el_node=NULL;
				tok = strtok(NULL, " ");
			    }
		    
		fclose(fin);
	                st=find_kth_string_lexicographic(k);
			if(st!=NULL)
    			cout<<k<<"th string is"<<" "<<st<<endl;
			cout<<"InOrder Traversal:"<<endl;
			Inorder_Traversal(tree_root);
			cout<<endl;
			cout<<"PreOrder Traversal:"<<endl;
			Preorder_traversal(tree_root);
			cout<<"\nPostOrder Traversal:"<<endl;
			 PostOrder_Traversal(tree_root);
			cout<<endl;
			print_tree();
			st=(char*)malloc(11*sizeof(char));
//(Change this string (yrWGRzvIcq )if you generate new input file)
			strcpy(st,"yrWGRzvIcq"); 
 			x=find_no_of_occurences(st);
			if(x==-1)
			cout<<"string not found"<<endl;
			else
			cout<<"number of occurences of string"<<" "<<st<<"\tis\t"<<x<<endl;
			x=find_successor(st);
			if(x==-1)
			cout<<"string\t"<<st<<"\tdoes not belong to the tree"<<endl;
			else if(x==-2)
			cout<<"string\t"<<st<<"\thas no successor"<<endl;
			else
			cout<<"successor of"<<" "<<st<<"\tis\t"<<bt[x].elem->str<<endl;
			stk1=search_elem(st);
			if(stk1==NULL)
			cout<<"string\t"<<st<<"\tnot found in the tree"<<endl;
			else{
			while(!stk1->if_empty()){
				n=stk1->pop();
				cout<<bt[n].elem->str<<"->";			
				}
     				cout<<"NULL"<<"\nPath from string"<<" "<<st<<"\tto\t"<<bt[tree_root].elem->str<<endl;
			    }
				delete st;
	return 0;
}

/*int main(){
	int choice;
	char* st=NULL,*s1=NULL;
	//char inp[100];
	int cnt;
	stack1* stk1=NULL;
	 element* nod =NULL;
	cout<<"Enter initial size of the binary tree you want to implement"<<endl;
	cin>>ar_size;
	bt=(btree*)malloc(ar_size*sizeof(btree));
	if(bt==NULL){
		cout<<"Error allocating memory"<<endl;
		return 0;
	}
	do{
		cout<<"Choose the option:"<<endl;
		cout<<"1. Insert string and count"<<endl;
		cout<<"2. Find kth string lexicographic order"<<endl;
		cout<<"3. Find number of occurences of string"<<endl;
		cout<<"4. Get total number of strings assuming duplicates as distinct strings"<<endl;
		cout<<"5. Get total number of distinct strings"<<endl;
		cout<<"6. Print tree"<<endl;
		cout<<"7. Find successor"<<endl;
		cout<<"8. Print path from the string to root"<<endl;
		cout<<"9.Inorder Traversal"<<endl;
		cout<<"10.Preorder Traversal"<<endl;
		cout<<"11.PostOrder Traversal"<<endl;
		cout<<"Enter any other option to exit"<<endl;
		cin>>choice;
		cout<<"You entered\t"<<choice<<endl;
		
		switch(choice){
			case 1:
			        nod = new element;
				s1=(char*)malloc(5*sizeof(char));
				cout<<"Enter the string and its occurence in order"<<endl;
				cin>>s1;
				nod->str=s1;
				cin>>cnt;
				nod->count=cnt;
				insert_elem(nod);
				 nod=NULL;
				s1=NULL;
				break;
			case 2:
				cout<<"Enter k"<<endl;
				cin>>cnt;
				cout<<"findind\t"<<cnt<<"th"<<endl;
				st=find_kth_string_lexicographic(cnt);
				if(st!=NULL){
					cout<<cnt<<"th string is\t "<<st<<endl;
					free(st);
					break;
				}else{
					cout<<"String not found"<<endl;
					break;
				}
			case 3:
				s1=(char*)malloc(5*sizeof(char));
				cout<<"Enter the string to find its occurences"<<endl;
				cin>>s1;
				cnt=find_no_of_occurences(s1);
				cout<<"String\t"<<s1<<"has\t "<<cnt<<"\toccurences"<<endl;
				free(s1);
					break;
			case 4:
				cout<<"Total number of strings assuming duplicates as separate strings is \t"<<total_count<<endl;
				break;
			case 5:
				cout<<"Total number of distinct strings is \t"<<tree_size<<endl;
				break;
			case 6:
				print_tree();
				break;
			case 7:
				s1=(char*)malloc(5*sizeof(char));
				cout<<"Enter string to find its successor"<<endl;
				cin>>s1;
				cout<<"finding successor for the string"<<s1<<endl;
				choice = find_successor(s1);cout<<"successor choice\t"<<choice<<endl;
				if(choice==-1)
				cout<<" Input string does not belong to the tree"<<endl;
				else if(choice == -2)
				cout<<"No successor found"<<endl;
				else
				cout<<"Successor of input string\t"<<s1<<"is\t"<<bt[choice].elem->str<<endl;
				free(s1);
			break;
			case 8:
				s1=(char*)malloc(5*sizeof(char));
				cout<<"Enter the string to print its path to tree_root"<<endl;
				cin>>s1;
				stk1=search_elem(s1);
				if(stk1==NULL){
					cout<<"String does not belong to the tree"<<endl;
					free(s1);
					break;
					}else{
					while(!stk1->if_empty()){
					cnt=stk1->if_empty()?-1:stk1->pop();
					st =cnt>=0?bt[cnt].elem->str:NULL;
					st!=NULL?cout<<st<<"->":cout<<"NULL";
					}cout<<"NULL\nPath from string\t"<<s1<<"\tto\t"<<bt[tree_root].elem->str<<endl;
					free(s1);
					break;
					}
			case 9:
				cout<<"Inorder Traversal:"<<endl;
				Inorder_Traversal(tree_root);
				cout<<endl;
			break;
			case 10:
				cout<<"Preorder Traversal"<<endl;
				Preorder_traversal(tree_root);
				cout<<endl;
			break;
			case 11: 
				cout<<"PostOrder Traversal"<<endl;
				PostOrder_Traversal(tree_root);
				cout<<endl;
			break;
			default:
				cout<<"Exiting"<<endl;
				return 0;
		}
	}while(true);
	return 0;
}*/
