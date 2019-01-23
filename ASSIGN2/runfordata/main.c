/*
 * \
 * main.c
 *
 *  Created on: Sep 20, 2018
 *      Author: zzq
 */
#include"stdio.h"
#include"stdlib.h"
#include"time.h"
#include"graph.h"
#include"string.h"

float p;
float step;
int number;
int len;
int compIndex;
int max;

int main(int argc, char* argv[]){
	/*if(argc<2) {
		printf("Wrong!");
		return 0;
	}
	len = atoi(argv[1]);
	char* path = malloc(13*sizeof(char));
	strcpy(path,argv[2]);
	strcat(path,".txt");*/

	FILE* fp;
	fp = fopen("./result.txt","w");
	srand(time(0));
	for(int i=1;i<=60;i++){
		compIndex=0;
		//printf("\n\nThe %dth loop is going",i);
		len = 500;
		p = i/100.0;
		printf("\n%f",p);
		int** grid = graph_generate(p);
		printf("\n%d",number);
		graph* gra = create_graph();
		//gra->vertex = malloc((number+1)*sizeof(vertexNode));
		gra = checkNeighbors(grid, gra);
		int* visited = malloc((number+1)* sizeof(int));
		int* component = malloc((number+1)* sizeof(int));
		int* memNum = malloc((number+1)* sizeof(int));

		for(int i=0;i<number+1;i++){
				visited[i]=0;
				memNum[i]=0;
		}
		dfs(gra,visited,component, memNum);
		memNum=realloc(memNum, (compIndex+1)*sizeof(int));
		analysis(memNum);
		output(fp,memNum);

		free(gra->vertex);
		free(gra);
		free(visited);
		free(component);
		free(memNum);
		for(int i=0;i<len+2;i++){
			free(grid[i]);
		}
		free(grid);
		printf("\n\n ");
	}
	fclose(fp);
	printf("\nAll is over!");
	return 0;
}
