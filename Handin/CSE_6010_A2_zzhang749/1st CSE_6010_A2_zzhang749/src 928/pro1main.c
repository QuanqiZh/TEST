//
//main.c:
//This file contains program that can generate a graph
//based on the theory of the paper in the assignment.
//It can also turn the graph into the form of adjacency
//list and output a file that contains the number of vertexes
//and the list.
//
// Author: Zhiquan Zhang, created on 9/26/2018
// All rights reserved
//
#include"stdio.h"
#include"stdlib.h"
#include"time.h"
#include"pro1graph.h"
#include"string.h"

int number;// "number" is the number of the vertex of a graph.
int len;//"len" is the size of the grid.

int main(int argc, char* argv[]){
	/************ Read the input parameters ************/
	if(argc<2) {
		printf("Wrong!");
		return 0;
	}
	len = atoi(argv[1]);
	float p = atof(argv[2]);
	char* path = malloc(13*sizeof(char));
	if(path==NULL) return 0;
	strcpy(path,argv[3]);
	strcat(path,".txt");
	/************ Read the input parameters ************/

	/************ Open file and initialize random function ************/
	FILE* fp;
	fp = fopen(path,"w");
	srand(time(0));
	/************ Open file and initialize random function ************/

	/************ Create the graph's adjacency list's head ************/
	int** grid = graph_generate(p);
	graph* gra = create_graph();
	/************ Create the graph's adjacency list's head ************/

	/************ Create the graph's adjacency list's other part ************/
	gra = checkNeighbors(grid, gra);
	/************ Create the graph's adjacency list's other part ************/

	/************ Print and save the adjacency list ************/
	showList(gra);
	output(gra,fp);
	printf("\nAll is over!");
	/************ Print and save the adjacency list ************/

	/************ Free Memory************/
	free(gra->vertex);
	free(gra);
	for(int i=0;i<len+2;i++){
		free(grid[i]);
	}
	free(grid);
	/************ Free Memory************/

	return 0;
}
