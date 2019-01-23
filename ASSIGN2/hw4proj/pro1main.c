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
float p;
int number;
int len;

int main(int argc, char* argv[]){
	/************ Read the input parameters ************/
	if(argc<2) {
		printf("Wrong!");
		return 0;
	}
	len = atoi(argv[1]);
	p = atof(argv[2]);
	char* path = malloc(13*sizeof(char));
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
	for(int i=1;i<len+1;i++){
			for(int j=1;j<len+1;j++){
				printf("%d ",grid[i][j]);
			}
			printf("\n");
		}
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

	free(gra->vertex);
	free(gra);
	for(int i=0;i<len+1;i++){
		free(grid[i]);
	}
	free(grid);

	return 0;
}
