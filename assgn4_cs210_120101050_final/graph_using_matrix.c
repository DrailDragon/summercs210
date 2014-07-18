#include "auxiliary.h"
int** G=NULL;
int node_count=0;
bool add_edge(int v1,int v2){
	if(v1>node_count-1 || v2>node_count-1){
		printf("Enter a node value less than:%d or increment graph size\n",node_count);
		return false;
	}
	if(v1==v2){
		printf("No self loops are allowed\n");
		return false;
	}
	if(G[v1][v2]==1 && G[v2][v1]==1){
		printf("Edge between nodes:%d and %d already exists\n",v1,v2);	
		return false;	
	}
	G[v1][v2]=1;
	G[v2][v1]=1;
	printf("A new edge added between nodes:%d and %d\n",v1,v2);
	return true;
}
bool delete_edge(int v1,int v2){
	if(v1>node_count-1 || v2>node_count-1){
		printf("Enter a node value less than:%d or increment graph size\n",node_count);
		return false;
	}
	if(G[v1][v2]==0 || G[v2][v1]==0){
		printf("Edge between nodes:%d and %d doesn't exist\n",v1,v2);	
		return false;	
	}
	G[v1][v2]=0;
	G[v2][v1]=0;
	printf("edge between nodes:%d and %d deleted\n",v1,v2);
	return true;
}
bool bfs(int s){
	if(s>node_count-1){
		printf("Enter a node value less than:%d or increment graph size\n",node_count);
		return false;
	}
	int i,root,j;
	bool visited[node_count];
	for(i=0;i<node_count;i++)
	visited[i]=false;
	int depth[node_count];
	for(i=0;i<node_count;i++)
		depth[i]=0;
	int ancestor[node_count];
	int q[node_count+1],tail=1,head=1;
	enqueue(q,&head,&tail,s,node_count+1);
	visited[s]=true;
	ancestor[s]=-1;
	while(tail!=head){
		root=dequeue(q,&head,&tail,node_count+1);
		printf("vertex is:%d\tancestor is %ddepth from source vertex is:%d\n",root,ancestor[root],depth[root]);
		for(i=0;i<node_count;i++){
			if(G[root][i]==1 && !visited[i]){
				enqueue(q,&head,&tail,i,node_count+1);
				visited[i]=true;
				ancestor[i]=root;
				depth[i]=depth[root]+1;
			}
		}
	}
		return true;
}
bool dfs(int s){
	if(s>node_count-1){
		printf("Enter a node value less than:%d or increment graph size\n",node_count);
		return false;
	}
	int i,root;
	bool visited[node_count];
	for(i=0;i<node_count;i++)
	visited[i]=false;
	int depth[node_count];
	for(i=0;i<node_count;i++)
		depth[i]=0;
	int ancestor[node_count];
	int stk[node_count],top=-1;
	push(stk,&top,s,node_count);
	ancestor[s]=-1;
	while(top!=-1){
		root=pop(stk,&top,node_count);
		if(!visited[root]){
		visited[root]=true;
		printf("vertex is:%d\tancestor is %ddepth from source vertex is:%d\n",root,ancestor[root],depth[root]);
		}	
		for(i=0;i<node_count;i++){
			if(G[root][i]==1 && !visited[i]){
				push(stk,&top,i,node_count);
				ancestor[i]=root;
				depth[i]=depth[root]+1;
			}
		}
	}
		return true;
}
/*********this section contains optional functions if graph is disconnected the dfs and bfs for the whole graph with its number of components********************/
bool aux_bfs(int s,bool* visited,int* ancestor,int* depth){
	if(s<0 || s>node_count-1){
		printf("Please enter a valid source vertex less than %d\n",node_count);
		return false;
	}
	int q[node_count+1],tail=1,head=1,v,i;
	enqueue(q,&head,&tail,s,node_count+1);
	visited[s]=true;
	ancestor[s]=-1;
	while(tail!=head){
		v=dequeue(q,&head,&tail,node_count+1);
		printf("vertex is:%d\tancestor is %ddepth from source vertex is:%d\n",v,ancestor[v],depth[v]);
		for(i=0;i<node_count;i++){
			if(G[v][i]==1 && !visited[i]){
				enqueue(q,&head,&tail,i,node_count+1);
				visited[i]=true;
				ancestor[i]=v;
				depth[i]=depth[v]+1;
			}
		}
	}
	return true;
}
bool bfs_withcomp(int s){
	if(s<0 || s>node_count-1){
		printf("Please enter a valid source vertex less than %d\n",node_count);
		return false;
	}
	int i,num_comp=1,unvisited=-1;
	int depth[node_count],ancestor[node_count];
	bool visited[node_count],flag=0;
	for(i=0;i<node_count;i++)
		depth[i]=0;
	for(i=0;i<node_count;i++)
		visited[i]=false;
	printf("Component 1:\n");
	flag=aux_bfs(s,visited,ancestor,depth);
	while(flag && unvisited!=node_count-1){
		for(i=0;i<node_count;i++){
			if(!visited[i])
				unvisited=i;
		}
		if(unvisited!=-1){
			printf("Component %d:\n",num_comp+1);
			flag=aux_bfs(unvisited,visited,ancestor,depth);
			if(flag)
			num_comp++;
			}else{
			flag=0;
			}
		unvisited=-1;
	}
	printf("Number of components in the graph is %d\n",num_comp);
	return true;
	
}
bool aux_dfs(int s,bool*visited,int* ancestor,int* depth){
	if(s<0 || s>node_count-1){
		printf("Please enter a valid source vertex less than %d\n",node_count);
		return false;
	}
	int stk[node_count],top=-1,v,i;
	push(stk,&top,s,node_count);
	ancestor[s]=-1;
	while(top!=-1){
		v=pop(stk,&top,node_count);
		if(!visited[v]){
		visited[v]=true;
		printf("vertex is:%d\tancestor is %ddepth from source vertex is:%d\n",v,ancestor[v],depth[v]);
		}	
		for(i=0;i<node_count;i++){
			if(G[v][i]==1 && !visited[i]){
				push(stk,&top,i,node_count);
				ancestor[i]=v;
				depth[i]=depth[v]+1;
			}
		}
	}
	return true;
}
bool dfs_withcomp(int s){
	if(s<0 || s>node_count-1){
		printf("Please enter a valid source vertex less than %d\n",node_count);
		return false;
	}
	int i,num_comp=1,unvisited=-1;
	int depth[node_count],ancestor[node_count];
	bool visited[node_count],flag=0;
	for(i=0;i<node_count;i++)
		depth[i]=0;
	for(i=0;i<node_count;i++)
		visited[i]=false;
	printf("Component 1:\n");
	flag=aux_dfs(s,visited,ancestor,depth);
	while(flag && unvisited!=node_count-1){
		for(i=0;i<node_count;i++){
			if(!visited[i])
				unvisited=i;
		}
		if(unvisited!=-1){
			printf("Component %d:\n",num_comp+1);
			flag=aux_dfs(unvisited,visited,ancestor,depth);
			if(flag)
			num_comp++;	
			}else{
			flag=0;
			}
		unvisited=-1;
		
	}
	printf("Number of components in the graph is %d\n",num_comp);
	return true;
} 

