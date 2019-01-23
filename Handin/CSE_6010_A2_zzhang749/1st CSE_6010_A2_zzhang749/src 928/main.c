//
//main.c:
//This file contains program that can analyze important information like the number of components,
//the average size of components and the largest component of a graph, which can be converted from 
//a txt file through this file.
//
// Author: Zhiquan Zhang, created on 9/26/2018
// All rights reserved
//
#include"stdio.h"
#include"stdlib.h"
#include"graph.h"
#include"string.h"
int number; // "number" is the number of the vertex of a graph.
int compIndex; //"compIndex" is the number of known component.
int max; //"max" is the size of the largest component.
int main(int argc, char* argv[]){
	/************ Read the input parameters and initialize************/
	if(argc<3) {
		printf("Wrong!");
		return 0;
	}
	char* inputpath = malloc(20*sizeof(char));
	char* outputpath = malloc(20*sizeof(char));
	strcpy(inputpath,argv[1]);
	strcpy(outputpath,argv[2]);
	strcat(inputpath,".txt");
	strcat(outputpath,".txt");
	FILE* input;
	FILE* foutput;
	input = fopen(inputpath,"r");
	foutput = fopen(outputpath,"w");
	compIndex=0;
	number=1;
	/************ Read the input parameters and initialize ************/

	/************ Read the input parameters ************/
	graph* gra = malloc(sizeof(graph));
	char* str = malloc(20*sizeof(char));
	// Check the allocation.
	if(gra==NULL || str==NULL) return 0;
	fgets(str,20,input);
	number = atoi(str);
	free(str);
	printf("\nThe read number is %d!!",number);
	/************ Read the input parameters ************/

	/************ Allocate memory for important parameters ************/
	gra->vertex = malloc((number+1)*sizeof(vertexNode));// My vertex starts at 1!So the length of them is number+1!
	int* visited = malloc((number+1)* sizeof(int));//This array saves whether a node has been visisted.
	int* component = malloc((number+1)* sizeof(int));//This array saves every node's component.
	int* memNum = malloc((number+1)* sizeof(int));//This array saves the number of different components
	if(visited==NULL || component==NULL || memNum==NULL) return 0;
	for(int i=0;i<number+1;i++){
			visited[i]=0;
			memNum[i]=0;
		}
	/************ Allocate memory for important parameters ************/

	/************ Generate a graph and analyze it ,output the result************/
	fromStringtoGraph(gra,input);
	showList(gra);
	dfs(gra,visited, component, memNum);
	printf("\nBelow is the result");
	memNum=realloc(memNum, (compIndex+1)*sizeof(int));
	analysis(memNum);
	output(foutput, memNum);
	/************ Generate a graph and analyze it ,output the result************/

	/************ free memomry and close files************/
	fclose(input);
	fclose(foutput);
	free(gra->vertex);
	free(gra);
	free(visited);
	free(component);
	free(memNum);
	/************ free memomry and close files************/
	return 0;
}
