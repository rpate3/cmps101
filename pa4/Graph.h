//Rahul Patel
//rpate3
//pa4

#include "List.h"
#include <stdio.h>
#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#define INF -200
#define NIL -201

//Graph Type
typedef struct  GraphObj* Graph;
//
//// Constructors and Destructors
Graph newGraph(int n);
void freeGraph(Graph* pG);
//
// Access functions
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);
//
//Manipulation Procedures
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);
//
void printGraph(FILE* out, Graph G);

#endif
