//
//graph.c:
//This file contains relevant function and parameters of the program.
//
#include"stdio.h"
#include"stdlib.h"
#include"pro1graph.h"

/*
 * Define global variables, "number" is the number of heads of the adjacency list.
 * "len" is the length of the matrix generated.
 */
extern int number;
extern int len;

/************ Function Definition ************/
int** graph_generate(double prob){
	//Check the parameter
	if(prob<0) return NULL;

	int num = 0;
	printf("Graph_generate begins\n");
	int** grid = malloc((len+2)*sizeof(int*));
	if(grid == NULL) return NULL;

	// Add 2 rows filled with zero as the first and last row.
	// Add 2 columns filled with zero as the most left and most right.
	// By doing this, when checking the neighbors of an element in the matrix,
	// we can avoid discussing the nodes in the corner or on the edge.
	for(int i=0;i<len+2;i++){
		grid[i] = malloc((len+2)*sizeof(int));
		if(grid[i] == NULL) return NULL;
	}

	for(int j=0;j<len+2;j++){
		grid[0][j]=0;
		grid[len+1][j]=0;
		grid[j][0]=0;
		grid[j][len+1]=0;
	}

	for(int i=1;i<len+1;i++){
		for(int j=1;j<len+1;j++){
			if(rand()%100 >= 100*prob)
				grid[i][j] = 0;
			else grid[i][j]=++num;
		}
	}
	number = num;
	return grid;
}
/************ Function Definition ************/


/************ Function Definition ************/
graph* create_graph(){
	graph* gra = malloc(sizeof(graph));
	gra->vertex_num=number;
	//gra->vertex = realloc(gra->vertex,(number+1)*sizeof(vertexNode));

	//
	gra->vertex = malloc((number+1)*sizeof(vertexNode));
	for(int i=1;i<gra->vertex_num+1;i++){
		gra->vertex[i].val=i;
		gra->vertex[i].firstedge=NULL;
	}
	return gra;
}
/************ Function Definition ************/


/************ Function Definition ************/
void insert_nextedge(edgeNode* edge, edgeNode* insert){
	//Check the parameter
	if(edge==NULL || insert == NULL) return;
	edgeNode* temp;
	temp = edge;
	while(temp->nextedge!=NULL){
		temp = temp->nextedge;
	}
	temp->nextedge = insert;
}
/************ Function Definition ************/


/************ Function Definition ************/
graph* checkNeighbors(int** grid, graph* gra){
	//Check the parameter
	if(grid==NULL || gra==NULL) return NULL;
	for(int i=1;i<len+1;i++){
		for(int j=1;j<len+1;j++){
			if(grid[i][j]!=0){
				//add nodes to the graph.
				if(grid[i-1][j]!=0){
					edgeNode* temp = malloc(sizeof(edgeNode));
					temp->val = grid[i-1][j];
					temp->nextedge = NULL;
					if(gra->vertex[grid[i][j]].firstedge!=NULL){
						insert_nextedge(gra->vertex[grid[i][j]].firstedge,temp);
					}else gra->vertex[grid[i][j]].firstedge = temp;
				}

				if(grid[i][j-1]!=0){
					edgeNode* temp = malloc(sizeof(edgeNode));
					temp->val = grid[i][j-1];
					temp->nextedge = NULL;
					if(gra->vertex[grid[i][j]].firstedge!=NULL){
						insert_nextedge(gra->vertex[grid[i][j]].firstedge,temp);
					}else gra->vertex[grid[i][j]].firstedge = temp;
				}

				if(grid[i][j+1]!=0){
					edgeNode* temp = malloc(sizeof(edgeNode));
					temp->val = grid[i][j+1];
					temp->nextedge = NULL;
					if(gra->vertex[grid[i][j]].firstedge!=NULL){
						insert_nextedge(gra->vertex[grid[i][j]].firstedge,temp);
					}else gra->vertex[grid[i][j]].firstedge = temp;
				}

				if(grid[i+1][j]!=0){
					edgeNode* temp = malloc(sizeof(edgeNode));
					temp->val = grid[i+1][j];
					temp->nextedge = NULL;
					if(gra->vertex[grid[i][j]].firstedge!=NULL){
						insert_nextedge(gra->vertex[grid[i][j]].firstedge,temp);
					}else gra->vertex[grid[i][j]].firstedge = temp;
				}

			}
		}
	}
	return gra;
}
/************ Function Definition ************/


/************ Function Definition ************/
void showList(graph* result){
	//Check the parameter
	if(result == NULL) return;
	for(int i=1;i<number+1;i++){
		printf("\n%d",i);
		if(result->vertex[i].firstedge==NULL) continue;
		else{
			printf(" %d",result->vertex[i].firstedge->val);
			edgeNode* temp;
			temp = result->vertex[i].firstedge;
			while(temp->nextedge!=NULL)
			{
				temp = temp->nextedge;
				if(temp->nextedge==NULL){
					printf(" %d",temp->val);
					break;
				}
				else printf(" %d",temp->val);
			}
		}
	}
}
/************ Function Definition ************/


/************ Function Definition ************/
void output(graph*result, FILE* fp){
	//Check the parameter
	if(result==NULL || fp==NULL) return;
	fprintf(fp, "%d", number);
	for(int i=1;i<number+1;i++){
		fprintf(fp, "\n");
		fprintf(fp, "%d", i);
		if(result->vertex[i].firstedge==NULL) continue;
		else{
			fprintf(fp, "\t%d", result->vertex[i].firstedge->val);
			edgeNode* temp;
			temp = result->vertex[i].firstedge;
			while(temp->nextedge!=NULL)
			{
				temp = temp->nextedge;
				if(temp->nextedge==NULL){
					fprintf(fp, "\t%d", temp->val);
					break;
				}
				else{
					fprintf(fp, "\t%d", temp->val);
				}
			}
		}
	}
}
/************ Function Definition ************/

