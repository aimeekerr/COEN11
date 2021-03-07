#include "global.h"
void readfile(char *argv,int key) //this function inserts the data from the file back into the program
{
	char buffer[200];
	char *q;
	int size1;
	char name1[20];
	FILE *fp;
	fp=fopen(argv,"r");
	if(fp==NULL)
	{
		printf("No file found\n");
		return;
	}
	else
	{
		fseek(fp,24,SEEK_SET);
		while(fgets(buffer,200,fp)!=NULL)
		{
			q=buffer;
			while(*q!='\n')
			{
				*q^=key;
				q++;
			}
			sscanf(buffer,"%s\t%d",name1,&size1);
			insert(name1,size1);
		}
	}
	fclose(fp);
	return;
}
void writefile(char *argv,int key) //this function takes the data from the program and saves it into a text file
{
	char *q;
	char buffer[200];
	int i;
	FILE *fp;
	NODE *p;
	fp=fopen(argv,"w");
	fprintf(fp,"Name   Size\n");
	fprintf(fp,"___________\n");
	if(fp==NULL)
	{
		printf("Error\n");
		return;
	}
	else
	{
		for(i=0;i<4;i++)
		{
			p=heads[i].head;
			while(p!=NULL)
			{
				sprintf(buffer,"%s\t%d",p->name,p->size);
				q=buffer;
				while(*q!='\0')
				{
					*q^=key;
					q++;
				}
				fprintf(fp,"%s\n",buffer);
				p=p->next;
			}
		}
	}
	fclose(fp);
	return;
}
void *autosave(void *arg)//this function is a thread autosaves the list into a binary file every 15 seconds
{
	for(;;)
	{
		sleep(15);
		printf("saving...\n");
		pthread_mutex_lock(&mutex);
		int i;
		FILE *fp;
		NODE *p;
		fp=fopen(arg,"wb");
		if(fp==NULL)
		{
			return NULL;
		}
		else
		{
			for(i=0;i<4;i++)
			{
				p=heads[i].head;
				while(p!=NULL)
				{
					fwrite(p,sizeof(NODE),1,fp);
					p=p->next;
				}
			}
		}
		fclose(fp);
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}
void read_autosave(char *arg)//this function prints the data saved in the autosave file
{
	pthread_mutex_lock(&mutex);
	int i;
	NODE stuff;
	FILE *fp;
	fp=fopen(arg,"rb");
	if(fp==NULL)
	{
		printf("File is empty!\n");
		pthread_mutex_unlock(&mutex);
		return;
	}
	else
	{
		while(fread(&stuff,sizeof(NODE),1,fp)>0)
		{
			printf("Name: %s Size: %d\n",stuff.name,stuff.size);
		}
	}
	fclose(fp);
	pthread_mutex_unlock(&mutex);
	return;
}
