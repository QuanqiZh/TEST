//
//  main.c
//  PRO5
//
//  Created by Zhiquan Zhang on 11/23/18.
//  Copyright © 2018 Zhiquan Zhang. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "read.h"
#include "dijkstra.h"
#include "virusSpread_medical.h"

//The medical mode. 1 and 0 represents two modes. 1 is emergency mode. 0 is distance mode.
int mode;

//The struct used to save the read data.
struct city_z cities[MAXNUM];

//The struct used to simulate the virus circulation process.
struct City city[CITY_NUMBER +1];

int main(int argc,  char * argv[]) {
    //parameters check.
    char* path1 = malloc(sizeof(char)*20);
    if(path1 == NULL){
        fprintf(stderr, "malloc error\n"); exit(1);
    }
    char* path2 = malloc(sizeof(char)*20);
    if(path2 == NULL){
        fprintf(stderr, "malloc error\n"); exit(1);
    }
    
    path1 = argv[1];
    path2 = argv[2];
    mode = atoi(argv[3]);
    
    //Have to choose mode 1 or mode 0.
    if(mode!=1 && mode!=0){
        printf("mode can only be 1 or 0!");
        exit(1);
    }
        
    printf("You have chosen the mode %d\n",mode);
    
    int num_city = Read_healthmap(path1);
    
    //Read the map and generate a map.
    float** map = malloc(num_city*sizeof(float*));
    
    if(map == NULL){
        fprintf(stderr, "malloc error\n"); exit(1);
    }
    
    for(int i=0;i<num_city;i++){
        map[i] = malloc(num_city*sizeof(float));
    }
    
    map = Read_dis(path2, num_city);
    
    srand( ( unsigned )time( NULL ) );
    
    //Initialization all the data and begin to simulate the process.
    Initialize(city,cities);
    SIS_Diffusion(city,map);

    
    //Free all the parameters.
    Free_Cities(city);
    for (int i=0;i<num_city;i++){
        free(map[i]);
        map[i] = NULL;
    }
    free(map);
    map = NULL;

    
    return 0;
}
