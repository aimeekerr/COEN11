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
NODE *head=NULL;
NODE *tail=NULL;
void insert();
void remove1();
void list();
void checksize();
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
		if(head==NULL) //runs if there is nothing in the list
		{
			temp->next=NULL;
			head=temp;
			tail=head;
		}
		else //runs if there is something in the list already
		{
			temp->next=NULL;
			tail->next=temp;
			tail=tail->next;
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
	if(head==NULL) //checks if the list is empty
	{
		printf("The list is empty\n");
		return;
	}
	else
	{
		int size1;
		NODE *p,*q;
		p=q=head;
		int round1=0;
		printf("Size of group?\n");
		scanf("%d",&size1);
		while(p!=NULL)
		{
			if(head==NULL) //runs if list is empty
			{
				printf("The list is empty!\n");
				return;
			}
			if(size1>=p->size)
			{
				printf("%s:%d removed\n",p->name,p->size);
				if(p->next==NULL && head!=tail) //runs if element found is at the end and is not the only thing in the list
				{
					printf("case 1\n");
					q->next=NULL;
					free(p);
					tail=q;
					return;
				}
				else if(p->next==NULL && head==tail) //runs if element found is the only element in the list
				{
					printf("case 2\n");
					head=NULL;
					tail=NULL;
					free(p);
					return;
				}
				else if(p==head && head!=tail) //runs if the element is the first element in the list but is not the only one in the list
				{
					printf("case 3\n");
					head=head->next;
					free(p);
					return;
				}
				else //runs if the element found is in the middle of the list
				{
					printf("case 4\n");
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
			els //runs if it is not the first rounde
			{
				p=p->next;
				q=q->next;
			}
		}
		printf("There are no spots available\n");
		return;
	}
}
void list() //this function lists the entries
{
	NODE *p;
	p=head;
	if(head==NULL)
	{
		printf("The list is empty\n");
	}
	else
	{
		while(p!=NULL)
		{
			printf("- %s:%d\n",p->name,p->size);
			p=p->next;
		}
	}
	return;
}
int duplicate(char *name1) //this function checks for duplicate names
{
	int dupl;
	NODE *p;
	p=head;
	while(p!=NULL)
	{
		dupl=strcmp(name1,p->name);
		if(dupl==0)
		{
			return 0;
		}
		p=p->next;
	}
	return 1;
}
void checksize() //This function lists the entires with less than or equal to the specified number
{
	int size1;
	NODE *p;
	p=head;
	if(head==NULL)
	{
		printf("The list is empty\n");
	}
	else
	{
		printf("Size?\n");
		scanf("%d",&size1);
		printf("The groups with less than %d people are:\n",size1);
		while(p!=NULL)
		{
			if(size1>=p->size)
			{
				printf("- %s:%d\n",p->name,p->size);
			}
			p=p->next;
		}
	}
}
