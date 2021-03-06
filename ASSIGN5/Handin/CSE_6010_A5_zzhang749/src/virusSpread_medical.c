/*
 * virusSpread.c
 *
 *  Created on: Nov 18, 2018
 *      Author: mrisleyz
 */
#include "virusSpread_medical.h"
extern int mode;
//int main()
//{
//    srand( ( unsigned )time( NULL ) );
//    Initialize(city);
//    //    Print_City(city);
//    SIS_Diffusion(city);
//    //    Output_To_File();
//}

/*
 * Initialize the parameters of City struct
 */
void Initialize(struct City *city, struct city_z *cities){
    
    if(city==NULL || cities == NULL){
        fprintf(stderr, "read error\n"); exit(1);
    }
    
    for (int k = 1;k <= CITY_NUMBER; k++){
        city[k].population = cities[k-1].P;
        city[k].is_rescued = 0;
        city[k].start_time = 0;
        city[k].visited_time = 0;
        if( !( city[k].AdjacencyMatrix = ( int ** )malloc( sizeof( int * ) * ( city[k].population + 1 ) ) ) )
        {
            printf( "ERROR: **AdjecentMatrix malloc error.\n" );
            exit( -1 );
        }
        for( int i = 1; i <= city[k].population; i ++ )
            if( !( city[k].AdjacencyMatrix[i] = ( int * )malloc( sizeof( int ) * ( city[k].population + 1 ) ) ) )
            {
                printf( "ERROR: *AdjecentMatrix malloc error.\n" );
                exit( -1 );
            }
        // Initialize the adjacency matrix according to the average contact rate and city's population
        for (int i = 1;i<=city[k].population;i++){
            for (int j =1;j<=city[k].population;j++){
                double a = (rand() % 10000) * 0.0001;  // randomly get a number from 0 to 1
                //printf("a is %f ",a);
                //double a = 0.6;
                if(i==j){
                    city[k].AdjacencyMatrix[i][j]=1;
                }
                else if(i<j){
                    if (a <= ALPHA) {
                        city[k].AdjacencyMatrix[i][j]=1;
                    }
                    else{
                        city[k].AdjacencyMatrix[i][j]=0;
                    }
                }
                else{
                    city[k].AdjacencyMatrix[i][j]=city[k].AdjacencyMatrix[j][i];
                }
            }
        }
        if( !( city[k].vertex = ( int * )malloc( sizeof( int  ) * ( city[k].population + 1 ) ) ) )
        {
            printf( "ERROR: **AdjecentMatrix malloc error.\n" );
            exit( -1 );
        }
        if( !( city[k].temp_infected_this_step = ( int * )malloc( sizeof( int  ) * ( city[k].population + 1 ) ) ) )
        {
            printf( "ERROR: **AdjecentMatrix malloc error.\n" );
            exit( -1 );
        }
        if( !( city[k].is_visited_this_step = ( int * )malloc( sizeof( int  ) * ( city[k].population + 1 ) ) ) )
        {
            printf( "ERROR: **AdjecentMatrix malloc error.\n" );
            exit( -1 );
        }
        for(int i =1;i<=city[k].population;i++){
            city[k].vertex[i] = 0;
        }
        for(int i =1;i<=city[k].population;i++){
            city[k].temp_infected_this_step[i] = 0;
        }
        for(int i =1;i<=city[k].population;i++){
            city[k].is_visited_this_step[i] = 0;
        }
        if( !( city[k].sequence_of_infected_vertices = ( int ** )malloc( sizeof( int * ) * ( STEP + 1 ) ) ) )
        {
            printf( "ERROR: **Sequence Matrix malloc error.\n" );
            exit( -1 );
        }
        for( int i = 1; i <= STEP; i ++ )
            if( !( city[k].sequence_of_infected_vertices[i] = ( int * )malloc( sizeof( int ) * ( city[k].population + 1 ) ) ) )
            {
                printf( "ERROR: *Sequence Matrix malloc error.\n" );
                exit( -1 );
            }
        for( int i =1; i<= STEP;i++){
            for(int j=1; j<= city[k].population;j++){
                city[k].sequence_of_infected_vertices[i][j] = 0;
            }
        }
        
        city[k].sum_of_infected_vertices = 0;
        city[k].count_infected_neighbors = 0;
        city[k].count_infected_this_step = 0;
        city[k].count_recovered_this_step = 0;
        city[k].initial_infected_vertex = rand()%city[k].population+1;
        printf( "Initial = No.%d\n", city[k].initial_infected_vertex );
        city[k].vertex[city[k].initial_infected_vertex] = 1;
        
        city[k].sequence_of_infected_vertices[1][1] = city[k].initial_infected_vertex;
        city[k].sum_of_infected_vertices++;
        
    }
}


/*
 * Check the parameters of City struct through printing it
 */
