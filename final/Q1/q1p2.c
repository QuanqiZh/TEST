#include "stdio.h"
#include "time.h"
#include "stdlib.h"
#include "math.h"

int main(int argc, char* argv[]){
    
    int* pos = malloc(sizeof(int)*2);
    if(pos==NULL){
        printf("Malloc error!");
        exit(1);
    }
    
    FILE* f1;
    FILE* f2;
    f1 = fopen("Position.txt","r");
    f2 = fopen("Distance.txt","w");
    int index = 0;
    for(int i=0; i<100; i++){
        char* line = malloc(sizeof(char)*10);
        fgets(line,5,f1);
        int x = atoi(line);
        
        while(line[index]!=' ') index++;
        
        int y = atoi(line+index);
        
        double distance = sqrt(x*x+y*y);
        fprintf(f2,"%f\n",distance);
    }
    
    printf("Over!\n");
    return 0;
}

