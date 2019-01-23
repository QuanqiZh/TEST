//
//head.h:
//This is the test program for the concerned functions in head.c. This program
//
// Author: Zhiquan Zhang, created on 9/5/2018
// All rights reserved
//
#ifndef HEAD_H_
#define HEAD_H_

/*
 * function that can apply memory for generating matrix
 * with assigned row and column. It returns a matrix with
 * assigned rows and columns.
 */
double** malloc_matrix(int n1, int n2);

/*
 * function that can release the memory that has been allocated for
 * a matrix.
 */
void free_matrix(int n1, int n2, double** a);

/*
 * function that can multiply two matrixes and return the result.
 * */
int matrix_multiply(int n1, int n2, int n3,
          double **a, double **b, double **c);

/*
 * function that can fill a matrix with the number between 0.0 and 10.0.
 * */
void fill_matrix(int n1, int n2, double **a);

/*
 * function that can print a matrix.
 * */
void print_matrix(int n1, int n2, double **a);

#endif /* HEAD_H_ */
