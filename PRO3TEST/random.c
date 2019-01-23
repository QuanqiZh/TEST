/*
 * random.c
 *
 *  Created on: Oct 10, 2018
 *      Author: mrisleyz
 */
#include <stdlib.h>
#include <math.h>
#include <time.h>

void rand_init(int rand_seed){
	if(rand_seed < 0){
		srand(time(NULL));
	}
	else{
		srand(rand_seed);
	}
}

double urand (){
	return (double)rand() / ((double)RAND_MAX+1);
}

double randexp(double mean){
	return -mean * (log(1.0-urand()));
}

