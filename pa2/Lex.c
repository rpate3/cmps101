//Rahul Patel
//rpate3
//pa2

#include<stdio.h>
#include<string.h>
#include<stdlib.h> 

#include "List.h"

#define MAX 200

//Insertsort operation
List insertsort(char** array, int length){


	List list = newList();
	append(list, 0);//append 0 onto the list
	for(int i = 1; i <length; i++){
		char *temp = array[i]; 
		int index = i-1; 
		moveTo(list, index); //moves cursor to correct position
		while(index>-1 && strcmp(temp, array[getElement(list)]) <0){//sorts lex
			index--; 
			movePrev(list); 
		}
		if(getIndex(list)==-1){ //condition for null cursor
			prepend(list, i); 
		}else{
			insertAfter(list, i); 
		}
	}
	return list;
}


//reads in the input file and stores them in an array of strings
char** read(FILE* input, int lines){
	char** Sarray= malloc(sizeof(char**)*lines); 
	char line[200]; 
	for(int i=0; i<lines; i++){
		fgets(line, 200, input);
		Sarray[i] = strdup(line); 
	}
	return Sarray; 
}

void freed(char** lines, int linec, List list){
	for(int i=0; i<linec; i++){
		free(lines[i]); 		
	}
	free(lines); 
	freeList(&list);
}








int main(int argc,char* argv[]){
	if(argc > 3){  //Checks command line
		printf("Invalid inputs\n"); 
		exit(1);
	}

	//read in the files
	FILE* input = fopen(argv[1],"r");
	FILE* output = fopen(argv[2], "w");


	int linecount = 0; 
	char lines[MAX]; 
	
	//goes through the file and counts the lines
	while(fgets(lines, MAX, input)!= NULL) linecount++; 


	fclose(input); 
	input = fopen(argv[1], "r"); 
	char** inlines = read(input, linecount); 
	
	//carries out insertsort and stores result into a list
 	List list = insertsort(inlines, linecount); 

	//prints out list by going through the indicies
	for(moveTo(list,0); getIndex(list)>=0; moveNext(list)){
		printf( "%s", inlines[getElement(list)]); 
	}
	
	//close files
	fclose(input); 
	fclose(output);
	freed(inlines, linecount, list);  
	return(0); 
}
