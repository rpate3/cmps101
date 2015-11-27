//Rahul Patel
//rpate3
//pa2

#include <stdlib.h>
#include "List.h"

//node points to nodeObj
typedef struct nodeObj* node; 

struct nodeObj{
	node next; 
	node prev; 
	int data;
};

//ListObj type
typedef struct ListObj{
	node cursor; 
	node front;
	node back; 
	int length; 
	int index;
}ListObj; 

//Creates a new empty list 
List newList(){
	List listA= malloc (sizeof(struct ListObj)); 
	listA->cursor = NULL;
	listA->back = NULL;
	listA->front = NULL; 
	listA->length = 0; 
	listA->index = -1; 
	return listA;
}
//frees memory locations
void freeList(List *pL){
	if((*pL) == NULL) return; 
	clear(*pL); 
	free(*pL);
	*pL = NULL; 
}

//Returns number of elements in this list
int length(List L){ 
	if(L==NULL) return -1; 
	return L->length; 
}
//Returns the index of the cursor element in this list, or returns -1 if the cursor 
//element is undefined
int getIndex(List L){
	if (L == NULL) return -1;
	return L->index;
}

//Returns front element in this list
int front(List L){
	if(L == NULL) return -1;
	if(L->length >0){
		return L->front->data;
	}
	return -1;
}

//Returns back element in this list
int back(List L){ 
	if(L == NULL) return -1; 
	if(L->length>0){
		return L->back->data; 
	}
	return -1;
}

//Returns cursor element in this list
int getElement (List L){ 
	if(L == NULL) return -1; 
	if(L->length > 0 && L->index >=0) { 
		return L->cursor->data; 

	}
	return -1;
}

//Returns true of this List and L are the same integer sequence. 
//The cursor is ignored in both lists
int equals(List A, List B){
	if(A == NULL || B == NULL) return -1; 
	
	node one =  A-> front;
	node two =  B-> front; 
	while(one!=NULL && two != NULL){
		if(one->data != two->data) return 0; 
		one = one->next; 
		two = two->next; 
	}
	if(one != NULL || two != NULL) return 0; 
	return 1; 
}

//Re-sets this List to the empty state
void clear(List L){
	if(L==NULL) return; 
	node front = L->front; 
	while(front != NULL){
		node temp = front->next; 
		free(front);
		front = temp; 
	}  
	L->front = NULL; 
	L->back = NULL; 
	L->cursor = NULL; 
	L->length = 0;
	L->index = -1;
}

//Moves the cursor to the element at index i, otherwise the cursor becomes undefined
void moveTo(List L, int i){
	if(L==NULL) return; 
	
	L->cursor = L->front; 
	L->index = i;
	if(i>=0 && i<L->length){
		for(; i>0; i--){
			L->cursor= L->cursor->next; 
		}
	}else{
		L->cursor = NULL; 
		L->index =-1;
	}
}

//Moves the cursor one step toward the front of the list 
void movePrev(List L){ 
	if(L==NULL) return;
	if(L->index>=0 && L->index< L->length){ 
		L->cursor = L->cursor->prev;
		L->index--; 
	}else{ 
		L->cursor = NULL;
		L->index = -1;
	}
}

//Moves the cursor one step toward the back of the list
void moveNext(List L){ 
	if(L==NULL) return; 
	if(L->index>=0 && L->index< L->length-1){ 
		L->cursor = L->cursor->next;
		L->index++;  
	}else{ 
		L->cursor = NULL;
		L->index = -1;
	}
}

//Inserts a new element before front element in this List
void prepend(List L, int data){
	L->length++; 
	node node= malloc(sizeof(struct nodeObj)); 
	node ->data = data; 
	node ->prev = NULL; 
	node ->next = L->front; 
	
	if(L->front == NULL){ 
		L->back = node; 
	}else{ 
		L->front->prev = node; 
	} 
	L->front = node;
	if(L->index >=0) L->index++; 
}

//Inserts new element after back element in this List
void append(List L, int data){ 
	if(L==NULL) return; 
	L->length++; 
	node node= malloc(sizeof(struct nodeObj)); 
	node-> data = data;
	node-> prev = L->back;
	node->next = NULL; 

	if(L->back == NULL){
		L->front = node; 
	}else {
		L->back->next = node;		
	}
	L->back = node;   
}

//Inserts new element before cursor element in this List
void insertBefore(List L, int data){
	if(L==NULL) return;
	if(!(L->length>0 && L->index>=0)) return; 
	L->length++;
	
	node node= malloc(sizeof(struct nodeObj)); 
	node->data = data; 
	node->prev = L->cursor->prev; 
	node->next = L->cursor;
	if(node->prev != NULL){
		L->cursor->prev->next = node; 
	}else{
		L->front = node; 
	}
	L->cursor->prev = node;
	L->index++; 
}

//Inserts new element after cursor element in this List 
void insertAfter(List L, int data){
	if(L==NULL) return; 
	if(!(L->length>0 && L->index>=0)) return; 
	L->length++; 
	
	node node= malloc(sizeof(struct nodeObj));
	node->data = data; 
	node->prev = L->cursor; 
	node->next = L->cursor->next; 

	if(node->next != NULL){
		L->cursor->next->prev = node; 
	}else{
		L->back = node; 
	}
	L->cursor->next = node; 
}

//Deletes the front element in this List
void deleteFront(List L){
	if(L->length>0){
		L->length--;
		if(L->cursor == NULL) return; 
		if(L->back == L->front) L->back = NULL; 
		node temp = L->front;
		L->front = L->front->next;
		free(temp); 
		L->front->prev = NULL;
		if(L->index != -1) L->index--; 
	}
}

//Deletes the back element in this List
void deleteBack(List L){
	if(L->length>0){
		L->length--; 
		if(L->index == L->length-1){
			 L->cursor == NULL; 
			 L->index = -1; 
		}
		if(L->back == L->front) L->front = NULL; 
		node temp = L->back;
		L->back = L->back->prev;
		free(temp);  
		L->back->next = NULL; 	
	}
}

//Deletes cursor element in this List
void delete(List L){
	if(L->length > 0 && L->index > 0){
		L->length--; 
		L->cursor->next->prev = L->cursor->prev;
		L->cursor->prev->next = L->cursor->next; 
		L->cursor = NULL; 
		L->index = -1; 
	}
}

//Prints the L to the file pointed to by out
void printList(FILE* out, List L){
	node temp = L->front; 
	while(temp!=NULL){
		printf("%d ",temp->data);
		temp = temp->next; 
	}
}

//copies List
List copyList(List L){
	List copy = newList(); 
	for(node temp = L->front; temp != NULL; temp = temp->next){
		append(copy, temp->data); 
	}
	return copy; 
}