void Print_City(struct City *city){
    if(city == NULL){
        fprintf(stderr, "read error\n"); exit(1);
    }
    
    for (int k=1;k<=CITY_NUMBER;k++){
        for(int i=1;i<=city[k].population;i++){
            for(int j=1;j<=city[k].population;j++){
                printf("%d ", city[k].AdjacencyMatrix[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

/*
 * SIS Diffusion program
 */
void SIS_Diffusion(struct City *city, float** map)
{
    if(city == NULL || map == NULL){
        fprintf(stderr, "read error\n"); exit(1);
    }
    
    // Infection rate and Recovery rate
    double rate_of_infection;
    double rate_of_recovery;
    // The rescue time is 10
    double rescue_time = 10;
    FILE* f = fopen("Statics.csv", "a");

    //The initial space of the hashtable is set twice as large as the city number.
    struct Element** VisitedCities = HashInit(CITY_NUMBER*2);
    
    struct Assistance* medical = malloc(sizeof(struct Assistance));
    if(medical==NULL){
        fprintf(stderr, "malloc error\n"); exit(1);
    }
    
    // Assistance struct paramters
    medical->location=1;
    medical->arrival_time=1;
    medical->depart_time=10;
    medical->speed=20.0;
    medical->VisitedCities=VisitedCities;
    // print the parameters to csv
    for(int i=1; i<11;i++){
        fprintf(f, "city%d,", i);
    }
    fprintf(f, "\n");
    
    // In the whole period of virus spread
    for( int step = 1; step <= STEP; step ++ )
    {
        for (int c = 1;c <= CITY_NUMBER;c++){
            
            int k = 1;
            // while the city is being rescued
            if(step>= medical->arrival_time && step<=medical->depart_time && c == medical->location){
                if(step==medical->arrival_time){
                    city[c].visited_time++;
                    //printf("%d %d %d %d\n",medical->arrival_time, medical->depart_time, medical->location,city[medical->location].visited_time);
                }
                rate_of_infection = 0.4*(1-0.1*city[c].visited_time);
                rate_of_recovery = 1 - rate_of_infection;
            }
            else{ // the city is not being rescued
                rate_of_infection = 0.6*(1-0.1*city[c].visited_time);
                rate_of_recovery = 1 - rate_of_infection;
            }
            
            //Emergency mode
            if(mode == 1){
                if(step == medical->depart_time){
                    //next_city is from 1-10
                    int next_city = count_max(city);
                    //printf("The next city is %d \n", next_city);
                    float path = dijkstra(medical->location-1, next_city-1, 10, map);
                    
                    int time_ontheway = (int)(path/medical->speed+0.5);
                    medical->arrival_time = medical->depart_time + time_ontheway;
                    medical->depart_time = medical->arrival_time + rescue_time;
                    medical->location = next_city;
                    //printf("%d %d %d\n", medical->arrival_time, medical->depart_time, medical->location);
                }
            }
            
            //Distance mode
            if(mode == 0){
                if(step == medical->depart_time){
                    //printf("%d %d %d %d\n",medical->arrival_time, medical->depart_time, medical->location,city[medical->location].visited_time);
                    //next_city is 0-9
                    int next_city = count_closet(medical->location-1,map,medical->VisitedCities);
                    //printf("The closet city is %d \n", next_city+1);
                    int time_ontheway = (int)(map[medical->location-1][next_city]/medical->speed+0.5);
                    //printf("Distacnce is %f\n", map[medical->location-1][next_city]);
                    //printf("Time on the way is %d\n", time_ontheway);
                    medical->arrival_time = medical->depart_time + time_ontheway;
                    medical->depart_time = medical->arrival_time + rescue_time;
                    medical->location = next_city+1;
                }
            }
            
            /* Traverse each the neighbors of node that is not being infected, count the total number of
             * infected node as k, then the node has probability 1 - ( 1 - beta ) ^ k to be infected. */
            for( int i = 1; i <= city[c].population; i ++ )
                if( city[c].vertex[i]) // Infectious i
                    for( int j = 1; j <= city[c].population; j ++ ) // Traverse i's neighbors
                        if( city[c].AdjacencyMatrix[i][j] && !city[c].vertex[j]&& !city[c].is_visited_this_step[j] ) // The neighbor j that is not infected
                        {
                            for( int k = 1; k <= city[c].population; k ++ )
                                if( city[c].AdjacencyMatrix[j][k] && city[c].vertex[k]) // Count the number of infected neighbors of j
                                    city[c].count_infected_neighbors ++;
                            city[c].infected_flag = rand() % ( city[c].population + 1 ) / ( double )city[c].population;
                            if( city[c].infected_flag <= 1 - pow( 1 - rate_of_infection, city[c].count_infected_neighbors ) )
                            {
                                city[c].temp_infected_this_step[j] = 1;
                                city[c].sequence_of_infected_vertices[step][k ++] = j;
                                city[c].count_infected_this_step ++;
                            }
                            city[c].is_visited_this_step[j] = 1;
                            city[c].count_infected_neighbors = 0;
                        }
            for( int i = 1; i <= city[c].population; i ++ )
                if( city[c].temp_infected_this_step[i] )
                    city[c].vertex[i] = 1;
            for( int i = 1; i <= city[c].population; i ++ )
                city[c].temp_infected_this_step[i] = 0;
            for( int i = 1; i <= city[c].population; i ++ )
                city[c].is_visited_this_step[i] = 0;

            /* Traverse all the infected nodes in the last step, and transform them into susceptible according to the recovery rate */
            for( int i = 1; i <= step - 1; i ++ )
                for( int j = 1; j <= city[c].population; j ++ )
                {
                    city[c].recovered_flag = rand() % ( city[c].population + 1 ) / ( double )city[c].population;
                    if( city[c].sequence_of_infected_vertices[i][j] && city[c].recovered_flag < rate_of_recovery )
                    {
                        city[c].vertex[city[c].sequence_of_infected_vertices[i][j]] = 0;
                        city[c].sequence_of_infected_vertices[i][j] = 0;
                        city[c].count_recovered_this_step ++;
                        city[c].sum_of_infected_vertices --;
                    }
                }
            /* Count the total number of infected people at this step */
            city[c].sum_of_infected_vertices += city[c].count_infected_this_step;
            //            sum_data_to_file[step] = sum_of_infected_vertices;
            printf( "Step = %d\n", step );
            printf( "Sum = %d\n", city[c].sum_of_infected_vertices );
            printf( "There are %d vertices newly infected this step.\n", city[c].count_infected_this_step );
            printf( "There are %d vertices newly recovered this step.\n\n", city[c].count_recovered_this_step );
            // sum_of_infected_vertices += count_infected_this_step;
            city[c].count_recovered_this_step = 0;
            city[c].count_infected_this_step = 0;
            fprintf(f, "%d,", city[c].sum_of_infected_vertices);
        }
        fprintf(f, "\n");
    }
    
    
    HashFree(VisitedCities,CITY_NUMBER*2);
    free(medical);
}

/*
 * Find the city with maximum number of infected people.
 */
int count_max(struct City *city){
    if(city == NULL){
        fprintf(stderr, "read error\n"); exit(1);
    }
    
    int max = 0;
    int max_id = 0;
    for(int i=1; i<1+CITY_NUMBER; i++){
        if(city[i].sum_of_infected_vertices > max){
            max = city[i].sum_of_infected_vertices;
            max_id = i;
        }
    }
    
    //This return is from 1-10
    return max_id;
}

/*
 * Find the nearest city.
 */
int count_closet(int loc, float** map,struct Element** VisitedCities){
    if(VisitedCities == NULL || map == NULL){
        fprintf(stderr, "read error\n"); exit(1);
    }
    
    float min = 10000.0;
    int closest_city;
    
    if(HashMapSize(VisitedCities,CITY_NUMBER*2)==10){
        HashMapClear(VisitedCities,CITY_NUMBER*2);
    }
    
    for(int i=0;i<10;i++){
        if(i==loc) continue;
        float temp = dijkstra(loc, i, CITY_NUMBER, map);
        if(temp<min && search(i+1,VisitedCities,CITY_NUMBER*2)==NULL){
            min = temp;
            closest_city = i;
        }
    }
    
    //Judge whether this city has been visited in a round
    //if(search(medical->location,VisitedCities,CITY_NUMBER)==NULL){
        //Distance mode will only allow the medical time to rescue a city once in a round;
    insert(closest_city+1,&closest_city,VisitedCities,CITY_NUMBER*2);
    //}
    
    //If all cities have been visited once, clear the HashMap
    
    //This return is from 0-9
    return closest_city;
}

/*
 * Free all the cities defined in Initialization
 */
void Free_Cities(struct City *city){
	for( int k = 1;k <= CITY_NUMBER; k++){
		for( int i = 1; i <= city[k].population; i ++ )
		{
			free( city[k].AdjacencyMatrix[i] );
			city[k].AdjacencyMatrix[i] = NULL;
		}
		free( city[k].AdjacencyMatrix );
		city[k].AdjacencyMatrix = NULL;
		free(city[k].vertex);
		city[k].vertex = NULL;
		free(city[k].temp_infected_this_step);
		city[k].temp_infected_this_step = NULL;
		free(city[k].is_visited_this_step);
		city[k].is_visited_this_step = NULL;
		for(int i = 1; i<STEP;i++){
			free(city[k].sequence_of_infected_vertices[i]);
			city[k].sequence_of_infected_vertices[i] = NULL;
		}
		free(city[k].sequence_of_infected_vertices);
		city[k].sequence_of_infected_vertices = NULL;
	}
}
