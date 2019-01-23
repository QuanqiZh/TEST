//*******************************************************
//
//This file is used to read the data in configuration files.
//The input should be a map and the srouce city, target city.
//
//*******************************************************
#include "read.h"
extern struct city_z cities[MAXNUM];

//This function can read the configuration file and save the data into a struct array.
//The input should be a special file in a special format.
int Read_healthmap(char* path) {
    
    if(path == NULL){
        fprintf(stderr, "read error\n"); exit(1);
    }
    
    //Open file and alloc memory for every line
    FILE* f1;
    f1 = fopen(path,"r");
    char* st = malloc(sizeof(char)*MIDSTRING);
    if(st==NULL){
        fprintf(stderr, "malloc error\n"); exit(1);
    }
    fgets(st, MIDSTRING, f1);
    
    //Get the total number of cities and allocate memory for the cities
    int index;
    for(int i=0;i<strlen(st);i++){
        if(st[i]==':') index = i;
    }
    int num_city = atoi(st+1+index);
    //struct city* cities = malloc(num_city*sizeof(city));
    fgets(st, MIDSTRING, f1);
    
    //Read cities data
    for(int i=0;i<num_city;i++){
        fgets(st, MIDSTRING, f1);
        int* b_index = malloc(2*sizeof(int));
        
        if(b_index==NULL){
            fprintf(stderr, "malloc error\n"); exit(1);
        }
        
        int* c_index = malloc(7*sizeof(int));
        if(c_index==NULL){
            fprintf(stderr, "malloc error\n"); exit(1);
        }
        
        int k=0;
        
        //Read the whole file and save all the data in the array.
        for(int j=0; j<MIDSTRING; j++){
            if(st[j]=='(') b_index[0] = j;
            if(st[j]==')') b_index[1] = j;
            if(st[j]==',') c_index[k++] = j;
        }
        
        char name = st[0];
        double x = atof(st+b_index[0]+1);
        double y = atof(st+c_index[1]+1);
        int population = atoi(st+c_index[2]+1);
        int inf = atoi(st+c_index[3]+1);
        int suc = atoi(st+c_index[4]+1);
        int exp = atoi(st+c_index[5]+1);
        int rec = atoi(st+c_index[6]+1);
        
        cities[i].name = name;
        cities[i].location_x = x;
        cities[i].location_y = y;
        cities[i].P = population;
        cities[i].I = inf;
        cities[i].S = suc;
        cities[i].E = exp;
        cities[i].R = rec;
    }
    
    return num_city;
}


//This function can generate a map that save the distance between different cities.
//The output map is used when the medical team tranfers from one city to another.
float** Read_dis(char* path, int num_city){
    if(path == NULL){
        fprintf(stderr, "read error\n"); exit(1);
    }
    
    FILE* f1;
    f1 = fopen(path,"r");
    
    float** map = malloc(num_city*sizeof(float*));
    
    if(map == NULL){
        fprintf(stderr, "malloc error\n"); exit(1);
    }
    
    for(int i=0;i<num_city;i++){
        map[i] = malloc(num_city*sizeof(float));
        if(map[i] == NULL){
            fprintf(stderr, "read error\n"); exit(1);
        }
    }
    
    for(int i=0;i<num_city;i++){
        for(int j=0;j<num_city;j++){
            map[i][j] = INF;
        }
    }
    
    for(int i=0; i<num_city*num_city; i++){
        char* line = malloc(sizeof(char)*MIDSTRING);
        if(line == NULL){
            fprintf(stderr, "malloc error\n"); exit(1);
        }
        fgets(line, MIDSTRING, f1);
        if(strlen(line)<=1) break;
        map[line[0]-'A'][line[3]-'A'] = atof(line+5);
        map[line[3]-'A'][line[0]-'A'] = atof(line+5);
    }
    
    return map;
}
