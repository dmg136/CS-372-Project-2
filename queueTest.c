#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"

void main()
{
	queue* myQueue = list_new();
	assert(myQueue);
	assert(myQueue->head->num == 0);
	assert(myQueue->tail->num == 0);
	
	printf("test no queue passed in\n");
	int ret = list_remove_element(NULL, 9);
	assert (ret == ULT_NONE);
	
	/*
	printf("\ntest empty list\n");
	ret = list_remove_element(myQueue, 12);
	assert (ret == ULT_NONE);
	*/
	
	printf("\ntest add to invalid queue\n");
	ret = list_add_element(NULL);
	assert (ret == ULT_FAILED);
	
	printf("\ntest add 1 element\n");
	ret = list_add_element(myQueue);
	printf("first element after tid 0: %d\n", ret);
	assert (ULT_isOKRet(ret));
	
	printf("\ninside queue, %d elements\n", myQueue->numTCB);
	list_print(myQueue);
	
	printf("\ntest add another element\n");
	ret = list_add_element(myQueue);
	printf("second element after tid 0: %d\n", ret);
	assert (ULT_isOKRet(ret));
	
	printf("\ninside queue, %d elements\n", myQueue->numTCB);
	list_print(myQueue);
	
	printf("\ntest remove third element\n");
	ret = list_remove_element(myQueue, 2);
	printf("second element's tid: %d\n", ret);
	assert (ULT_isOKRet(ret));
	
	printf("\ntest remove second element\n");
	ret = list_remove_element(myQueue, 1);
	printf("first element's tid: %d\n", ret);
	assert (ULT_isOKRet(ret));
}