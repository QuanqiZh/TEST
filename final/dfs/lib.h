#ifndef LIB_H__
#define LIB_H__
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

#endif
