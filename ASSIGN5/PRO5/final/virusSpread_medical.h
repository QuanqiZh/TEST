#ifndef V_M_H__
#define V_M_H__
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include "read.h"
# include "dijkstra.h"
# include "hashtable.h"
# define STEP 400 // 感染轮数
# define FILENAME_OUT "data_1.0.txt"
# define ALPHA 0.4
# define CITY_NUMBER 10

struct City{
    int population;
    int is_rescued;
    int start_time;
    int **AdjacencyMatrix;
    int *vertex;
    int visited_time;
    
    // record variables
    double infected_flag, recovered_flag;
    int initial_infected_vertex;
    int *temp_infected_this_step;
    int *is_visited_this_step;
    int sum_of_infected_vertices;
    int count_infected_neighbors;
    int count_infected_this_step;
    int count_recovered_this_step;
    int **sequence_of_infected_vertices;
    
}city[CITY_NUMBER +1];

struct Assistance{
    int location;
    int depart_time;
    int arrival_time;
    float speed;
    struct Element** VisitedCities;
}Assistance;

void Free_AdjacencyMatrix(int sum_of_vertex, int **AdjacencyMatrix);
void SIS_Diffusion(struct City *city, float** map);
void Initialize(struct City *city, struct city_z *cities);
void Print_City(struct City *city);
int count_max(struct City *city);
int count_closet(int loc, float** map,struct Element** VisitedCities);

#endif
