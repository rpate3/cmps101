//Rahul Patel
//rpate3
//pa5
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Graph.h"

int main (int argc, char* argv[]){
  char line[200];
  // checks for correct arguments on input line
  if(argc != 3) {
    printf("Invalid number of inputs");
    exit(1);
  }

  // access files
  FILE* in = fopen(argv[1], "r");
  FILE* out = fopen(argv[2], "w");

 
  // read each line of in file
  fgets(line, 200, in);
  int num = 0;
  sscanf(line, "%d", &num);
  List L = newList();
  for (int i = 1; i <= num; i++) append(L, i);
  Graph G = newGraph(num);
  while( fgets(line, 200, in) != NULL) {
    int v1 = 0;
    int v2 = 0;
    sscanf(line, "%d %d", &v1, &v2);
   if(v1 == 0 && v2 == 0) break;
    addArc(G, v1, v2);
  }

  DFS(G, L);
  fprintf(out, "Adjacency list output for graph G:\n");
  printGraph(out, G);

  Graph T = transpose(G);
  DFS(T, L);

  //counts numCount
  int numCount = 0;
  for(moveTo(L, 0); getIndex(L) >= 0; moveNext(L)){
    if(getParent(T, getElement(L)) == NIL) numCount ++ ;
  }
  // puts components into array list of size numCount
  List Count[numCount];
  int i = numCount;
  for(moveTo(L, 0); getIndex(L) >= 0; moveNext(L)){
    if(getParent(T, getElement(L)) == NIL){
      i--;
      Count[i] = newList();
    }
    append(Count[i], getElement(L));
  }

  // prints out count
  fprintf(out, "\nG contains %d strongly connected components:", numCount);
  for(int i = 0; i < numCount; i++){
    fprintf(out, "\n");
    fprintf(out, "Component %d: ", i + 1);
    printList(out, Count[i]);
    freeList(&(Count[i]));
  }
  // frees memory
  fprintf(out, "\n");
  freeGraph(&T);
  freeGraph(&G);
  freeList(&L);
  fclose(in);
  fclose(out);
}
