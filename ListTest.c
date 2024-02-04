/********************************************************************************* 
* Harman Gidha
* ListTest.c 
*********************************************************************************/ 

#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

int main(int argc, char* argv[])
{
    int X[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    List L = newList();
    freeList(&L);
    assert(L == NULL);

    List l = newList();
    assert(length(l) == 0);
    assert(index(l) == -1);

    List a = newList();
    
    for(int i=0; i<=20; i++){
      append(l, &X[i]);
      prepend(a, &X[i]);
   }
    assert(*(int*)front(l) == X[0]);
    assert(*(int*)back(l) == X[20]);

    moveFront(l);
    assert(*(int*)get(l) == X[0]);

    assert(*(int*)front(a) == X[20]);
    assert(*(int*)back(a) == X[0]);

    moveFront(a);
    assert(*(int*)get(a) == X[20]);

    List b = newList();
    clear(a);
    assert(length(a) == length(b));

    set(l, &X[0]);
    assert(*(int*)get(l) == X[0]);

    moveBack(l);
    assert(*(int*)get(l) == X[20]);
    movePrev(l);
    assert(*(int*)get(l) == X[19]);

    moveNext(l);
    assert(*(int*)get(l) == X[20]);

    prepend(l, &X[1]);
    moveFront(l);
    assert(*(int*)get(l) == X[1]);

    insertBefore(l, &X[2]);
    moveFront(l);
    assert(*(int*)get(l) == X[2]);

    insertAfter(l, &X[15]);
    moveNext(l);
    assert(*(int*)get(l) == X[15]); 

    deleteFront(l);
    moveFront(l);
    assert(*(int*)get(l) == X[15]);
    deleteBack(l);
    moveBack(l);
    assert(*(int*)get(l) == X[19]);

    delete(l);
    moveBack(l);
    assert(*(int*)get(l) == X[18]); 
    
    freeList(&l);
    freeList(&a);
    freeList(&b);
}