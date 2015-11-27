//Rahul Patel
//rpate3
//pa5`

#ifndef __LIST_H_INLCUDE__
#define __LIST_H_INCLUDE__

#include <stdio.h>

//Constructors and deconstructors
typedef struct ListObj* List; 
List newList(void); 
void freeList(List *pL); 

//Access functions
int length(List L); //Returns number of elements in this list. 
int getIndex(List L); //Returns the index of the cursor element in this list
int front(List L); // Returns front element in this list
int back(List L); // Returns back element in this List
int getElement(List L); //Returns cursor element in this list
int equals(List A, List B); // Returns true if this List and L are the same

//Manipulation procedures
void clear(List L); // Re-sets this List to the empty state
void moveTo(List L, int i); //moves cursor to the element at index i 
void movePrev(List L); //moves cursor one step toward the front of the list
void moveNext(List L); //movres the cursor one step toward the back of the list
void prepend(List L, int data); // Inserts new element to front  of List
void append(List L, int data); //Inserts new element to back  of List
void insertBefore(List L, int data); //Inserts new element before cursor element in this List
void insertAfter(List L, int data); // Inserts new element after cursor element in this List
void deleteFront(List L); // Deletes the front element in this List
void deleteBack(List L); // Deletes the back element in this List
void delete(List L); //Deletes cursor element in this List

//Other operations
void printList(FILE* out, List L); //prints list
List copyList(List L);  //returns a copy of list
#endif

