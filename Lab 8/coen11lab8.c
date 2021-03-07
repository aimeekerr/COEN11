/* Aimee Kerr
 * Coen 11
 * Feb 28 2019
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
void readfile();
void writefile();
int duplicate(char *);
void reverselist();
void reversenames();
int main(int argc, char *argv[])
{
	if(argc==1) //this if statement checks how many arguments there are to see if there is a file
	{
		printf("Invalid\n");
		return 1;
	}
	readfile(argv[1]); //this runs at the start to check if there is an existing file and if there is it puts the data back into the program
	for(;;) //This is a forever loop to keep the program going until it is stopped
	{
		printf("- (1) Inset name and size of group to list\n");
		printf("- (2) Remove\n");
		printf("- (3) Show the list\n");
		printf("- (4) Check groups sizes\n");
		printf("- (5) Show list reversed\n");
		printf("- (6) Show names reversed\n");
		printf("- (0) Quit\n");
		int pick;
		scanf("%d",&pick);
		switch(pick) //This is a switch statement for picking options
		{
			case 1:
			{
				char name1[20];
				int size1;
				printf("Name?\n");
				scanf("%s",name1);
				printf("Size?\n");
				scanf("%d",&size1);
				insert(name1,size1);
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
			case 5:
			{
				NODE *p;
				int i;
				for(i=0;i<4;i++)
				{
					p=heads[i].head;
					reverselist(p);
				}
				break;
			}
			case 6:
			{
				NODE *p;
				char *q;
				int i;
				for(i=0;i<4;i++)
				{
					p=heads[i].head;
					while(p!=NULL)
					{
						printf("- ");
						q=p->name;
						reversenames(q);
						p=p->next;
						printf("\n");
					}
				}
				break;
			}
			case 0:
			{
				writefile(argv[1]);
				int i;
				NODE *p,*q;
				for(i=0;i<4;i++)
				{
					p=heads[i].head;
					free1(p);
				}
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
void readfile(char *argv) //this function inserts the data from the file back into the program
{
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
		while(fscanf(fp,"%s\t%d\n",name1,&size1)==2)
		{
			insert(name1,size1);
		}
	}
	fclose(fp);
	return;
}
void writefile(char *argv) //this function takes the data from the program and saves it into a text file
{
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
				fprintf(fp,"%s\t%d\n",p->name,p->size);
				p=p->next;
			}
		}
	}
	fclose(fp);
	return;
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
