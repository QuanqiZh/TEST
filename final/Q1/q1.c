#include "stdio.h"
#include "time.h"
#include "stdlib.h"

int main(int argc, char* argv[]){
    
    int* pos = malloc(sizeof(int)*2);
    if(pos==NULL){
        printf("Malloc error!");
        exit(1);
    }
    
    FILE* f1;
    f1 = fopen("Position.txt","w");
    
    pos[0] = 0;
    pos[1] = 0;
    
    srand((int)time(0)); // ????????? int type
    
    
    for(int i=0; i<100; i++){
        int random_num = rand()%100;
        
        //North
        if(random_num<30){
            pos[1]++;
        }

        //East
        if(random_num<50 && random_num>=30){
            pos[0]++;
        }
        
        //South
        if(random_num<75 && random_num>=50){
            pos[1]--;
        }
        
        //West
        if(random_num<90 && random_num>=75){
            pos[0]--;
        }
        
        fprintf(f1,"%d %d\n",pos[0],pos[1]);
    }
    
    printf("Over!\n");
    return 0;
}