/******end optional section ********/
bool delete_graph(){
	int i;
 	for(i=0;i<node_count;i++){
		free(G[i]);
	}
	free(G);
	if(!G){
		printf("Existing graph deleted\n");
		return true;
	}
	printf("Error deleting existing gaph,try again...\n");
	return false;
}
bool increment_graphsize(int newsize){
	if(newsize<=node_count){
		printf("Please enter the new size greater than %d\n",node_count);
		return false;
	}
	int i,j;
	G=(int**)realloc(G,newsize*sizeof(int*));
	for(i=0;i<newsize;i++){
		G[i]=(int*)realloc(G[i],newsize*sizeof(int));
		}
	if(G){
		for(i=0;i<node_count;i++){
			for(j=node_count;j<newsize;j++)
				G[i][j]=0;
		}
		for(i=node_count;i<newsize;i++){
			for(j=0;j<newsize;j++)
				G[i][j]=0;
		}
		node_count=newsize;
		printf("graph size incremented to %d\n",node_count);
		return true;
	}
	printf("Error reallocating graph of new size:%d\n",newsize);
	return false;
}
bool print_graph_matrix(){
		int k,i,j;
		printf("\t");
	for(k=0;k<node_count;k++){
		printf("%d\t",k);
		}
		printf("\n");
	for(k=0;k<node_count;k++){
		printf(" _ _\t");
		}
		printf("_\n");
	for(i=0;i<node_count;i++){
		printf("%d|\t",i);
		for(j=0;j<node_count;j++)
			printf("%d\t",G[i][j]);
		printf("\n");
	}
return true;
}
int main(){
int choice,i,j;
int v1,v2;
	do{
		printf("Choose the option:\n");
		printf("1.Create new empty graph\n");
		printf("2.Add edge\n");
		printf("3.Delete edge\n");
		printf("4.bfs\n");
		printf("5.dfs\n");
		printf("6.Increment graph-size\n");
		printf("7.Print graph matrix\n");	
		printf("Enter any other integer to exit\n");
		printf("8.bfs with number of components\n");
		printf("9.dfs with number of components\n");
		scanf("%d",&choice);
		printf("You entered:%d\n",choice);
		switch(choice){
			case 1:
			if(G)
			 choice=delete_graph();
			if(choice){
				printf("Enter the initial number of nodes you want in the graph\n");
				scanf("%d",&node_count);
				G=(int**)malloc(node_count*sizeof(int*));
				if(G){
					printf("Empty graph with 0 edges and %d vertices created\n",node_count);
					for(i=0;i<node_count;i++){
					G[i]=(int*)malloc(node_count*sizeof(int));
					}
					for(i=0;i<node_count;i++){
						for(j=0;j<node_count;j++)
						G[i][j]=0;
					}
					break;
				}
				printf("Error allocating memory for empty graph of size:%d,try again...\n",node_count);
				break;	
			}
			printf("Error deleting existing graph\n");
			break;
			case 2:
				if(!G){
					printf("First Create a new empty graph\n");
					break;
				}
				printf("Enter the two vertices to add edge between them\n");
				scanf("%d%d",&v1,&v2);
				add_edge(v1,v2);
				break;
			case 3:
				if(!G){
					printf("First Create a new empty graph\n");
					break;
				}
				printf("Enter the two vertices to delete edge between them\n");
				scanf("%d%d",&v1,&v2);
				delete_edge(v1,v2);
				break;
			case 4:
				if(!G){
					printf("First Create a new empty graph\n");
					break;
				}
				printf("Enter the vertex to start bfs from\n");
				scanf("%d",&v1);
				bfs(v1);
				break;
			case 5:
				if(!G){
					printf("First Create a new empty graph\n");
					break;
				}
				printf("Enter the vertex to start dfs from\n");
				scanf("%d",&v1);
				dfs(v1);
				break;
			case 6:
				if(!G){
					printf("First Create a new empty graph\n");
					break;
				}
				printf("Enter the new size of the graph you want\n");
				scanf("%d",&choice);
				increment_graphsize(choice);
				break;
			case 7:
				if(!G){
					printf("First Create a new empty graph\n");
					break;
				}
				print_graph_matrix();
				break;
			case 8:
				if(!G){
					printf("First Create a new empty graph\n");
					break;
				}
				printf("Enter the vertex to start bfs from\n");
				scanf("%d",&v1);
				bfs_withcomp(v1);
				break;
			case 9:
				if(!G){
					printf("First Create a new empty graph\n");
					break;
				}
				printf("Enter the vertex to start dfs from\n");
				scanf("%d",&v1);
				dfs_withcomp(v1);
				break;
			default:
				printf("Exiting\n");
				return 0;
		}
	}while(true);
return 0;
}
