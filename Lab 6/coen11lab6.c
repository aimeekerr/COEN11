/* Aimee Kerr
 * Coen 11
 * Feb 7 2019
 */
#define NODE struct node
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct node //This intializes the linked list
{
	char name[20];
	int size;
	NODE *next;
};
typedef struct list //this initializes the struct that contains my head and tail
{
	NODE *head;
	NODE *tail;
}LIST;
LIST heads[4]={{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL}}; //this initializes the array of the head and tail struct with no values inside
void insert();
void remove1();
void list();
void checksize();
void free1();
int duplicate(char *);
int main(void)
{
	for(;;) //This is a forever loop to keep the program going until it is stopped
	{
		printf("- (1) Inset name and size of group to list\n");
		printf("- (2) Remove\n");
		printf("- (3) Show the list\n");
		printf("- (4) Check groups sizes\n");
		printf("- (0) Quit\n");
		int pick;
		scanf("%d",&pick);
		switch(pick) //This is a switch statement for picking options
		{
			case 1:
			{
				insert();
				break;
			}
			case 2:
			{
				remove1();
				break;
			}
			case 3:
			{
				list();
				break;
			}
			case 4:
			{
				checksize();
				break;
			}
			case 0:
			{
				free1();
				return 1;
			}
			default:
			{
				printf("Invalid option\n");
				break;
			}
		}
	}
}
void insert() //this funtion inserts a new node into the list
{
	char name1[20];
	int size1;
	int dup;
	int index;
	NODE *temp;
	printf("Name?\n");
	scanf("%s",name1);
	dup=duplicate(name1);
	if(dup==1)
	{
		temp=(NODE*)malloc(sizeof(NODE));
		strcpy(temp->name,name1);
		printf("Size?\n");
		scanf("%d",&size1);
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
void free1() //this function frees all the data after the user exits the program
{
	int i;
	NODE *p,*q;
	for(i=0;i<4;i++)
	{
		p=q=heads[i].head;
		while(p!=NULL)
		{
			if(p==NULL)
				break;
			else
			{
				p=p->next;
				free(q);
				q=p;
			}
		}
	}
}
