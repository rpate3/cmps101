#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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
  int numV = 0;
  sscanf(line, "%d", &numV);
  List L = newList();
  for (int i = 1; i <= numV; i++) append(L, i);
  Graph G = newGraph(numV);
  while( fgets(line, 200, in) != NULL) {
    int v1 = 0;
    int v2 = 0;
    sscanf(line, "%d %d", &v1, &v2);
   if(v1 == 0 && v2 == 0) break;
    addArc(G, v1, v2);
  }

  DFS(G, L);
  fprintf(out, "Adjacency list representation of G:\n");
  printGraph(out, G);

  Graph T = transpose(G);
  DFS(T, L);

  //counts the number of numCount
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
  for(int j = 0; j < numCount; j++){
    fprintf(out, "\n");
    fprintf(out, "Component %d: ", j + 1);
    printList(out, Count[j]);
    freeList(&(Count[j]));
  }
  // frees memory
  fprintf(out, "\n");
  freeGraph(&G);
  freeGraph(&T);
  freeList(&L);
  fclose(in);
  fclose(out);
  return(0);
}
