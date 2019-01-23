//
//pq.c:
//This file contains many functions that are relevant to this assignment such as
//creating a priority queue, inserting elements into the queue, deleting elements,
//counting the number of the elements in the queue, releasing the memory allocated for queue.
//
// Author: Zhiquan Zhang, created on 9/10/2018
// All rights reserved
//
#include"stdlib.h"
#include"stdio.h"
#include"pq.h"

/************ Function Definition ************/
PrioQ *PQ_create(){
	PrioQ *pq = malloc(sizeof(PrioQ));
	// If there is no enough memory, return NULL.
	if(pq==NULL) return NULL;
	pq->next=NULL;
	return pq;
}
/************ Function Definition ************/

/************ Function Definition ************/
int PQ_insert(PrioQ *PQ, double key, void *data){
		if(PQ==NULL) return 0;
		PrioQ* newNode = PQ_create();
		if(newNode==NULL) return 0;
		// Inserting the first node.
		if(PQ->next==NULL){
			PQ->next = newNode;
			newNode->data=data;
			newNode->priority=key;
			newNode->next = NULL;
		}

		// Inserting other nodes.
		else{
		PrioQ* temp = PQ_create();
		if(temp == NULL) return 0;
		temp = PQ;
		while(temp->next!=NULL && temp->next->priority<key){
			temp = temp->next;
		}

		PrioQ* nextNode = PQ_create();
		//Memory not enough.
		if(nextNode==NULL) return 0;
		nextNode = temp->next;
		temp->next = newNode; //
		newNode->data=data;
		newNode->priority=key;
		newNode->next = nextNode;
		}
	return 1;
}
/************ Function Definition ************/

/************ Function Definition ************/
void* PQ_delete(PrioQ *PQ, double *key){
	if(PQ == NULL) return NULL;
	PrioQ *temp = PQ->next;
	void* data1 = PQ->next->data;
	key = &PQ->next->priority;
	PQ->next = PQ->next->next;
	free(temp);
	return data1;
}
/************ Function Definition ************/

/************ Function Definition ************/
unsigned int PQ_count(PrioQ *PQ){
	PrioQ *begin = PQ;
	if(PQ == NULL){
		printf("No Priority Queue exists!");
		return 0;
	}
	unsigned int result = 0;
	while(PQ->next!=NULL){
		result++;
		PQ=PQ->next;
	}
	PQ = begin;
	return result;
}
/************ Function Definition ************/

/************ Function Definition ************/
void *PQ_free(PrioQ *PQ){
	if(PQ == NULL) return NULL;
	int i=0;
	printf("Free begins!\n");
	while(PQ->next!=NULL){
		PrioQ *temp = PQ->next;
		PQ->next = PQ->next->next;
		free(temp);
		printf("The %dth element has been deleted\n",++i);
	}
	free(PQ);
	return NULL;
}
/************ Function Definition ************/

