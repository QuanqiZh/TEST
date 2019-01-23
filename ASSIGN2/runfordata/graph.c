/*
 * graph.c
 *
 *  Created on: Sep 21, 2018
 *      Author: zzq
 */
#include"stdio.h"
#include"stdlib.h"
#include"graph.h"

extern int number;
extern int len;
extern int compIndex;
extern int max;
extern float p;

int** graph_generate(double prob){
	int num = 0;
	int** grid = malloc((len+2)*sizeof(int*));
	if(grid == NULL) return NULL;
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
			//printf("%d",grid[i][j]);
		}
	}
	number = num;
	return grid;
}

graph* create_graph(){
	graph* gra = malloc(sizeof(graph));
	gra->vertex = malloc((number+1)*sizeof(vertexNode));
	gra->vertex_num=number;
	//gra->vertex = realloc(gra->vertex,(number+1)*sizeof(vertexNode));
	for(int i=1;i<gra->vertex_num+1;i++){
		gra->vertex[i].val=i;
		gra->vertex[i].firstedge=NULL;
	}
	return gra;
}


void insert_nextedge(edgeNode* edge, edgeNode* insert){
	edgeNode* temp;
	temp = edge;
	while(temp->nextedge!=NULL){
		temp = temp->nextedge;
	}
	temp->nextedge = insert;
}

graph* checkNeighbors(int** grid, graph* gra){
	for(int i=1;i<len+1;i++){
		for(int j=1;j<len+1;j++){
			if(grid[i][j]!=0){
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

				//printf("One element over! It's [%d, %d]\n", i,j);
			}
		}
	}
	return gra;
}

void showList(graph* result){
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

void dfsExploreVertexNodes(graph* gra, vertexNode node, int* visited, int* component, int* memNum){
	if(visited[node.val]==1) return;
	visited[node.val]=1;
	if(node.firstedge==NULL){
		component[node.val] = compIndex;
		memNum[compIndex]+=1;
		return;
	}
	else {
		edgeNode* temp = node.firstedge;
		vertexNode vertex1;
		while(temp!=NULL){
			vertex1 = gra->vertex[temp->val];
			dfsExploreVertexNodes(gra,vertex1,visited,component, memNum);
			temp = temp->nextedge;
		}
		component[node.val] = compIndex;
		memNum[compIndex]+=1;
		return;
	}
}

void dfs(graph* result, int* visited, int* component, int* memNum){
	for(int i=1;i<number+1;i++)
	{
		if(visited[i]==1) continue;
		else{
			compIndex+=1;
			dfsExploreVertexNodes(result,result->vertex[i],visited,component,memNum);
		}
	}
}


void analysis(int* memNum){
	float sum=0;
	max=0;
	float average = 0;
	for(int i=1;i<compIndex+1;i++){
		sum+=memNum[i];
		if(memNum[i]>max) max = memNum[i];
	}
	average = sum / compIndex;
	printf("\nTotal component is %d",compIndex);
	printf("\nThe max group contains %d elements",max);
	printf("\nThe average is %f",average);
}

void output(FILE* output, int* memNum){
	float sum=0;
	max=0;
	float average = 0;
	for(int i=1;i<compIndex+1;i++){
		sum+=memNum[i];
		if(memNum[i]>max) max = memNum[i];
	}
	average = sum / compIndex;
	fprintf(output,"%f\t",p);
	fprintf(output,"%d\t",compIndex);
	fprintf(output,"%f\t",average);
	fprintf(output,"%d",max);
	fprintf(output,"\n");

}

