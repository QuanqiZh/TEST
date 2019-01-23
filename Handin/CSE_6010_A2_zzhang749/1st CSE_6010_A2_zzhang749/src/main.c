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
//int number; // "number" is the number of the vertex of a graph.
//int compIndex; //"compIndex" is the number of known component.
//int max; //"max" is the size of the largest component.
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
	/************ Read the input parameters and initialize ************/

	/************ Read the input parameters ************/
	char* str = malloc(20*sizeof(char));
	// Check the allocation.
	if(str == NULL) return 0;
	fgets(str,20,input);
	int number = atoi(str);
	free(str);
	printf("\nThe read number is %d!!",number);
	/************ Read the input parameters ************/

	/************ Allocate memory for important parameters and initialization ************/
	graph* gra = malloc(sizeof(graph));
	int* num = malloc(sizeof(int));
	int* compIndex = malloc(sizeof(int));
	gra->vertex = malloc((number+1)*sizeof(vertexNode));// My vertex starts at 1!So the length of them is number+1!
	int* visited = malloc((number+1)* sizeof(int));//This array saves whether a node has been visisted.
	int* component = malloc((number+1)* sizeof(int));//This array saves every node's component.
	int* memNum = malloc((number+1)* sizeof(int));//This array saves the number of different components
	if(visited==NULL || component==NULL || memNum==NULL || gra==NULL || compIndex==NULL || num==NULL || gra->vertex==NULL) return 0;
	*num = number;
	*compIndex = 0;
	for(int i=0;i<number+1;i++){
			visited[i]=0;
			memNum[i]=0;
		}
	/************ Allocate memory for important parameters ************/

	/************ Generate a graph and analyze it ,output the result************/
	from_file_to_graph(gra,input,num);
	show_list(gra, num);
	dfs(gra,visited, component, memNum, num, compIndex);
	printf("\nBelow is the result");
	memNum=realloc(memNum, (*compIndex+1)*sizeof(int));
	analysis(foutput, memNum, compIndex);
	/************ Generate a graph and analyze it ,output the result************/

	/************ free memomry and close files************/
	fclose(input);
	fclose(foutput);
	free(gra->vertex);
	free(gra);
	free(visited);
	free(component);
	free(memNum);
	free(num);
	free(compIndex);
	/************ free memomry and close files************/
	return 0;
}
