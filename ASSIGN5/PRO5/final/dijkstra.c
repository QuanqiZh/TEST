//*******************************************************
//
//This file is used to calculate the shortest paths.
//The input should be a map and the srouce city, target city.
//
//*******************************************************
#include "dijkstra.h"

float dijkstra(int src, int des, int num_city, float** map){
    
    //Check parameters
    if(map==NULL){
        fprintf(stderr, "read error\n"); exit(1);
    }
    
    //Initialization
    
    //If the destination and srouce city are the same, directly return 0.
    if(des == src) return 0;
    float len[num_city];
    int visited[num_city];
    int SIZE = num_city;
    
    for(int i=0; i<SIZE; i++){
        len[i] = map[src][i];
        visited[i] = -1;
        
    }
    
    //Read all the cities' distance and calculating the shortest path
    for(int i=0; i<SIZE; i++){
        int min = INF;
        int index = 0;
        
        //Visited updated, find the newest min in len
        for(int j=0; j<SIZE; j++){
            if(visited[j]!=1 && len[j]<min ){
                index = j;
                min = len[j];
            }
        }
        
        visited[index]=1;
        
        //Use the min to update len[]
        for(int j=0; j<SIZE; j++){
            if(visited[j]!=1 && ((len[index]+map[index][j])<len[j]))
                len[j] = len[index]+map[index][j];
        }
    }
    
    //Return the shortest path's value
    return len[des];
}
