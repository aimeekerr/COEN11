#define SIZE 10
#define length 20
#include <stdio.h>
#include <string.h>
void insert();
void remove1();
void list();
void checksize();
int duplicate(char *);
int counter=0;
typedef struct entry{
	char name[20];
	int size;
}entry;
entry array[10];
int main(void)
{
	int i;
	for(i=10;i<10;i++)
	{
		array[i].name[0]='\0';
	}
	for(;;)
	{
		printf("- (1) Inset name and size of group to list\n");
		printf("- (2) Remove\n");
		printf("- (3) Show the list\n");
		printf("- (4) Check groups sizes\n");
		printf("- (0) Quit\n");
		int pick;
		scanf("%d",&pick);
		switch(pick)
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
void insert()
{
	char name1[20];
	int size1;
	int dup;
	if(counter==10)
	{
		printf("The list is full!\n");
		return;
	}
	else
	{
		printf("Name?\n");
		scanf("%s",name1);
		dup=duplicate(name1);
		if(dup==1)
		{
			strcpy(array[counter].name,name1);
			printf("Size?\n");
			scanf("%d",&size1);
			array[counter].size=size1;
			counter++;
			return;
		}
		else if(dup==0)
		{
			printf("That name is already taken!\n");
			return;
		}
	}
}
void remove1()
{
	if(counter==0)
	{
		printf("The list is empty");
		return;
	}
	else
	{
		int i;
		int j;
		int size1;
		entry*p=array;
		printf("Size of group?\n");
		scanf("%d",&size1);
		for(i=0;i<10;i++)
		{
			if(size1>=p->size)
			{
				printf("%s:%d removed\n",p->name,p->size);
				for(j=i;j<counter-1;j++)
				{
					p->size=(p+1)->size;
					strcpy(p->name,(p+1)->name);
					p++;
				}
				counter--;
				return;
			}
		}
		printf("There are no spots available\n");
		return;
	}
}
void list()
{
	int i;
	entry*p=array;
	if(counter==0)
	{
		printf("The list is empty\n");
	}
	else
	{
		for(i=0;i<counter;i++)
		{
			printf("- %s:%d\n",p->name,p->size);
			p++;
		}
	}
	return;
}
int duplicate(char *name1)
{
	int dupl;
	int i;
	entry*p=array;
	for(i=0;i<counter;i++)
	{
		dupl=strcmp(name1,p->name);
		if(dupl==0)
		{
			return 0;
		}
		p++;
	}
	return 1;
}
void checksize()
{
	int i;
	int size1;
	entry*p=array;
	if(counter==0)
	{
		printf("The list is empty");
	}
	else
	{
		printf("Size?\n");
		scanf("%d",&size1);
		printf("The groups with less than %d people are:\n",size1);
		for(i=0;i<counter;i++)
		{
			if(size1>=p->size)
			{
				printf("- %s:%d\n",p->name,p->size);
			}
			p++;
		}
	}
}
