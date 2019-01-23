//
//graph.c:
//This file contains relevant function and parameters of the program.
//
#include"stdio.h"
#include"stdlib.h"
#include"graph.h"

/*
 * Define global variables, "number" is the number of heads of the adjacency list.
 * "compIndex" is the number of known component. "max" is the size of the largest
 * component.
 */
extern int number;
extern int compIndex;
extern int max;

/************ Function Definition ************/
void fromStringtoGraph(graph* gra,FILE* input){
	//Check the parameter
	if(gra == NULL || input == NULL) return;
	for(int j=0;j<number;j++){
		// 64 can be changed as long as it's larger than 34(5*6+4).
		char* ch = malloc(64*sizeof(char));
		fgets(ch,64,input);
		for(int i=0;i<64;i++){
			if(ch[i]=='\0') break;
			if(i==0){
				gra->vertex[atoi(ch)].val=atoi(ch);
				gra->vertex[atoi(ch)].firstedge=NULL;
				continue;
			}
			else if(ch[i]=='\t'){
				edgeNode* temp = malloc(sizeof(edgeNode));
				temp->val = atoi(ch+i+1);
				temp->nextedge = NULL;
				if(gra->vertex[atoi(ch)].firstedge!=NULL){
					insert_nextedge(gra->vertex[atoi(ch)].firstedge,temp);
				}else gra->vertex[atoi(ch)].firstedge = temp;
			}
		}
		free(ch);
	}
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
void showList(graph* result){
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
				printf(" %d",temp->val);
			}
		}
	}
}
/************ Function Definition ************/

/************ Function Definition ************/
void dfsExploreVertexNodes(graph* gra, vertexNode node, int* visited, int* component, int* memNum){
	if(gra==NULL || visited == NULL || component==NULL || memNum == NULL) return;
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
/************ Function Definition ************/

/************ Function Definition ************/
void dfs(graph* result, int* visited, int* component, int* memNum){
	//Check the parameter
	if(result==NULL || visited == NULL || component==NULL || memNum == NULL) return;
	//Iterate every node of the adjacency list.
	for(int i=1;i<number+1;i++)
	{
		if(visited[i]==1) continue;
		else{
			compIndex+=1;
			dfsExploreVertexNodes(result,result->vertex[i],visited,component,memNum);
		}
	}
}
/************ Function Definition ************/

/************ Function Definition ************/
void analysis(int* memNum){
	//Check the parameter
	if(memNum==NULL) return;
	float sum=0;
	max=0;
	float average = 0;
	for(int i=1;i<compIndex+1;i++){
		sum+=memNum[i];
		if(memNum[i]>max) max = memNum[i];
	}
	average = sum / compIndex;
	printf("\nTotal is %d",compIndex);
	printf("\nThe max group contains %d elements\n",max);
	printf("\nThe average is %f",average);
}
/************ Function Definition ************/

/************ Function Definition ************/
void output(FILE* output, int* memNum){
	//Check the parameter
	if(output==NULL || memNum ==NULL) return;
	int* hist = malloc((max+1)*sizeof(int));
	//Check whether it's successful.
	if(hist == NULL) return;
	float sum=0;
	max=0;
	float average = 0;
	for(int i=1;i<compIndex+1;i++){
		sum+=memNum[i];
		if(memNum[i]>max) max = memNum[i];
	}
	average = sum / compIndex;

	fprintf(output,"%d",compIndex);
	fprintf(output,"\n");
	fprintf(output,"%f",average);
	fprintf(output,"\n");
	fprintf(output,"%d",max);

	// calculate the histogram.
	for(int i=0;i<(max+1);i++){
		hist[i]=0;
	}

	for(int i=1;i<compIndex+1;i++){
		hist[memNum[i]]++;
	}

	for(int i=1;i<max+1;i++){
		fprintf(output,"\n");
		fprintf(output,"%d %d",i, hist[i]);
	}
}
/************ Function Definition ************/
