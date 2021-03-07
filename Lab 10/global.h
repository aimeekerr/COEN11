#define NODE struct node
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
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
extern LIST heads[4]; //this initializes the array of the head and tail struct
extern pthread_mutex_t mutex;
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
void *autosave(void *arg);
void read_autosave(char *arg);
