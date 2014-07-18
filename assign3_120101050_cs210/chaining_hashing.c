#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<stdbool.h>
#define EMPTYKEY " "
#define M 20/***hash-value***/
typedef struct elem* elem_ptr;
typedef struct elem{
	char* key;
	char* value;
	elem_ptr next;
}elem;
typedef struct HT{
	elem* el;
}HT;
HT* ht=NULL;
elem* elem1=NULL;
int table_size=M;
int elem_count=0;
/****hash1****/
int h(char* k){
	int hash=0;
	while(*k){
		if(*k=='\0')
		break;
		hash=hash+*k++;
	}
	return hash%M;
}
bool insert(elem* el1){
	char* k = el1->key;
	int home,i;
	int pos=home=h(k);
	printf("Home pos:%d\n",home);
	if(ht[pos].el==NULL)
	{
	ht[pos].el=el1;
	printf("key:%s\tvalue:%s\tinserted at index\t%d\n",ht[pos].el->key,ht[pos].el->value,pos);
	elem_count+=1;
	return true;
	}else{
		elem* tmp=ht[pos].el;
		if(strcmp(tmp->key,k)==0)
		{
			printf("Duplicate key exists,can't be inserted\n");
			return false;
		}	
		while(tmp->next!=NULL)
		{
			tmp=tmp->next;
			if(strcmp(tmp->key,k)==0)
				{
				printf("Duplicate key exists,can't be inserted\n");
				return false;
				}	
		}
		tmp->next=el1;
		tmp=tmp->next;
		printf("key:%s\tvalue:%s\tinserted at index\t%d\n",tmp->key,tmp->value,pos);
		elem_count+=1;
		return true;
	}
}
bool search(char* k){
	int home,i;
	int pos=home=h(k);
	if(ht[pos].el!=NULL)
		{
		if(strcmp(ht[pos].el->key,k)==0){
			printf("Element with key:%s\tvalue:%s\t Found at bucket number:%d\n",ht[pos].el->key,ht[pos].el->value,pos+1);
			return true;
			}
		elem* tmp=ht[pos].el;
		while(tmp->next!=NULL)
			{
				tmp=tmp->next;
				if(strcmp(tmp->key,k)==0){
				printf("Element with key:%s\tvalue:%s\t Found at bucket number:%d\n",tmp->key,tmp->value,pos);
				return true;
				}
			}
		}
	printf("Element with key:%s\tnot found\n",k);
	return false;
}
bool delete_elem(char* k){
	int home,i;
	int pos=home=h(k);
	if(ht[pos].el!=NULL)
		{
		if(strcmp(ht[pos].el->key,k)==0){
			printf("key:%s\tvalue:%s\tat bucket number:%d\tdeleted\n",ht[pos].el->key,ht[pos].el->value,pos+1);
			elem* t=ht[pos].el;
			ht[pos].el=ht[pos].el->next;
			t->next=NULL;
			free(t);
			t=NULL;
			elem_count--;
			return true;
			}
		elem* tmp=ht[pos].el;
		while(tmp->next!=NULL)
			{
				elem* t=tmp;
				tmp=tmp->next;
				if(strcmp(tmp->key,k)==0){
				printf("key:%s\tvalue:%s\tat bucket number:%d\tdeleted\n",tmp->key,tmp->value,pos+1);
				t->next=tmp->next;
				if(tmp->next!=NULL)
				tmp->next=NULL;
				free(tmp);
				tmp=NULL;
				elem_count--;
				return true;
				}
			}
		}
	printf("Element with key:%s\t not found\n",k);
	return false;
}
bool print_key_value_pairs(){
	if(elem_count==0)
	{
	printf("Table empty\n");
	return false;
	}
	int i;
	for(i=0;i<table_size;i++)
	{
		printf("Bucket Number: %d\n",i+1);
		if(ht[i].el)
		{
			printf("key:%s\tvalue:%s\n",ht[i].el->key,ht[i].el->value);
			elem* tmp=ht[i].el;
			while(tmp->next!=NULL)
			{
				tmp=tmp->next;
				printf("key:%s\tvalue:%s\n",tmp->key,tmp->value);
			}
			printf("\n");
		}
	else
	printf("EMPTYKEY\n");
	}
	return true;
}

