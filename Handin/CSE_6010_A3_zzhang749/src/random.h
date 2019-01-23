/*
 * random.h
 *
 *  Created on: Oct 10, 2018
 *      Author: mrisleyz
 */

#ifndef RANDOM_H_
#define RANDOM_H_

void rand_init(int rand_seed); // Initialize the random funtion to set time seed
double urand(); // Generate a random number uniformly distributed over the interval [0,1)
double randexp(double mean); // Returns -U*(log(1-urand()))


#endif /* RANDOM_H_ */
