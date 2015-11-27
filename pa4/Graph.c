//Rahul Patel 
//rpate3
//pa4


#include <stdlib.h> 
#include "Graph.h"
#include "List.h" 
#include <stdio.h>

static void insertsort(List l, int u); 

#define white 1000000
#define black 1000000
#define gray  1000000

struct GraphObj{
	List *adj; 
	int *color;
	int *distance; 
	int *parent; 
	int order; 
	int size; 
	int source; 
} GraphObj; 

//Return a graph with vertices but no edges 
Graph newGraph(int n){
	Graph g = malloc(sizeof(struct GraphObj)); 
	g->adj = malloc((n+1)*sizeof(List)); 
	g->color = malloc((n+1)*sizeof(int)); 
	g->distance = malloc((n+1)*sizeof(int)); 
	g->parent = malloc((n+1)*sizeof(int)); 
	g->source = NIL; 
	g->order = n; 
	g->size = 0; 

	for(int i=0; i<n+1; i++){
		g->adj[i] = newList();	
		g->color[i] = white; 
		g->parent[i] = NIL; 
		g->distance[i] = INF; 
	}
	return g;
}
//free Graph memory
void freeGraph(Graph *pG){
	Graph f = *pG; 
	for(int i=0; i<(f->order) +1; i++){
		freeList(&(f->adj[i])); 
	}
	free(f->adj); 
	free(f->color); 
	free(f->parent); 
	free(f->distance); 
	free(*pG); 
	*pG = NULL; 
}

//Access Functions 
//returns number of vertices
int getOrder(Graph G){
  return G->order;
}
//returns # of edges
int getSize(Graph G){
  return G->size;
}
//returns source vertex
int getSource(Graph G){
  return G->source;
}

//returns parent vertex
int getParent(Graph G, int u){
	return G->parent[u]; 
}
//find distance from vertex to source
int getDist(Graph G, int u){
	if(getSource(G) == NIL){
		return INF; 
	}

	return G->distance[u]; 
}
//finds path from vertex to source
void getPath(List L, Graph G, int u){
	int s = G->source; 
	if(u==s){
		prepend(L,s); 
		return;
	}else if (G->parent[u] == NIL){
		append(L, NIL); 
	}else{
		prepend(L,u); 
		getPath(L, G, G->parent[u]); 
	}
}

//clear edges
void makeNull(Graph G){
	for(int i=0; i<G->order +1; i++){
		clear(G->adj[i]);
	}
}

//forms an edge between two vertices
void addEdge(Graph G, int u, int v){
	List U = G->adj[u]; 
	List V = G->adj[v]; 
	insertsort(U,v); 
	insertsort(V,u); 
}

//add an edge
void addArc(Graph G, int u, int v){
	List U = G->adj[u]; 
	insertsort(U,v); 
}

//adds vertices to list in order
void insertsort(List L, int u){
	if(length(L)==0) append(L,u); 
	for(moveTo(L,0); getIndex(L)>=0; moveNext(L)){
	int one = getElement(L); 
	if(u<one){
		insertBefore(L,u); 
		break; 
		}
	}
	if(getIndex(L) == -1) append(L,u); 
}

//attempt for BFS algorithm
void BFS(Graph G, int s){
	for(int u=1; u<G->order; u++){
		if(u!=s){
			G->color[u] = white; 
			G->distance[u] = INF; 
			G->parent[u] = NIL; 
		}
	}
	G->source = s; //define source
	G->color[s] = gray; 
	G->distance[s] = 0; 
	G->parent[s] = NIL; 
	List H; 
	prepend(H,s); 
	while(length(H)>0){
		int u = back(H); 
		deleteBack(H); 	
		List neigh = G->adj[u];
		for(moveTo(neigh,0); getIndex(neigh)>=0; moveNext(neigh)){
			int v = getElement(neigh); 
			if((G->color[v] = white)){
				G->color[v] = gray; 
				G->distance[v] = G->distance[u]+1; 
				G->parent[v]=u; 
				prepend(H,v); 
			} 
		} 
		G->color[u] = black; //vertex located 
	} 
	freeList(&H); 
}

//prints graph out 
void printGraph(FILE* out, Graph G){
	for(int i=1; i<getOrder(G)+1; i++){
		fprintf(out, "%d: ", i); 
		printList(out, G->adj[i]); 
		fprintf(out, "\n"); 
	}
}