int main(int argc, char *argv[]) {
	int ch;
	int k_size=0,val_size=0;
	char* k=NULL,*val=NULL;
	do{
		printf("Choose the option:\n");
		printf("1.Create new table\n");
		printf("2.Insert new element\n");
		printf("3.Search element\n");
		printf("4.Get hashed value of a key\n");
		printf("5.Delete table\n");
		printf("6.Print key-value pairs of the table\n");
		printf("7.Delete element\n");
		scanf("%d",&ch);
		printf("You entered\t%d\n",ch);
		switch(ch){
			case 1:
				if(ht)
				free(ht);
				ht=(HT*)malloc(table_size*sizeof(HT));
				if(!ht){
					printf("Error allocating memory for table\n");
					break;
				}else
				printf("Empty Table of size \t%d\tcreated\n",table_size);
				break;
			case 2:
				if(!ht){
					printf("First create empty table\n");
					break;
				}
				/*printf("Enter the maximum sizes of key and value\n");
				scanf("%d%d",&k_size,&val_size);*/
				k=(char*)malloc((k_size+1)*sizeof(char));
				val=(char*)malloc((val_size+1)*sizeof(char));
				if(k && val){
						printf("Enter key-value pair to insert\n");
						scanf("%s%s",k,val);
						elem1=(elem*)malloc(sizeof(elem));
						if(!elem1){
							printf("Error allocating memory for new  element\n");
							break;
						}
						elem1->key=k;
						elem1->value=val;
						elem1->next=NULL;
						insert(elem1);
					break;
				}else{
				printf("Error allocating memories for key-value pair\n");
				break;
			    }
			case 3:
				 if(!ht){
					printf("First create empty table\n");
					break;
					}
				/*printf("Enter the maximum size of key to be searched\n");
				scanf("%d",&k_size);*/
				k=(char*)malloc((k_size+1)*sizeof(char));
				printf("Enter key to search for element\n");
				scanf("%s",k);
				search(k);
				break;
			case 4:
				 if(!ht){
					printf("First create empty table\n");
					break;
					}
				/*printf("Enter the maximum size of key \n");
				scanf("%d",&k_size);*/
				k=(char*)malloc((k_size+1)*sizeof(char));
				printf("Enter key to get its hashed value\n");
				scanf("%s",k);
				int hash=0;
				printf("Hashed Value of the key \t%s\t is\t%d\n",k,h(k));
				break;
			case 5: 
				if(!ht){
					printf("First create empty table\n");
					break;
					}
				if(ht){
				for(ch=0;ch<table_size;ch++)
				{
				if(ht[ch].el!=NULL)
					{
					   if(ht[ch].el->key!=NULL)
						free(ht[ch].el->key);
					   if(ht[ch].el->value!=NULL)
						free(ht[ch].el->value);
					 ht[ch].el=NULL;
					}
				}
				ht=NULL;
				      }
				if(ht){
					printf("Error deleting table,Try again...\n");
					break;
				}else{
					elem_count=0;
					table_size=0;
					printf("Table deleted\n");
					break;
				}
			case 6:
				if(!ht){
					printf("First create empty table\n");
					break;
					}
				print_key_value_pairs();
				break;
			case 7:
				if(!ht){
					printf("First create empty table\n");
					break;
					}
				/*printf("Enter the maximum size of key to be deleted\n");
				scanf("%d",&k_size);*/
				k=(char*)malloc((k_size+1)*sizeof(char));
				printf("Enter key to be deleted for element\n");
				scanf("%s",k);
				delete_elem(k);
				break;
			default:
				printf("Exiting.\n");
				return 0;
		}
	}while(true);
	return 0;
}
