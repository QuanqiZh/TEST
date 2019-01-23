//
//main.c:
//This is the test program for the concerned functions in head.c. This program
//can help check whether the functions could work smoothly. The output is the
//multiplication of two matrixes.
//
// Author: Zhiquan Zhang, created on 9/5/2018
// All rights reserved
//
#include"head.h"
#include"stdio.h"

int main(){
/************	Initialize matrixes separately ************/
	double** A = malloc_matrix(4,3);
	double** B = malloc_matrix(3,2);
	double** C = malloc_matrix(4,2);
/************	Initialize matrixes separately ************/

/************	Fill the input matrixes with random number ************/
	fill_matrix(4,3,A);
	fill_matrix(3,2,B);
/************	Fill the input matrixes with random number ************/

/************	Multiply two matrixes ************/
	matrix_multiply(4,3,2,A,B,C);
/************	Multiply two matrixes ************/

/************	Print the result  ************/
	printf("This is the input matrix A\n");
	print_matrix(4,3,A);
	printf("\n");
	printf("This is the input matrix B\n");
	print_matrix(3,2,B);
	printf("\n");
	printf("This is the result matrix C\n");
	print_matrix(4,2,C);
/************	Print the result  ************/
	return 0;
}
