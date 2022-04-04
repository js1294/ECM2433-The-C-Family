#ifndef __QUEUE__
#define __QUEUE__ 1

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/*----- structure definition -----*/

struct Node
{
   int data;
   struct Node *next;
};

typedef struct Node NODE;

struct Queue
{
   NODE *front;
   NODE *back;
};

typedef struct Queue QUEUE;

/*----- function prototypes -----*/

extern QUEUE* createQueue();
extern void   enqueue    (QUEUE *, int);
extern char   dequeue    (QUEUE *);
extern void   printQueue (NODE *);
extern void   emptyQueue (QUEUE *);
extern int    isEmpty    (QUEUE *);

#endif