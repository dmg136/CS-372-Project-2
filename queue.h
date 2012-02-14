#include  <stdio.h>
#include  <stdlib.h>

#include "ULT.h"

typedef struct queue
{
	ThrdCtlBlk *head;
	ThrdCtlBlk *tail;
	ThrdCtlBlk *tidRunning;
	int numTCB;
} queue;

Tid list_add_element(queue* readyQueue);
Tid list_remove_element(queue* readyQueue, const Tid tid);

queue* list_new(void);
void context_init(ucontext_t* newContext);
Tid available_tid();
//ThrdCtlBlk* list_free( struct ThrdCtlBlk* );

void list_print( queue* readyQueue );
//void list_print_element(const struct my_struct* );