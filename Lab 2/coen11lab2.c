#define SIZE 10
#define length 20
#include <stdio.h>
#include <string.h>
void insert();
void remove1();
void list();
int counter=0;
char name[10][20];
int size[10];
int main(void)
{
	int i;
	for(i=10;i<10;i++)
	{
		name[i][0]='\0';
	}
	for(;;)
	{
		printf("- (1) Inset name and size of group to list\n");
		printf("- (2) Remove\n");
		printf("- (3) Show the list\n");
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
	if(counter==10)
	{
		printf("The list is full!\n");
		return;
	}
	else
	{
		printf("Name?\n");
		scanf("%s",name1);
		strcpy(name[counter],name1);
		printf("Size?\n");
		scanf("%d",&size1);
		size[counter]=size1;
		counter++;
		return;
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
		printf("Size of group?\n");
		scanf("%d",&size1);
		for(i=0;i<10;i++)
		{
			if(size1>=size[i])
			{
				printf("%s:%d removed\n",name[i],size[i]);
				for(j=i;j<counter-1;j++)
				{
					size[j]=size[j+1];
					strcpy(name[j],name[j+1]);
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
	if(counter==0)
	{
		printf("The list is empty\n");
	}
	else
	{
		for(i=0;i<counter;i++)
		{
			printf("- %s:%d\n",name[i],size[i]);
		}
	}
	return;
}
