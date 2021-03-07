#include "global.h"
void insert(char name1[20], int size1) //this funtion inserts a new node into the list
{
	int dup;
	int index;
	NODE *temp;
	dup=duplicate(name1);
	if(dup==1)
	{
		temp=(NODE*)malloc(sizeof(NODE));
		strcpy(temp->name,name1);
		temp->size=size1;
		if(size1==1 || size1==2) //this next few set of lines is to check which index the entry belongs in
		{
			index=0;
		}
		else if(size1==3 || size1==4)
		{
			index=1;
		}
		else if(size1==5 || size1==6)
		{
			index=2;
		}
		else
		{
			index=3;
		}
		if(heads[index].head==NULL) //runs if there is nothing in the list
		{
			temp->next=NULL;
			heads[index].head=temp;
			heads[index].tail=heads[index].head;
		}
		else //runs if there is something in the list already
		{
			temp->next=NULL;
			heads[index].tail->next=temp;
			heads[index].tail=heads[index].tail->next;
		}
		return;
	}
	else if(dup==0)
	{
		printf("That name is already taken!\n");
		return;
	}
}
void remove1() //this function deletes the specified node and moves the list around it
{
	int i;
	int index;
	int size1;
	NODE *p,*q;
	int round1=0;
	printf("Size of group?\n");
	scanf("%d",&size1);
	if(size1==1 || size1==2)
	{
		index=0;
	}
	else if(size1==3 || size1==4)
	{
		index=1;
	}
	else if(size1==5 || size1==6)
	{
		index=2;
	}
	else
	{
		index=3;
	}
	for(i=0;i<=index;i++) //this is a for loop to check for and then  remove the specified value
	{
		p=heads[i].head;
		q=p;
		while(p!=NULL)
		{
			if(size1>=p->size)
			{
				printf("%s:%d removed\n",p->name,p->size);
				if(p->next==NULL && heads[i].head!=heads[i].tail) //runs if element found is at the end and is not the only thing in the list
				{
					q->next=NULL;
					free(p);
					heads[i].tail=q;
					return;
				}
				else if(p->next==NULL && heads[i].head==heads[i].tail) //runs if element found is the only element in the list
				{
					heads[i].head=NULL;
					heads[i].tail=NULL;
					free(p);
					return;
				}
				else if(p==heads[i].head && heads[i].head!=heads[i].tail) //runs if the element is the first element in the list but is not the only one in the list
				{
					heads[i].head=heads[i].head->next;
					free(p);
					return;
				}
				else //runs if the element found is in the middle of the list
				{
					q->next=p->next;
					free(p);
					return;
				}
			}
			if(round1==0) //flag to check if it is the first round in order to make sure the q pointer is one behind the p pointer
			{
				p=p->next;
				round1++;
			}
			else //runs if it is not the first rounde
			{
				p=p->next;
				q=q->next;
			}
		}
	}
	printf("There are no spots available\n");
	return;
}
void list() //this function lists the entries
{
	int i;
	NODE *p;
	int check;
	for(i=0;i<4;i++)
	{
		p=heads[i].head;
		if(heads[i].head==NULL)
		{
			check++;
		}
		else
		{
			while(p!=NULL)
			{
				printf("- %s:%d\n",p->name,p->size);
				p=p->next;
			}
		}
	}
	if(check==4)
		printf("The List is empty!\n");
	return;
}
int duplicate(char *name1) //this function checks for duplicate names
{
	int dupl;
	NODE *p;
	int i;
	for(i=0;i<4;i++)
	{
		p=heads[i].head;
		while(p!=NULL)
		{
			dupl=strcmp(name1,p->name);
			if(dupl==0)
			{
				return 0;
			}
			p=p->next;
		}
	}
	return 1;
}
void checksize() //This function lists the entires with less than or equal to the specified number
{
	int size1;
	NODE *p;
	int i;
	int check=0;
	printf("Size?\n");
	scanf("%d",&size1);
	printf("The groups with less than %d people are:\n",size1);
	for(i=0;i<4;i++)
	{
		p=heads[i].head;
		while(p!=NULL)
		{
			if(size1>=p->size)
			{
				printf("- %s:%d\n",p->name,p->size);
				check=1;
			}
			p=p->next;
		}
	}
	if(check==0)
		printf("N/A\n");
}
void free1(NODE *p) //this function frees all the data after the user exits the program
{
	if(p==NULL)
	{
		return;
	}
	else
	{
		free1(p->next);
		free(p);
	}
}
void reverselist(NODE *p) //this function reverses the order of the list
{
	if(p==NULL)
	{
		return;
	}
	else
	{
		reverselist(p->next);
		printf("- %s:%d\n",p->name,p->size);
		return;
	}
}
void reversenames(char *q) //this function reverses the actual order of the lettering in the names
{
	if(*q=='\0')
	{
		return;
	}
	else
	{
		reversenames(q+1);
		printf("%c",*q);
	}
}
