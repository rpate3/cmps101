//Rahul Patel
//rpate3 
//pa5 
//
#include <stdlib.h>
#include "Graph.h"
#include <stdio.h> 

static void insertsort(List L, int u);

#define white 1000000
#define black 1999999
#define gray  -166666
struct GraphObj {
  List *adj;
  int *parent;
  int *color;
  int *discover;
  int *finish;
  int order; 
  int size; 
};



//Returns a Graph that points to GraphObj
Graph newGraph(int x){ 
  Graph newGraph = malloc(sizeof(struct GraphObj)); 
  newGraph->adj = malloc((x+1)*sizeof(List)); 
  newGraph->parent = malloc((x+1)*sizeof(int)); 
  newGraph->color = malloc((x+1)*sizeof(int)); 
  newGraph->discover = malloc((x+1)*sizeof(int));
  newGraph->finish = malloc((x+1)*sizeof(int));
  newGraph->order = x; 
  newGraph->size = 0; 
  for (int i = 0; i < x + 1; i++){
    newGraph->adj[i] = newList();
    newGraph->parent[i] = NIL;
    newGraph->color[i] = white; 
    newGraph->discover[i] = UNDEF; 
    newGraph->finish[i] = UNDEF; 
  }
  return newGraph;
} 
// frees memory related to Graph 
void freeGraph(Graph* pG){
  Graph f = *pG; 
  for(int i = 0; i < (f->order) + 1; i++){
    freeList(&(f->adj[i]));
  }
  free(f->adj); 
  free(f->color); 
  free(f->parent); 
  free(f->discover);
  free(f->finish);
  free(*pG);
  *pG = NULL; 
} 

 

// Access functions 
// returns number of vertices
int getOrder(Graph G){
 if(G==NULL){
	printf("error: null graph passed in\n"); 
	}
  return G->order;
}
// returns number of edges
int getSize(Graph G){
  return G->size;
}
// returns parent vertex of the chosen vertex
int getParent(Graph G, int u){
  if(u > getOrder(G) || u < 1){
    printf("error: invaid u parameter in getParent\n");
    return 0;
  }
  return G->parent[u];
}

// returns discover time of the vertex from source 
int getDiscover(Graph G, int u){
  if(u > getOrder(G) || u < 1){
    printf("error: invalid u parameter in getDiscover\n");
    return 0;
  }
  return G->discover[u];
}
 
// returns finish time of vertex from source
int getFinish(Graph G, int u){
  if(u > getOrder(G) || u < 1){
    printf("error: invalid u parameter in getFinish\n");
    return 0;
  }
  return G->finish[u];
} 

// creates an edge between vertices
void addEdge(Graph G, int u, int v){
  if(u > getOrder(G) || u < 1 || v > getOrder(G) || v < 1){
    printf("error: preconditions not satisfied in addEdge\n");
    printf("%d %d\n", u, v);
    return;
  }
  List L1 = G->adj[u];
  List L2 = G->adj[v];
  insertsort(L1, v);
  insertsort(L2, u);
}

// adds a directed edge
void addArc(Graph G, int u, int v){
  if(u > getOrder(G) || u < 1  || v > getOrder(G) || v < 1){
    printf("error: preconditions not satisfied in addArc\n");
    printf("%d %d\n", u, v);
    return;
  }
  List L = G->adj[u];
  insertsort(L, v);
}

//function to add vertices to beginning of list in order
static void insertsort(List L, int u){
  if (length(L) == 0){
    append(L, u);
    return;
  }
  for(moveTo(L, 0); getIndex(L) >= 0; moveNext(L)){
    int one = getElement(L);
    if(u < one){
      insertBefore(L, u);
      break;
    }
  }
  if(getIndex(L) == -1){
    append(L, u);
  }
}
 
 
// DFS algorithm
void DFS(Graph G, List s){
  if(length(s) != getOrder(G)){
    printf("error: list and graph incompatible on DFS\n");
    return;
  }
  int time = 0;
  int size = length(s);
  void Visit(int v1){
    time = time + 1;
    G->discover[v1] = time;
    G->color[v1] = gray;
    List adj = G->adj[v1];
    for(moveTo(adj, 0); getIndex(adj) >=0; moveNext(adj)){
      int v2 = getElement(adj);
      if(G->color[v2] == white){
	G->parent[v2] = v1;
	Visit(v2);
      }
      
    }
    G->color[v1] = black;
    time = time +1;
    G->finish[v1] = time;
    prepend(s, v1);
  }

  for(moveTo(s, 0); getIndex(s) >=0; moveNext(s)){
    int v = getElement(s);
    G->parent[v] = NIL;
    G->color[v] = white;
  }

  for(moveTo(s, 0); getIndex(s) >=0; moveNext(s)){
    int v = getElement(s);
    if(G->color[v] == white) Visit(v);
  }
  for(;size > 0 ; size--){
    deleteBack(s);
  }
} 

// print function 
void printGraph(FILE* out, Graph G){
  if(G == NULL || out  == NULL){
    printf("error: null in printGraph\n");
    return;
  }
  for (int i = 1; i < getOrder(G) + 1; i++){
    fprintf(out, "%d: ", i);
    printList(out, G->adj[i]);
    fprintf(out, "\n");
  }
}
// returns the Transpose of graph
Graph transpose(Graph G){
 int x = G->order;
  Graph newGraph = malloc(sizeof(struct GraphObj)); 
  newGraph->adj = malloc ((x+1)*sizeof(List)); 
  newGraph->parent = malloc((x+1)*sizeof(int)); 
  newGraph->color = malloc((x+1)*sizeof(int)); 
  newGraph->discover = malloc((x+1)*sizeof(int));
  newGraph->finish = malloc((x+1)*sizeof(int));
  newGraph->order = G->order;
  newGraph->size = G->size; 
  for (int i = 0; i < x + 1; i++){
    newGraph->adj[i] = newList();
    newGraph->parent[i] = NIL;
    newGraph->color[i] = white;
    newGraph->discover[i] = UNDEF;
    newGraph->finish[i] = UNDEF;
  }
  for(int i = 0; i < x + 1; i++){
    List t = G->adj[i];
    for(moveTo(t, 0); getIndex(t) >= 0; moveNext(t)){
      append(newGraph->adj[getElement(t)], i);
    }
  }
  return newGraph;
}
// makes a copy of Graph
Graph copyGraph(Graph G){
  int x = G->order;
  Graph newGraph = malloc(sizeof(struct GraphObj)); 
  newGraph->adj = malloc ((x+1)*sizeof(List)); 
  newGraph->parent = malloc((x+1)*sizeof(int)); 
  newGraph->color = malloc((x+1)*sizeof(int)); 
  newGraph->discover = malloc((x+1)*sizeof(int));
  newGraph->finish = malloc((x+1)*sizeof(int));
  newGraph->order = G->order;
  newGraph->size = G->size;
  for (int i = 0; i < x + 1; i++){
    newGraph->adj[i] = newList();
    List c = G->adj[i];
    for(moveTo(c, 0); getIndex(c) >= 0; moveNext(c)){
      append(newGraph->adj[i], getElement(c));
    }
    newGraph->parent[i] = NIL;
    newGraph->color[i] = white;
    newGraph->discover[i] = UNDEF;
    newGraph->finish[i] = UNDEF;
  }
  return newGraph;
}
