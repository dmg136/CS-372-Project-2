/*
int main(void)
{
  struct ThrdCtlBlk*  mt = NULL;
  
  mt = list_new();
  list_add_element(mt, 1);
  list_add_element(mt, 2);
  list_add_element(mt, 3);
  list_add_element(mt, 4); 
  
  list_print(mt);

  list_remove_element(mt);
  list_print(mt);

  list_free(mt);   // always remember to free() the malloc()ed memory
  free(mt);        // free() if list is kept separate from free()ing the structure, I think its a good design
  mt = NULL;      // after free() always set that pointer to NULL, C will run havon on you if you try to use a dangling pointer

  list_print(mt);

  return 0;
}
*/

#include <assert.h>
#include "queue.h"

Tid available_tid()
{
	int find, pos;
	for (pos = 0; pos < ULT_MAX_THREADS; pos++)
	{
		if (tids_available[pos] == 0)
		{
			find = pos;
			tids_available[pos] = 1;
			break;
		}
	}
	
	if (find >= ULT_MAX_THREADS)
		return ULT_NOMORE;
	else
		return find;
}

Tid list_add_element(queue* readyQueue)
{

	if ( NULL == readyQueue )
	{
	  printf("don't pass in null as queue structure in list_add\n");
	  return ULT_FAILED;
	}
	
	else if( NULL == readyQueue->head && NULL == readyQueue->tail )
	{
	  
	  int availTid = available_tid();
	  
	  if (availTid == ULT_NOMORE)
		return ULT_NOMORE;

	  ThrdCtlBlk* new_tcb = malloc( sizeof(ThrdCtlBlk) );
	  
	  if( NULL == new_tcb )
	  {
	    fprintf(stderr, "IN %s, %s: new_tcb malloc() failed\n", __FILE__, "list_add");
	    return ULT_NOMEMORY;
	  }

	  
	  new_tcb->num = availTid;
	  new_tcb->prev = NULL;
	  new_tcb->next = NULL;
	  int ret = context_init(&(new_tcb->tContext));
	  assert(ret == 0);
	  
	  readyQueue->head = new_tcb;
	  readyQueue->tail = new_tcb;
	  
	  readyQueue->numTCB++;
	  
	  return availTid;
	}
	else if( NULL == readyQueue->head || NULL == readyQueue->tail )
	{
	  fprintf(stderr, "There is something seriously wrong with your assignment of head/tail to the list\n");
	  return ULT_INVALID;
	}
	else
	{
	  // printf("List not empty, adding element to tail\n");
	  ThrdCtlBlk* new_tcb = malloc( sizeof(ThrdCtlBlk) );
	  
	if( NULL == new_tcb )
	{
	  fprintf(stderr, "IN %s, %s: new_tcb malloc() failed\n", __FILE__, "list_add");
	  return ULT_NOMEMORY;
	}
	  
	  int availTid = available_tid();
	  
	  if (availTid == ULT_NOMORE)
		return ULT_NOMORE;
	  
	  new_tcb->num = availTid;
	  //context_init(&(new_tcb->tContext));
	  new_tcb->prev = readyQueue->tail;
	  new_tcb->next = NULL;
	  
	  readyQueue->tail->next = new_tcb;
	  readyQueue->tail = new_tcb;
	  
	  readyQueue->numTCB++;
	  
	  return availTid;
	}
}

Tid list_remove_head( queue* readyQueue )
{

	if( NULL == readyQueue )
	{
	  printf("ULT_INVALID: No queue passed in, List is empty\n");
	  return ULT_INVALID;
	}
	
	else if( NULL == readyQueue->head && NULL == readyQueue->tail )
	{
	  printf("ULT_INVALID: Head and tail null, List is empty\n");
	  return ULT_INVALID;
	}
	
	else if( NULL == readyQueue->head || NULL == readyQueue->tail )
	{
	  printf("ULT_INVALID: One of the head/tail is empty while other is not \n");
	  return ULT_INVALID;
	}

	ThrdCtlBlk* temp = readyQueue->head;
	
	int tempTid = temp->num;
	
	if ( NULL == temp->prev && NULL == temp->next )
	{
		readyQueue->head = NULL;
		readyQueue->tail = NULL;
	}
	
	else if ( NULL == temp->prev && NULL != temp->next )
	{
		readyQueue->head = temp->next;
		readyQueue->head->prev = NULL;
		temp->next = NULL;
	}
	
	else if ( NULL != temp->prev && NULL != temp->next )
	{
		temp->next->prev = temp->prev;
		temp->prev->next = temp->next;
		temp->prev = NULL;
		temp->next = NULL;
	}
	
	else if ( NULL != temp->prev && NULL == temp->next )
	{
		temp->prev->next = NULL;
		temp->prev = NULL;
	}
	
	readyQueue->numTCB--;	
	tids_available[tempTid] = 0;
	free(temp);
	
	return tempTid;
}

