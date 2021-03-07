#include "global.h"
LIST heads[4]={{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL}}; //this initializes the array of the head and tail struct with no values inside
pthread_mutex_t mutex;
int main(int argc, char *argv[])
{
	if(argc<3) //this if statement checks how many arguments there are to see if there is a file
	{
		printf("Invalid\n");
		return 1;
	}
	pthread_mutex_init(&mutex, NULL);
	pthread_t thr;
	pthread_create(&thr, NULL,autosave,(void *) argv[2]);
	readfile(argv[1],atoi(argv[3])); //this runs at the start to check if there is an existing file and if there is it puts the data back into the program
	for(;;) //This is a forever loop to keep the program going until it is stopped
	{
		printf("- (1) Inset name and size of group to list\n");
		printf("- (2) Remove\n");
		printf("- (3) Show the list\n");
		printf("- (4) Check groups sizes\n");
		printf("- (5) Show list reversed\n");
		printf("- (6) Show names reversed\n");
		printf("- (7) Check auto-save file\n");
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
				pthread_mutex_lock(&mutex);
				insert(name1,size1);
				pthread_mutex_unlock(&mutex);
				break;
			}
			case 2:
			{
				pthread_mutex_lock(&mutex);
				remove1();
				pthread_mutex_unlock(&mutex);
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
			case 7:
			{
				read_autosave(argv[2]);
				break;
			}
			case 0:
			{
				pthread_mutex_lock(&mutex);
				pthread_cancel(thr);
				writefile(argv[1],atoi(argv[3]));
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

