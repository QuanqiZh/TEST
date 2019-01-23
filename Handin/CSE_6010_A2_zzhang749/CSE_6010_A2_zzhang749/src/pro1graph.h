//
//graph.h:
//This file contains the declaration of important functions and struts.
//The concrete information is in graph.c
//
// Author: Zhiquan Zhang, created on 9/26/2018
// All rights reserved
//
#ifndef PRO1GRAPH_H_
#define PRO1GRAPH_H_

/*
 * edgeNode is the struct that serves as the neighbor nodes of the adjacency list's head node.
 */
typedef struct edgeNode{
	int val;
	struct edgeNode* nextedge;
}edgeNode;

/*
 * vertexNode is the node that serves as the head node of the adjacency list.
 */
typedef struct vertexNode{
	int val;
	edgeNode* firstedge;
}vertexNode;

/*
* graph contains the adjacency list's all head nodes' pointer and the number of vertex.
*/
typedef struct graph{
	int vertex_num;
	int edge_num;
	vertexNode *vertex;
}graph;

/*
 * Generate the initial matrix.
 */
int** graph_generate(double prob, int* numberofVertex, int* length);

/*
 * Create a adjacency list, which only contains head nodes, based on the generated matrix's property.
 */
graph* create_graph(int* numberofVertex);

/*
 * Check the matrix and add the neighbor nodes of the adjacency list's head node.
 */
graph* check_neighbors(int** grid, graph* gra, int* length);

/*
 * The function that can insert a neighbor node of a node.
 */
void insert_nextedge(edgeNode* edge, edgeNode* insert);

/*
 * The function that can print the adjacency list.
 */
void show_list(graph* result);

/*
 * The function that can print the adjacency list.
 */
void output(graph*result, FILE* fp);
#endif /* PRO1GRAPH_H_ */

