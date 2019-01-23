#include <stdlib.h>
#include <stdio.h>
#include "heapSort.h"
#include "insertionSort.h"
#include "mergeSort.h"
#include "quickSort.h"
#include "countingSort.h"

int main()
{
    
    int array[]={0,14,10,8,7,9,3,2,4,1,23,14,12};
    int len=13;
    
    //Heapsort(array,len);
    
    //insertionSort(array,len);
    
    int* result = countSort(array,len);
    for (int i=0; i<len; i++)
    {
        printf("%d\n",result[i]);
    }
 
    return 0;
}
