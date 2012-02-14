#include <assert.h>

/* We want the extra information from these definitions */
#ifndef __USE_GNU
#define __USE_GNU
#endif /* __USE_GNU */
#include <stdlib.h>

#include "ULT.h"


void initQueue()
{
	queue = list_new();
	tids_available[0] = 1;
}

//Dr Norman's thread root function
stub(void (*root)(void *), void *arg) 
{
	// thread starts here 
	Tid ret; 
	root(arg); // call root function 
	ret = ULT_DestroyThread(ULT_SELF) 
	assert(ret == ULT_NONE); // we should only get here if we are the last thread. 
	exit(0); // all threads are done, so process should exit

}

Tid 
ULT_CreateThread(void (*fn)(void *), void *parg)
{
		
  //assert(0); /* TBD */
  return ULT_FAILED;
}



Tid ULT_Yield(Tid wantTid)
{

  //first call to yield, so no other thread to yield to
  if (firstCalled == 0)
  {
	firstCalled = 1;
	initQueue();
	return ULT_NONE;
  }

  if (wantTid >= ULT_MAX_THREADS || wantTid < -2)
	return ULT_INVALID;

  //continue execution of caller
  else if (wantTid == ULT_SELF)
  {
	//return tidRunning;
	//ThrdCtlBlk self_TCB = malloc(sizeof(ThrdCtlBlk));
	//self_TCB->num = tidRunning;
	//getContext( &(self_TCB->tContext) );

	//manipulate some pointers (stack ptr, etc)

	//list_add_element(queue, tidRunning);
	//list_remove_element(<self's thdctlblk>);
  }

  //invoke thread on ready queue
  else if (wantTid == ULT_ANY)
  {
	if (queue->head == NULL)
		return ULT_NONE;
	
	else
	{
		ThrdCtlBlk* switch_TCB = list_remove_element;
		setcontext(&switch_TCB);
		
	} 
  }
  
  //assert(0); /* TBD */
  return ULT_FAILED;

}


Tid ULT_DestroyThread(Tid tid)
{
  assert(0); /* TBD */
  return ULT_FAILED;
}





