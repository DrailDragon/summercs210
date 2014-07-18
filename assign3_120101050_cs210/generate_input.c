#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
char* gen_string(char* str,int siz){
	static char seed[]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	str=(char*)malloc(sizeof(char));
	int i;
	for(i=0;i<siz;i++)
	     str[i]=seed[rand()%strlen(seed)];
	return str;
}
int main(){
	int s;
	char* str[20];
	char* st=NULL;
	FILE* f=fopen("input_gen.txt","w");
	fprintf(f,"1\n");
	srand(time(NULL));
	for(s=1;s<21;s++){
	fprintf(f,"2\n");
	str[s-1]=gen_string(st,s);
	fprintf(f,"%s\n",str[s-1]);
	fprintf(f,"%s\n",gen_string(st,s+1));
	}
	fprintf(f,"6\n");
	for(s=0;s<20;s++){
	fprintf(f,"3\n");
	fprintf(f,"%s\n",str[rand()%20]);
	}
	fprintf(f,"6\n");
	for(s=0;s<10;s++)
	{
	 fprintf(f,"4\n");
	 fprintf(f,"%s\n",str[rand()%20]);
	}
	fprintf(f,"6\n");
	for(s=0;s<10;s++)
	{
	 fprintf(f,"7\n");
	 fprintf(f,"%s\n",str[rand()%20]);
	}
	fprintf(f,"6\n");
	fprintf(f,"5\n");
	fprintf(f,"6\n");
	fprintf(f,"6534534\n");
	fclose(f);
return 0;
}
