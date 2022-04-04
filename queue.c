#include <queue.h>

/*----- Local Function Prototypes -----*/

static NODE *newNode (int data);

/*----- Queue Functions -----*/

/* Creates a new node and return a pointer to it. */
static NODE *newNode (int data)
{
   NODE *n = (NODE *)malloc(sizeof(NODE));
   if (n==NULL)
   {
      printf("Memory allocation error\n");
      fprintf(stderr, "error %d: %s\n", errno, strerror(errno));
      exit(EXIT_FAILURE);
   }
   n->data = data;
   n->next = NULL;
   return n;
}

/* Creates a new queue with a front and back. */
extern QUEUE* createQueue()
{
   QUEUE *q = (QUEUE*)malloc(sizeof(QUEUE));
   if (q==NULL)
   {
      printf("Memory allocation error\n");
      fprintf(stderr, "error %d: %s\n", errno, strerror(errno));
      exit(EXIT_FAILURE);
   }
   q->front = q->back = NULL;
   return q;
}

/* Enqueues a node to the back of the queue. */
extern void enqueue (QUEUE* queue, int data)
{
   NODE *n = newNode(data);

   if (queue->back == NULL)
   {
      queue->front = queue->back = n;
      return;
   }

   queue->back->next = n;
   queue->back = n;
}

/* Dequeues a value of the front of the queue and returns the value. */
extern char dequeue (QUEUE* queue)
{
   int data = 0;

   if (queue->front == NULL)
   {
      printf("Warning: attempting to dequeue from an empty queue.\n");
      printf("Warning: line %d, file %s\n",__LINE__,__FILE__);
      return data;
   }

   NODE* front = queue->front;
   queue->front = queue->front->next;

   if (queue->front == NULL)
   {
      queue->back = NULL;
   }

   data = front->data;
   free(front);
   return data;
}

/* Recursively print out the contents of the queue from the node entered. */
extern void printQueue (NODE *node)
{
   if (node == NULL)
   {
      printf("\n");
      return;
   }
   else
   {
      printf(" %d ", node->data);
      printQueue(node->next);
   }
}

/* Recursively empties the queue, thus freeing all the memory. */
extern void emptyQueue (QUEUE* queue)
{
   if (queue->back == NULL && queue->front == NULL)
   {
      free(queue);
      return;
   }
   else
   {
      dequeue(queue);
      emptyQueue(queue);
   }
}

/* Checks if the queue is empty, returning 1 (True) if it is.*/
extern int isEmpty(QUEUE* queue)
{
   if (queue->back == NULL && queue->front == NULL){
      return 1;
   }
   return 0;
}