//
//  main.c
//  PRO4
//
//  Created by Zhiquan Zhang on 10/19/18.
//  Copyright © 2018 Zhiquan Zhang. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"
#include "omp.h"
#include "time.h"
#include "math.h"

#define SIZE 800
#define K 7

int main(int argc, const char * argv[]) {
    
    FILE* f = fopen("handin-test.txt", "a");
    
    //Allocate memory for three matrixes
    double** A = malloc(sizeof(double*)*SIZE);
    for(int i=0; i<SIZE; i++){
        A[i] = malloc(sizeof(double)*SIZE);
    }
    
    double** B = malloc(sizeof(double*)*SIZE);
    for(int i=0; i<SIZE; i++){
        B[i] = malloc(sizeof(double)*SIZE);
    }
    
    double** C = malloc(sizeof(double*)*SIZE);
    for(int i=0; i<SIZE; i++){
        C[i] = malloc(sizeof(double)*SIZE);
    }
    
    
    double sum = 0.0; //This variable serves to verify my code's corecctness.
    srand(time(0));
        
    //Initialize all variables
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            A[i][j] = (rand()%10)/10.0;
            B[i][j] = (rand()%10)/10.0;
            C[i][j] = 0.0;
        }
    }
    
    //Sequential to get the sum of the result matrix
    double start = omp_get_wtime();
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            for(int k=0; k<SIZE; k++){
                C[i][j] += (A[i][k]*B[k][j]);
            }
            sum += C[i][j];
        }
    }
    double seq_t = omp_get_wtime()-start;
    printf("Accoding to sequential, sum is %f\n", sum);
    printf("The time is %f\n", seq_t);
    
    //Let all variables be zero to recalculate in another method.
    for(int i=0;i<SIZE;i++){
        for(int j=0; j<SIZE; j++){
            C[i][j] = 0.0;
        }
    }
    sum = 0.0;
    
    
    //Static mapping method to calculate the final result
    omp_set_num_threads(K);
    start = omp_get_wtime();
    #pragma omp parallel
    {
        int j, nthrds;
        double myC;
        int ID=omp_get_thread_num();
        int num_threads=omp_get_num_threads();
        for(int n=ID; n<SIZE; n+=K){
            for(int i=0; i<SIZE; i++){
                for(j=0, myC=0.0; j<SIZE; j++){
                    myC += (A[n][j]*B[j][i]);
                }
                C[n][i] = myC;
                #pragma omp critical
                {
                    sum += myC;
                }
            }
        }
    }
    double sta_map_t = omp_get_wtime()-start;
    printf("Static parallel sum is %f\n", sum);
    printf("The time is %f\n", sta_map_t);
    
    //Let all variables be zero to recalculate in another method.
    for(int i=0;i<SIZE;i++){
        for(int j=0; j<SIZE; j++){
            C[i][j] = 0.0;
        }
    }
    sum = 0.0;
    
    
    //Dynamic mapping method to calculate the final result
    omp_set_num_threads(K);
    start = omp_get_wtime();
    int rank = 0;
    #pragma omp parallel
    {
        while(rank<SIZE){
            int j;
            double myC;
            int ID=omp_get_thread_num();
            int num_threads=omp_get_num_threads();
            int n;
            
            //critical part, prevent race for rank
            #pragma omp critical
            {
                n=rank;
                rank++;
            }
            for(int i=0; i<SIZE; i++){
                for(j=0, myC=0.0; j<SIZE; j++){
                    myC += (A[n][j]*B[j][i]);
                }
                C[n][i] = myC;
                #pragma omp critical
                {
                    sum += myC;
                }
            }
        }
    }
    double dyn_map_t = omp_get_wtime()-start;
    
    //Output the final results of computation
    printf("Dynamic parallel sum is %f\n", sum);
    printf("The time is %f\n", dyn_map_t);
    printf("The sta K is %f\n",seq_t/sta_map_t);
    printf("The dyn K is %f\n",seq_t/dyn_map_t);
    printf("K is %d\n", K);
    fprintf(f,"%d %d %f %f %f %f %f\n", K, SIZE, seq_t, sta_map_t, dyn_map_t, seq_t/sta_map_t, seq_t/dyn_map_t);
    
    //Free memory and close file
    for(int i=0; i<SIZE; i++){
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    
    free(A);
    free(B);
    free(C);
    fclose(f);
    
    return 1;
}

