//
//pq.h:
//This file contains the declaration of the struct and different functions
//in the file "pg.c".
//
// Author: Zhiquan Zhang, created on 9/10/2018
// All rights reserved
//
#ifndef PQ_H_
#define PQ_H_

/*
 * Define the new struct of the data structure
 */
typedef struct PrioQ{
	double priority;
	void *data;
	struct PrioQ *next;
}PrioQ;

/*
 * The function that creates a new priority queue.
 */
PrioQ *PQ_create();

/*
 * Insert elements into a priority queue. The parameters are
 * head pointer *PQ of a priority, the priority key, the data pointer
 * *data.
 */
int PQ_insert(PrioQ *PQ, double key, void *data);

/*
 * Delete the element with highest priority in queue, and store
 * the key of the deleted item in the input pointer key.
 */
void* PQ_delete(PrioQ *PQ, double *key);

/*
 * count the number of the elements in a queue.
 */
unsigned int PQ_count(PrioQ *PQ);

/*
 * Release all memory allocated for a queue.
 */
void *PQ_free(struct PrioQ *PQ);
#endif /* PQ_H_ */
