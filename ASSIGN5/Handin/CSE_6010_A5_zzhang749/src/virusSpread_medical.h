#ifndef V_M_H__
#define V_M_H__
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include "read.h"
# include "dijkstra.h"
# include "hashtable.h"
# define STEP 400 // Total infection times
# define ALPHA 0.5 // Average contact rate
# define CITY_NUMBER 10 // Total city number

struct City{
	// Paramters in City struct
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

// Assistance struct
struct Assistance{
    int location;
    int depart_time;
    int arrival_time;
    float speed;
    struct Element** VisitedCities;
}Assistance;

// SIRS virus spread function
void SIS_Diffusion(struct City *city, float** map);
// Initialize all parameters in City struct
void Initialize(struct City *city, struct city_z *cities);
// Check the parameters in City struct
void Print_City(struct City *city);
// Find the city with maximum number of infected people
int count_max(struct City *city);
// Find the nearest city
int count_closet(int loc, float** map,struct Element** VisitedCities);
// Free the City struct
void Free_Cities(struct City *city);

#endif
