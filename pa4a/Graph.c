#include <stdlib.h>

#include "Graph.h"

static void insertsort(List L, int u);

#define white 1000000
#define black 1999999
#define gray  -166666
struct GraphObj {
  List *array;
  int *color;
  int *parent;
  int *discover;
  int *finish;
  int order; 
  int size; 
};



//Returns a Graph that points to GraphObj
Graph newGraph(int n){ 
  Graph newGraph = malloc(sizeof(struct GraphObj)); 
  newGraph->array = malloc ((n+1)*sizeof(List)); 
  newGraph->color = malloc((n+1)*sizeof(int)); 
  newGraph->parent = malloc((n+1)*sizeof(int)); 
  newGraph->discover = malloc((n+1)*sizeof(int));
  newGraph->finish = malloc((n+1)*sizeof(int));
  newGraph->order = n; 
  newGraph->size = 0; 
  for (int i = 0; i < n + 1; i++){
    newGraph->array[i] = newList();
    newGraph->color[i] = white;
    newGraph->parent[i] = NIL; 
    newGraph->discover[i] = UNDEF; 
    newGraph->finish[i] = UNDEF; 
  }
  return newGraph;
} 
// frees memory related to Graph 
void freeGraph(Graph* pG){
  Graph f = *pG; 
  for(int i = 0; i < (f->order) + 1; i++){
    freeList(&(f->array[i]));
  }
  free(f->array); 
  free(f->color); 
  free(f->parent); 
  free(f->discover);
  free(f->finish);
  free(*pG);
  *pG = NULL; 
} 

 

/*** Access functions ***/
// returns number of vertices
int getOrder(Graph G){
 if(G==NULL){
	printf("passed in null graph\n"); 
	}
  return G->order;
}
// returns number of edges
int getSize(Graph G){
  return G->size;
}
// returns parent vertex of the chosen vertex
int getParent(Graph G, int u){
  if(u < 1 || u > getOrder(G)){
    printf("getParent: invalid u parameter\n");
    return 0;
  }
  return G->parent[u];
}

// returns discover time of the vertex from source 
int getDiscover(Graph G, int u){
  if(u < 1 || u > getOrder(G)){
    printf("getDiscover: invalid u parameter\n");
    return 0;
  }
  return G->discover[u];
}
 
// returns finish time of vertex from source
int getFinish(Graph G, int u){
  if(u < 1 || u > getOrder(G)){
    printf("getFinish: invalid u parameter\n");
    return 0;
  }
  return G->finish[u];
} 

// creates an edge between vertices
// precondition, the vertex numbers must be > 1 and < getOrder(G) 
void addEdge(Graph G, int u, int v){
  if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
    printf("Addedge: preconditions not met\n");
    printf("%d %d\n", u, v);
    return;
  }
  List U = G->array[u];
  List V = G->array[v];
  insertsort(U, v);
  insertsort(V, u);
}

// function to append vertices in adjacent order
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
 
// adds a directed edge
void addArc(Graph G, int u, int v){
  if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
    printf("Addarc: preconditions not met\n");
    printf("%d %d\n", u, v);
    return;
  }
  List U = G->array[u];
  insertsort(U, v);
}
 
// DFS algorithm
void DFS(Graph G, List s){
  if(length(s) != getOrder(G)){
    printf("DFS: unequal list and graph sizes\n");
    return;
  }
  int time = 0;
  int size = length(s);
  void Visit(int vertex){
    time = time + 1;
    G->discover[vertex] = time;
    G->color[vertex] = gray;
    List adj = G->array[vertex];
    for(moveTo(adj, 0); getIndex(adj) >=0; moveNext(adj)){
      int vert = getElement(adj);
      if(G->color[vert] == white){
	G->parent[vert] = vertex;
	Visit(vert);
      }
      
    }
    G->color[vertex] = black;
    time = time +1;
    G->finish[vertex] = time;
    prepend(s, vertex);
  }

  for(moveTo(s, 0); getIndex(s) >=0; moveNext(s)){
    int v = getElement(s);
    G->color[v] = white;
    G->parent[v] = NIL;
  }

  for(moveTo(s, 0); getIndex(s) >=0; moveNext(s)){
    int v = getElement(s);
    if(G->color[v] == white) Visit(v);
  }
  for(;size > 0 ; size--){
    deleteBack(s);
  }
} 

/*** Other operations ***/ 
// print function 
void printGraph(FILE* out, Graph G){
  if(out == NULL || G == NULL){
    printf("printGraph: Passed in NUll parameters\n");
    return;
  }

  for (int i = 1; i < getOrder(G) + 1; i++){
    fprintf(out, "%d: ", i);
    printList(out, G->array[i]);
    fprintf(out, "\n");
  }
}
// returns the Transpose of graoh
Graph transpose(Graph G){
 int n = G->order;
  Graph newGraph = malloc(sizeof(struct GraphObj)); 
  newGraph->array = malloc ((n+1)*sizeof(List)); 
  newGraph->color = malloc((n+1)*sizeof(int)); 
  newGraph->parent = malloc((n+1)*sizeof(int)); 
  newGraph->discover = malloc((n+1)*sizeof(int));
  newGraph->finish = malloc((n+1)*sizeof(int));
  newGraph->order = G->order;
  newGraph->size = G->size;
  for (int i = 0; i < n + 1; i++){
    newGraph->array[i] = newList();
    newGraph->color[i] = white;
    newGraph->parent[i] = NIL;
    newGraph->discover[i] = UNDEF;
    newGraph->finish[i] = UNDEF;
  }
  for(int i = 0; i < n + 1; i++){
    List g = G->array[i];
    for(moveTo(g, 0); getIndex(g) >= 0; moveNext(g)){
      append(newGraph->array[getElement(g)], i);
    }
  }
  return newGraph;
}
// makes a copy of Graph
Graph copyGraph(Graph G){
  int n = G->order;
  Graph newGraph = malloc(sizeof(struct GraphObj)); 
  newGraph->array = malloc ((n+1)*sizeof(List)); 
  newGraph->color = malloc((n+1)*sizeof(int)); 
  newGraph->parent = malloc((n+1)*sizeof(int)); 
  newGraph->discover = malloc((n+1)*sizeof(int));
  newGraph->finish = malloc((n+1)*sizeof(int));
  newGraph->order = G->order;
  newGraph->size = G->size;
  for (int i = 0; i < n + 1; i++){
    newGraph->array[i] = newList();
    List g = G->array[i];
    for(moveTo(g, 0); getIndex(g) >= 0; moveNext(g)){
      append(newGraph->array[i], getElement(g));
    }
    newGraph->color[i] = white;
    newGraph->parent[i] = NIL;
    newGraph->discover[i] = UNDEF;
    newGraph->finish[i] = UNDEF;
  }
  return newGraph;
}
