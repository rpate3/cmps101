//Rahul Patel
//rpate3
//pa2

#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main(int argc, char* argv[]){
   
   List A = newList();
   List B = newList();
   List C = NULL;
   int i;

   for(i=1; i<=20; i++){
      append(A,i);
      prepend(B,i);
   }

   printList(stdout,A); 
   printf("\n");
   printList(stdout,B); 
   printf("\n");

   for(moveTo(A,0); getIndex(A)>=0; moveNext(A)){
      printf("%d ", getElement(A));
   }
   printf("\n");
   for(moveTo(B,length(B)-1); getIndex(B)>=0; movePrev(B)){
      printf("%d ", getElement(B));
   }
   printf("\n");

   C = copyList(A);
   printf("%s\n", equals(A,B)?"true":"false");
   printf("%s\n", equals(B,C)?"true":"false");
   printf("%s\n", equals(C,A)?"true":"false");

   moveTo(A,5); 
   insertBefore(A,-1);
   moveTo(A,15);
   insertAfter(A,-2);
   moveTo(A,10);
   delete(A);
   printList(stdout,A);
   printf("\n");
   clear(A);
   printf("%d\n", length(A));

   freeList(&A);
   freeList(&B);
   freeList(&C);
   
   return(0);
                      }
