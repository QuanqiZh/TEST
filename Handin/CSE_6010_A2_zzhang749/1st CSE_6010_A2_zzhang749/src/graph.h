//
//graph.h:
//This file contains the declaration of important functions and struts.
//The concrete information is in graph.c
//
// Author: Zhiquan Zhang, created on 9/26/2018
// All rights reserved
//

#ifndef GRAPH_H_
#define GRAPH_H_

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
 * The function that can turns a output file from last program to a adjacency list.
 */
void from_file_to_graph(graph* gra,FILE* input, int* number);

/*
 * The function that can insert a neighbor node of a node.
 */
void insert_nextedge(edgeNode* edge, edgeNode* insert);

/*
 * The function that can print the adjacency list.
 */
void show_list(graph* result, int* number);

/*
 * The function that can use DFS to search the adjacent vertexes of a single head node in the adjacency list.
 */
void dfs_explore_vertexNodes(graph* gra, vertexNode node, int* visited, int* component, int* memNum, int* compIndex);

/*
 * The function that can use DFS to search all head nodes in the adjacency list.
 */
void dfs(graph* result, int* visited, int* component, int* memNum, int* number, int* compIndex);

/*
 * The function that analyze the information of a graph and output the result in a ".txt" file.
 */
void analysis(FILE* output, int* memNum, int* compIndex);

#endif /* GRAPH_H_ */
