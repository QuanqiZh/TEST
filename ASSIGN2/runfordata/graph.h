/*
 * graph.h
 *
 *  Created on: Sep 21, 2018
 *      Author: zzq
 */

#ifndef GRAPH_H_
#define GRAPH_H_

typedef struct edgeNode{
	int val;
	struct edgeNode* nextedge;
}edgeNode;

typedef struct vertexNode{
	int val;
	edgeNode* firstedge;
}vertexNode;

typedef struct graph{
	int vertex_num;
	int edge_num;
	vertexNode *vertex;
}graph;

void fromStringtoGraph(graph* gra,FILE* input);
void dfsExploreVertexNodes(graph* gra, vertexNode node, int* visited, int* component, int* memNum);
void analysis(int* memNum);
void dfs(graph* result, int* visited, int* component, int* memNum);
int** graph_generate(double prob);
graph* create_graph();
void insert_nextedge(edgeNode* edge, edgeNode* insert);
graph* checkNeighbors(int** grid, graph* gra);
void showList(graph* result);
void output(FILE* output, int* memNum);
#endif /* GRAPH_H_ */
