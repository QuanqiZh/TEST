//
//head.c:
//This file contains many functions that are relevant to this assignment such
//as the function allocate memory, release memory, multiply matrixes and etc.
//
// Author: Zhiquan Zhang, created on 9/5/2018
// All rights reserved
//
#include"stdio.h"
#include"stdlib.h"
#include"head.h"
#include"time.h"

/************	Function Definition ************/
double** malloc_matrix(int n1, int n2){
	//Allocate the first dimension's memory
	double** matrix =  malloc(n1*sizeof(double*));

	//Allocate the first dimension's memory
	for(int i=0;i<n1;i++)
	{
	matrix[i] = malloc(n2*sizeof(double));
	}

	//If the allocation fails due to the lack of memory, return NULL.
	if(matrix==NULL){
		printf("Failed!");
		return NULL;
	}
	return matrix;
}
/************	Function Definition ************/

/************	Function Definition ************/
void free_matrix(int n1, int n2, double** a){
	//Release the memory of the second'dimenson.
	for(int i=0;i<n1;i++){
		free(a[i]);
	}

	//Release the memory of the first'dimenson.
	free(a);
}
/************	Function Definition ************/

/************	Function Definition ************/
int matrix_multiply(int n1, int n2, int n3,
          double **a, double **b, double **c){
	if(a==NULL || b==NULL || n1 == 0 || n2 == 0) return 1;
	double sum = 0;

	//the multiplication of two matrixes.
	for(int i=0;i<n1;i++){
		for(int j=0;j<n3;j++){
			for(int k=0;k<n2;k++){
				sum += (a[i][k]*b[k][j]);
				if(k+1 == n2){
					c[i][j] = sum;
					sum=0;
					}
				}
			}
		}
	return 0;
}
/************	Function Definition ************/

/************	Function Definition ************/
void fill_matrix(int n1, int n2, double **a){
	// Generate the seed of a random number.
	srand((int)time(0));
	// Generate the random number between 0.0 and 10.0.
	for(int i=0;i<n1;i++){
		for(int j=0;j<n2;j++){
			//To get a double type element rather than int
			a[i][j]=((rand()%100)/10.0);
		}
	}
}
/************	Function Definition ************/

/************	Function Definition ************/
void print_matrix(int n1, int n2, double **a){
	// Print all the elements in the matrix.
	for(int i=0;i<n1;i++){
		for(int j=0;j<n2;j++){
			//The elements of the result would have two digits after the floating point.
			printf("%.2lf ",a[i][j]);
		}
		printf("\n");
	}
}
/************	Function Definition ************/

