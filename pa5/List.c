//Rahul Patel
//rpate3
//pa5
//
#include <stdlib.h>
#include "List.h"

//reads that node points to nodeObj
typedef struct nodeObj* node;

struct nodeObj {
  node prev;
  node next;
  int data;
};

// struct type ListObj
typedef struct ListObj {
  node cursor;
  node front;
  node back;
  int length;
  int index;
} ListObj;

// constructor for  newList
List newList() {
  List listA = malloc (sizeof(struct ListObj));
  listA->cursor = NULL;
  listA->front = NULL;
  listA->back = NULL;
  listA->length = 0;
  listA->index = -1;
  return listA;
}

// deletes the list by freeing memory locations
void freeList (List* pL){
 if((*pL) == NULL) return; 
  clear(*pL);
  free(*pL);
  *pL = NULL;
}

// returns length of list
int length(List L){
 if(L==NULL) {printf("error: List L is null");return -1;} 
  return L->length;
}

// returns the index of the cursor element 
int getIndex(List L){
 if(L==NULL) {printf("error: List L is null");return -1;} 
  return L->index;
}

// Return the front element if length > 0
int front(List L){
if(L==NULL) {printf("error: List L is null");return-1;} 
  if (L->length > 0) return L->front->data;
  return -1;
}

// Return back element if length > 0
int back(List L){
if(L==NULL) {printf("error: List L is null");return-1;} 
  if (L->length > 0) return L->back->data;
  return -1;
}

// Return cursor element in list
int getElement(List L){
if(L==NULL) {printf("error: List L is null");return-1;}   
if (L->length > 0 && L->index >=0){
    return L->cursor->data;
  }
  return -1;
}

//Returns true if the two lists are identical
int equals (List A, List B){
 if(A==NULL || B==NULL) {printf("error: A or B null");return-1;} 
  node one = A->front;
  node two = B->front;
  while (one != NULL && two !=NULL){
    if(one->data != two->data) return 0;
    one = one->next;
    two = two->next;
  }
 return 1; 
}

// Sets list to empty state
void clear(List L){
if(L==NULL) {printf("error: List L is null");return;}
  node front = L->front;
  while (front != NULL){
    node tmp = front->next;
    free(front);
    front = tmp;
  }
  L->front = NULL;
  L->back = NULL;
  L->cursor = NULL;
  L->length = 0;
  L->index = -1;
}

// moves the cursor to index i
void moveTo(List L, int i){
if(L==NULL) {printf("error: List L is null");return;} 
  L->cursor = L->front;
  L->index = i;
  if(i >= 0 && i < L->length){
    for(; i > 0; i--){
      L->cursor = L->cursor->next;
    }
  } else {
    L->cursor = NULL;
    L->index = -1;
  }
}

//this operation is equivalent to moveTo(getIndex() - 1)
void movePrev(List L){
if(L==NULL) {printf("error: List L is null");return;} 
  if(L->index > 0 && L->index < L->length){
    L->cursor = L->cursor->prev;
    L->index--;
  } else {
    L->cursor = NULL;
    L->index = -1;
  }
}

//this opeartion is equivalent to moveTo(getIndex() + 1)
void moveNext(List L){
if(L==NULL) {printf("error: List L is null");return;} 
  if(L->index >= 0 && L->index < L->length - 1){
    L->cursor = L->cursor->next;
    L->index++;
  } else {
    L->cursor = NULL;
    L->index = -1;
  }
}

// prepends list
void prepend(List L, int data){
  L->length++;
  node n = malloc(sizeof(struct nodeObj));
  n->data = data;
  n->prev = NULL;
  n->next = L->front;
  if (L->front == NULL){
    L->back = n;
  } else {
    L->front->prev = n;
  }  
  L->front = n;

  if (L->index >= 0) L->index++;
}

//appends  list
void append(List L, int data){
  L->length++;
  node n= malloc(sizeof(struct nodeObj));
  n->data = data;
  n->prev = L->back;
  n->next = NULL;
  if(L->back == NULL){
    L->front = n;
  } else {
    L->back->next = n;
  }
  L->back = n;
}

// inserts element before the cursor
void insertBefore(List L, int data){
if(L==NULL) {printf("error: List L is null");return;}
  if (!(L->length > 0 && L->index >= 0)) return;
  L->length++;
  node n = malloc(sizeof(struct nodeObj));
  n->data = data;
  n->prev = L->cursor->prev;
  n->next = L->cursor;
  if(n->prev != NULL){
    L->cursor->prev->next = n; 
  } else {
    L->front = n;
  }
  
  L->cursor->prev = n;
  L->index++;
}

// inserts element after the cursor
void insertAfter(List L, int data){
if(L==NULL) {printf("error: List L is null"); return;} 
  if (!(L->length > 0 && L->index >= 0)) return;
  L->length++;
  node n = malloc(sizeof(struct nodeObj));
  n->data = data;
  n->prev = L->cursor;
  n->next = L->cursor->next;
  
  if(n->next != NULL){
    L->cursor->next->prev = n;
  } else {
    L->back = n;
  }

  L->cursor->next = n;
}

// deletes the front node
void deleteFront(List L){
  if(L->length > 0){
    L->length--;
    if(L->index == 0) L->cursor = NULL;
    if(L->back == L->front) L->back = NULL;
    node tmp = L->front;
    L->front = L->front->next;
    free(tmp);
    L->front->prev = NULL;
    if(L->index != -1) L->index--;
  }
}

// deletes the back node
void deleteBack(List L){
  if(L->length > 0){
    L->length--;
    if(L->index == L->length - 1){
      L->cursor = NULL;
      L->index = -1;
    }
    if(L->back == L->front){
      free(L->back);
      L->front = NULL;
      return;
    }

    node tmp = L->back;
    L->back = L->back->prev;
    free(tmp);
    L->back->next = NULL;
  }

}

// deletes the cursor node
void delete(List L){
if(L==NULL) {printf("error: List L is null"); return;} 
  if(L->cursor == L->front){
    deleteFront(L);
  } else if (L->cursor == L->back){
    deleteBack(L);
  }

  if (L->length > 0 && L->index > 0){
    L->length--;
    node tmp = L->cursor;
    L->cursor->next->prev = L->cursor->prev;
    L->cursor->prev->next = L->cursor->next;
    L->cursor = NULL;
    L->index = -1;
    free(tmp);
  }
}

// prints out the list
void printList (FILE *out, List L){
if(L==NULL){printf("error: List L is null"); return;} 
  node tmp = L->front;
  while (tmp != L->back){
    fprintf(out, "%d ", tmp->data);
    tmp = tmp->next;
  }
  if(tmp != NULL) fprintf(out, "%d", tmp->data);
  
}

// Returns a copy of the List parameter
List copyList(List L){

  List copy = newList();
  for(node tmp = L->front; tmp != NULL; tmp = tmp->next){
    append(copy, tmp->data);
  }
  return copy;
}

