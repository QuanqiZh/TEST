#include <stdlib.h>
#include <stdio.h>

int* countSort(int a[], int SIZE){
    
    int* c = malloc(sizeof(int)*SIZE);
    
    for(int i=0;i<SIZE;i++){
        c[i]=0;
    }
    
    int max = 0;
    
    for(int i=0; i<SIZE; i++){
        if(a[i]>=max) max = a[i];
    }
    
    int* b = malloc(sizeof(int)*(max+1));
    
    for(int i=0;i<max+1;i++){
        b[i]=0;
    }
    
    for (int i = 0; i < SIZE; i++)
    {
        b[a[i]]++;
    }
    for (int i = 1; i < max + 1; i++)
    {
        b[i] = b[i] + b[i - 1];
    }
    for (int i = 0; i < SIZE; i++)
    {
        b[a[i]]--;
        c[b[a[i]]] = a[i];
    }
    return c;
    
}
