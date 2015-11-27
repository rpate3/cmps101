//Rahul Patel
//rpate3
//pa4

#include "List.h"
#include <stdio.h>
#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#define INF -200
#define NIL 0
#define UNDEF 0 

//Graph Type
typedef struct  GraphObj* Graph;
//
//// Constructors and Destructors
Graph newGraph(int n);//newly created graph 
void freeGraph(Graph* pG);//free memory pertaining to graph
//
// Access functions
int getOrder(Graph G);//returns number of vertices 
int getSize(Graph G);//returns size 
int getDiscover(Graph G, int u);//returns appropriate field values
int getParent(Graph G, int u);//returns parent of vertex u 
int getFinish(Graph G, int u);//returns appropriate field values
//void getPath(List L, Graph G, int u);
//
//Manipulation Procedures
//void makeNull(Graph G);
void addEdge(Graph G, int u, int v);//inserts edge joined u to v 
void addArc(Graph G, int u, int v);//inserts a new directed edge from u to v
void DFS(Graph G, List S);//runs DFS algo on Graph G
//
void printGraph(FILE* out, Graph G);//prints out graph
Graph transpose(Graph G); //returns transpose graph 
Graph copyGraph(Graph G); //makes a copy of Graph G

#endif
