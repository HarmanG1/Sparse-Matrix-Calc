/********************************************************************************* 
* Harman Gidha
* List.c 
*********************************************************************************/ 

#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
   void* data;
   Node next;
   Node prev;
} NodeObj;

// private ListObj type
struct ListObj{
   Node front;
   Node back;
   int length;
   Node cursor;
   int curindex;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(void* data){
   Node N = malloc(sizeof(NodeObj));
   assert( N!=NULL );
   N->data = data;
   N->next = NULL;
   N->prev = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList(){
   List L;
   L = malloc(sizeof(ListObj));
   assert( L!=NULL );
   L->front = L->back = NULL;
   L->length = 0;
   L->cursor = NULL;
   L->curindex = -1;
   return(L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) { 
      while((*pL)->front != NULL)
      {
         Node n = (*pL)->front->next;
         freeNode(&(*pL)->front);
         (*pL)->front = n;
      }
      free(*pL);
      *pL = NULL;
   }
}

int length(List L)
{
   if(L == NULL)
   {
      fprintf(stderr, "Error: List is Null\n");
      exit(EXIT_FAILURE);
   }
   
   return L->length;
}

int index(List L)
{
   if(L == NULL)
   {
      fprintf(stderr, "Error: List is Null\n");
      exit(EXIT_FAILURE);
   }
   
   if(L->cursor != NULL)
   {
      return L->curindex;
   }
   return -1;
}

void* front(List L) // Returns front element of L. Pre: length()>0
{
   if(L == NULL)
   {
      fprintf(stderr, "Error: List is Null\n");
      exit(EXIT_FAILURE);
   }
   
   if(L->length > 0)
   {
      return L->front->data;
   }
   fprintf(stderr, "Error: Precondition not met\n");
   exit(EXIT_FAILURE);
}

void* back(List L) // Returns back element of L. Pre: length()>0
{
   if(L == NULL)
   {
      fprintf(stderr, "Error: List is Null");
      exit(EXIT_FAILURE);
   }
   
   if(L->length > 0)
   {
      return L->back->data;
   }
   fprintf(stderr, "Error: Precondition not met\n");
   exit(EXIT_FAILURE);
}

void* get(List L) // Returns cursor element of L. Pre: length()>0, index()>=0
{
   if(L == NULL)
   {
      fprintf(stderr, "Error: List is Null\n");
      exit(EXIT_FAILURE);
   }
   
   if((L->length > 0) && (L->curindex >= 0))
   {
      return L->cursor->data;
   } 
   fprintf(stderr, "Error: Precondition not met\n");
   exit(EXIT_FAILURE);
}

void clear(List L) // Resets L to its original empty state.
{
   if(L == NULL)
   {
      fprintf(stderr, "Error: List is Null\n");
      exit(EXIT_FAILURE);
   }
   
   while(L->front != NULL)
   {
      Node n = L->front->next;
      freeNode(&L->front);
      L->front = n;
   }
   L->length = 0;
   L->cursor = NULL;
   L->curindex = -1;
   L->back = NULL;
}

void set(List L, void* x) // Overwrites the cursor element’s data with x. // Pre: length()>0, index()>=0
{
   if(L == NULL)
   {
      fprintf(stderr, "Error: List is Null\n");
      exit(EXIT_FAILURE);
   }
   
   if((L->length > 0) && (L->curindex >= 0))
   {
      L->cursor->data = x;
      return;
   }
   fprintf(stderr, "Error: Precondition not met\n");
   exit(EXIT_FAILURE);
}

void moveFront(List L) // If L is non-empty, sets cursor under the front element, // otherwise does nothing.
{
   if(L == NULL)
   {
      fprintf(stderr, "Error: List is Null\n");
      exit(EXIT_FAILURE);
   }
   
   if(L->length > 0)
   {
      L->cursor = L->front;
      L->curindex = 0;
   }
}

void moveBack(List L) // If L is non-empty, sets cursor under the back element,// otherwise does nothing.
{
   if(L == NULL)
   {
      fprintf(stderr, "Error: List is Null\n");
      exit(EXIT_FAILURE);
   }
   
   if(L->length > 0)
   {
      L->cursor = L->back;
      L->curindex = L->length - 1;
   }
}
// If cursor is defined and not at front, move cursor one step toward the front of L; if cursor is defined and at
void movePrev(List L) // front, cursor becomes undefined; if cursor is undefined // do nothing
{
   if(L == NULL)
   {
      fprintf(stderr, "Error: List is Null\n");
      exit(EXIT_FAILURE);
   }
   
   if((L->cursor != NULL))
   {
      if(L->curindex > 0)
      {
         L->cursor = L->cursor->prev;
         L->curindex = L->curindex - 1;
      }
      else if(L->curindex == 0)
      {
         L->cursor = NULL;
         L->curindex = -1;
      }
   }
}                       

void moveNext(List L)
{
   if(L == NULL)
   {
      fprintf(stderr, "Error: List is Null\n");
      exit(EXIT_FAILURE);
   }
   
   if((L->cursor != NULL))
   {
      if(L->curindex < (L->length - 1))
      {
         L->cursor = L->cursor->next;
         L->curindex = L->curindex + 1;
      }
      else if(L->curindex == (L->length - 1))
      {
         L->cursor = NULL;
         L->curindex = -1;
      }
   }
}

void prepend(List L, void* x) // Insert new element into L. If L is non-empty, insertion takes place before front element.
{
   if(L == NULL)
   {
      fprintf(stderr, "Error: List is Null\n");
      exit(EXIT_FAILURE);
   }
   
   if(L->length > 0)
   {
      Node n = L->front;
      Node y = newNode(x);
      L->front = y;
      L->front->next = n;
      n->prev = L->front;
   }
   else
   {
      Node n = newNode(x);
      L->front = n;
      L->back = n;
   }
   L->length++;
   if(L->curindex >= 0)
   {
      L->curindex++;
   }
}

void append(List L, void* x) // Insert new element into L. If L is non-empty, insertion takes place after back element.
{
   if(L == NULL)
   {
      fprintf(stderr, "Error: List is Null\n");
      exit(EXIT_FAILURE);
   }
   
   if(L->length > 0)
   {
      Node n = L->back;
      Node y = newNode(x);
      L->back = y;
      L->back->prev = n;
      n->next = L->back;
   }
   else
   {
      Node n = newNode(x);
      L->front = n;
      L->back = n;
   }
   L->length++;
}

void insertBefore(List L, void* x) // Insert new element before cursor. Pre: length()>0, index()>=0
{
   if(L == NULL)
   {
      fprintf(stderr, "Error: List is Null\n");
      exit(EXIT_FAILURE);
   }
   
   if((L->length > 0) && (L->curindex >= 0))
   {
      if(L->curindex == 0)
      {
         prepend(L, x);
      }
      else
      {
         Node n = newNode(x);
         L->cursor->prev->next = n;
         n->prev = L->cursor->prev;
         L->cursor->prev = n;
         n->next = L->cursor;
         L->length++;
         L->curindex++;
      }
      return;
   }
   fprintf(stderr, "Error: Precondition not met\n");
   exit(EXIT_FAILURE);
}

void insertAfter(List L, void* x) // Insert new element after cursor. Pre: length()>0, index()>=0
{
   if(L == NULL)
   {
      fprintf(stderr, "Error: List is Null\n");
      exit(EXIT_FAILURE);
   }

   if((L->length > 0) && (L->curindex >= 0))
   {
      if(L->curindex == (L->length - 1))
      {
         append(L, x);
      }
      else
      {
         Node n = newNode(x);
         L->cursor->next->prev = n;
         n->next = L->cursor->next;
         L->cursor->next = n;
         n->prev = L->cursor;
         L->length++;
      }
      return;
   }
   fprintf(stderr, "Error: Precondition not met\n");
   exit(EXIT_FAILURE);
}

void deleteFront(List L) // Delete the front element. Pre: length()>0
{
   if(L == NULL)
   {
      fprintf(stderr, "Error: List is Null\n");
      exit(EXIT_FAILURE);
   }

   if(L->length > 0)
   {
      if(L->front->next != NULL)
      {
         Node n = L->front;
         L->front = L->front->next;
         L->front->prev = NULL;
         freeNode(&n);
      }
      else{
         freeNode(&L->front);
      }
      L->length--;
      if(L->curindex >=0)
      {
         L->curindex--;
         if(L->curindex == -1)
         {
            L->cursor = NULL;
         }
      }
      return;
   }
   fprintf(stderr, "Error: Precondition not met\n");
   exit(EXIT_FAILURE);
}

void deleteBack(List L) // Delete the back element. Pre: length()>0
{
   if(L == NULL)
   {
      fprintf(stderr, "Error: List is Null\n");
      exit(EXIT_FAILURE);
   }

   if(L->length > 0)
   {
      if(L->back->prev != NULL)
      {
         Node n = L->back;
         L->back = L->back->prev;
         L->back->next = NULL;
         freeNode(&n);
      }
      else{
         freeNode(&L->back);
      }
      L->length--;
      if(L->curindex == L->length)
      {
         L->curindex = -1;
         L->cursor = NULL;
      }
      return;
   }
   fprintf(stderr, "Error: Precondition not met\n");
   exit(EXIT_FAILURE);
}

void delete(List L) // Delete cursor element, making cursor undefined. Pre: length()>0, index()>=0
{
   if(L == NULL)
   {
      fprintf(stderr, "Error: List is Null\n");
      exit(EXIT_FAILURE);
   }

   if((L->length > 0) && (L->curindex >= 0))
   {
      if(L->curindex == 0)
      {
         deleteFront(L);
      }
      else if (L->curindex == (L->length - 1))
      {
         deleteBack(L);
      }
      else
      {
         Node n = L->cursor;
         L->cursor->prev->next = L->cursor->next;
         L->cursor->next->prev = L->cursor->prev;
         freeNode(&n);
         L->length--;
         L->curindex = -1;
         L->cursor = NULL;
      }
      return;
   }
   fprintf(stderr, "Error: Precondition not met\n");
   exit(EXIT_FAILURE);
}

// Prints to the file pointed to by out, a string representation of L consisting
void printList(FILE* out, List L) // of a space separated sequence of integers, with front on left.
{
   if(L == NULL)
   {
      fprintf(stderr, "Error: List is Null\n");
      exit(EXIT_FAILURE);
   }

   Node n = L->front;
   for(int i = 0; i < L->length; i++)
   {
      fprintf(out, "%p ", n->data);
      n = n->next;
   }
}