Tid list_remove_element( queue* readyQueue, const Tid tid )
{

	if( NULL == readyQueue )
	{
	  printf("ULT_INVALID: No queue passed in, List is empty\n");
	  return ULT_INVALID;
	}
	else if( NULL == readyQueue->head && NULL == readyQueue->tail )
	{
	  printf("ULT_INVALID: Head and tail null, List is empty\n");
	  return ULT_INVALID;
	}
	else if( NULL == readyQueue->head || NULL == readyQueue->tail )
	{
	  printf("ULT_INVALID: One of the head/tail is empty while other is not \n");
	  return ULT_INVALID;
	}
	
	ThrdCtlBlk* temp = readyQueue->head;
	
	int found = 0;
	int pos = 0;
	while (NULL != temp)
	{
		if (temp->num == tid)
		{
			found = 1;
			break;
		}
		else
		{
			pos++;
			temp = temp->next;
		}
	}
	
	//tid not found
	if (!found)
		return ULT_INVALID;
	
	//change pointers and free found tcb
	
	if ( NULL == temp->prev && NULL == temp->next )
	{
		readyQueue->head = NULL;
		readyQueue->tail = NULL;
	}
	
	else if ( NULL == temp->prev && NULL != temp->next )
	{
		readyQueue->head = temp->next;
		readyQueue->head->prev = NULL;
		temp->next = NULL;
	}
	
	else if ( NULL != temp->prev && NULL != temp->next )
	{
		temp->next->prev = temp->prev;
		temp->prev->next = temp->next;
		temp->prev = NULL;
		temp->next = NULL;
	}
	
	else if ( NULL != temp->prev && NULL == temp->next )
	{
		temp->prev->next = NULL;
		temp->prev = NULL;
	}
	
	readyQueue->numTCB--;
	tids_available[pos] = 0;
	free(temp);
	return tid;
}
  
/*
Tid list_free( ThrdCtlBlk* t )
{
	int freeTid;
	
	ThrdCtlBlk* find = t;
	
	while( t->next )
	{
	  list_remove_element(t);
	}

	return freeTid;
}
*/

queue* list_new(void)
{

	queue* readyQueue = malloc( sizeof(queue) );

	if( NULL == readyQueue )
	{
	  fprintf(stderr, "LINE: %d, new queue malloc() failed\n", __LINE__);
	  return NULL;
	}

	readyQueue->head = readyQueue->tail = NULL;
	readyQueue->numTCB = 1;
	
	tids_available[0] = 1;
	
	//set up initial current running thread
	ThrdCtlBlk *firstTCB = malloc(sizeof(ThrdCtlBlk));
	int ret = getcontext( &(firstTCB->tContext) );
	assert(ret == 0);
	
	firstTCB->num = 0;
	firstTCB->prev = firstTCB->next = NULL;
	
	readyQueue->tidRunning = firstTCB;
	readyQueue->head = firstTCB;
	readyQueue->tail = firstTCB;
	return readyQueue;
}

void list_print( queue* readyQueue )
{

	if( NULL == readyQueue )
	{
		printf("\nlist_print: passed in invalid queue\n");
		return;
	}
	
	else
    {
	  ThrdCtlBlk* temp = readyQueue->head;
	  
	  if (NULL == temp)
	  {
		printf("list is empty\n");
		return;
	  }
	  
	  int pos = 0;
      while ( NULL != temp )
		{
			printf("[%d]: %d ", pos, temp->num);
			pos++;
			temp = temp->next;
		}
    }

	printf("\n----------------------------\n");
}

void list_print_backwards( queue* readyQueue )
{
	if( NULL == readyQueue )
	{
		printf("\nlist_print: passed in invalid queue\n");
		return;
	}
	
	else
    {
	  ThrdCtlBlk* temp = readyQueue->tail;
	  
	  if (NULL == temp)
	  {
		printf("list is empty\n");
		return;
	  }
	  
	  int pos = readyQueue->numTCB - 1;
      while ( NULL != temp )
		{
			printf("[%d]: %d ", pos, temp->num);
			pos--;
			temp = temp->prev;
		}
    }

	printf("\n----------------------------\n");
}

int context_init(ucontext_t* newContext)
{
	return 0;
}

/*
void list_print_element(const ThrdCtlBlk* p )
{
	if( p ) 
    {
      printf("Num = %d\n", p->data);
    }
	else
    {
      printf("Can not print NULL struct \n");
    }
}
*/
