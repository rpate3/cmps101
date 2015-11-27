//Rahul Patel 
//rpate3
///pa4

#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
#include "Graph.h"  

int main(int argc, char* argv[]){
	char line[250]; 
	if(argc != 3){ //Checks the number of arguments on the input line
		printf("Error: invalid number of args");
		printf("\n");  
		exit(1);
	}
	
	//reads in files
	FILE* in = fopen(argv[1], "r"); 
	FILE* out = fopen(argv[2], "w"); 

	//read in lines of file	
	fgets(line, 250, in); 
	int numV =0; 
	sscanf(line, "%d", &numV); 

	//Creates the Graph
	Graph G = newGraph(numV); 
	while(fgets(line, 250, in)!=NULL){
		int v1=0; 
		int v2=0;
		sscanf(line, "%d %d", &v1, &v2);
		addEdge(G, v1, v2); 
	}
	printGraph(out, G);
	 
	//attempt to find distances between vertex
	List L; 
	int v1=0;
	int v2=0;  
	int d = getDist(G,v2);
	while(fgets(line, 250, in)!= NULL){
		if(v1 == 0 && v2 ==0) break; 
		BFS(G, v1); 
		getPath(L,G,v2);
		fprintf(out, "Distance from %d to %d is ", v1, v2); 
		fprintf(out, "%d\n", d); 
		if(front(L) == -200){ 
			fprintf(out, "No %d-%d path exists", v1, v2);
		}else{
		fprintf(out, "Shortest %d-%d path ", v1, v2); 
		printList(out, L);
		}  
		freeList(&L); 
	}
	//free graph and close files
	fprintf(out, "\n"); 
	freeGraph(&G); 
	fclose(in); 
	fclose(out); 

	return(0); 
}


