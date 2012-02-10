#include <assert.h>

/* We want the extra information from these definitions */
#ifndef __USE_GNU
#define __USE_GNU
#endif /* __USE_GNU */
#include <stdlib.h>

#include "ULT.h"




Tid 
ULT_CreateThread(void (*fn)(void *), void *parg)
{

	if (firstCalled == 0)
	{
		firstCalled = 1;
		queue = malloc(sizeof(queue));
	}
		
  //assert(0); /* TBD */
  return ULT_FAILED;
}



Tid ULT_Yield(Tid wantTid)
{
  assert(0); /* TBD */
  return ULT_FAILED;

}


Tid ULT_DestroyThread(Tid tid)
{
  assert(0); /* TBD */
  return ULT_FAILED;
}





