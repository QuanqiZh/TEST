//
//main.c:
//This file contains test program of the priority queue data structure.
//It creates a queue and inserts 20 elements with different keys. Then it
//verifies the order of the elements deleted. Finally, the memory will be
//released.
//
// Author: Zhiquan Zhang, created on 9/10/2018
// All rights reserved
//
#include"pq.h"
#include"stdlib.h"
#include"stdio.h"
#include"time.h"
int main(){
	/************ Creating a priority queue ************/
	printf("Test begins!\n");
	PrioQ* pq1 = PQ_create();
	printf("Set Up! Now it contains %d elements\n", PQ_count(pq1));
	/************ Creating a priority queue ************/

	/************ Inserting different elements into the priority queue ************/
	srand((int)time(0));
	for(int i=1;i<=20;i++){
		float rand_var = rand()%10000/100.0;
		PQ_insert(pq1,rand_var,&rand_var);
		printf("After the %dth insert, total %d.\n", i, PQ_count(pq1));
	}
	/************ Inserting different elements into the priority queue ************/

	/************ Deleting elements into the priority queue ************/
	for(int i=1;i<=20;i++){
		printf("The %dth element deleted is, %f\n",i, pq1->next->priority);
		PQ_delete(pq1,&pq1->next->priority);
	}
	/************ Deleting elements into the priority queue ************/
	printf("\n\n\n");


	/************ Inserting different elements into the priority queue ************/
	for(int i=1;i<=20;i++){
		float rand_var = rand()%10000/100.0;
		PQ_insert(pq1,rand_var,&rand_var);
		printf("After the %dth insert, total %d.\n", i, PQ_count(pq1));
	}

	printf("\n\n");
	/************ Inserting different elements into the priority queue ************/

	/************ Releasing the memory ************/
	PQ_free(pq1);
	printf("The memory has been released\n"); //
	/************ Releasing the memory ************/
	return 0;
}
