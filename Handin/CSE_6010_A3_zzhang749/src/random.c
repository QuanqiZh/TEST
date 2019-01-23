/*
 * random.c
 *
 *  Created on: Oct 10, 2018
 *      Author: mrisleyz
 */
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Initialize the random funtion to set time seed
void rand_init(int rand_seed){
    if(rand_seed < 0){
        srand(time(NULL));
    }
    else{
        srand(rand_seed);
    }
}

// Generate a random number uniformly distributed over the interval [0,1)
double urand (){
    return (double)rand() / ((double)RAND_MAX+1);
}

// Returns -U*(log(1-urand()))
double randexp(double mean){
    return -mean * (log(1.0-urand()));
}

