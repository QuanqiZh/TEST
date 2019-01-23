//*******************************************************
//
//This file is used to calculate the distance between cities.
//The input should be a file contains the magnitude and longtitude of some cities.
//Notice: this file should be used alone rather than used with other c files.
//
//*******************************************************
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI                      3.1415926
#define EARTH_RADIUS            6378.137        //The radius of the earth


double radian(double d);
double get_distance(double lat1, double lng1, double lat2, double lng2);


// get the arch
double radian(double d)
{
    return d * PI / 180.0;   //Transform angle
}


//Calculating the distance, the unit of output is kilometers.
double get_distance(double lat1, double lng1, double lat2, double lng2)
{
    double radLat1 = radian(lat1);
    double radLat2 = radian(lat2);
    double a = radLat1 - radLat2;
    double b = radian(lng1) - radian(lng2);
    
    double dst = 2 * asin((sqrt(pow(sin(a / 2), 2) + cos(radLat1) * cos(radLat2) * pow(sin(b / 2), 2) )));
    
    dst = dst * EARTH_RADIUS;
    dst= round(dst * 10000) / 10000;
    return dst;
}

//The program that can generate the distance between cities in the configuration files
int main (int argc, const char * argv[])
{
    double** points = malloc(10*sizeof(double*));
    
    if(points == NULL){
        printf("malloc error!");
        exit(1);
    }
    
    for(int i=0; i<10; i++){
        points[i] = malloc(sizeof(double)*2);
    }
    
    FILE* f1;
    FILE* f2;
    f1 = fopen("config_version2.txt","r");
    f2 = fopen("distance_version2.txt","w");
    
    
    //Belew are the process of generating the distances between cities.
    
    //Read the files
    for(int i=0;i<10;i++)
    {
        char* line = malloc(sizeof(char)*100);
        fgets(line,256,f1);
        points[i][0] = atof(line+1);
        points[i][1] = atof(line+11);
        printf("%f,%f\n",points[i][0],points[i][1]);
    }
    
    //Output the distances betwwen cities.
    for(int i=0;i<10;i++){
        for(int j=i+1;j<10;j++){
            float dst = get_distance(points[i][0], points[i][1], points[j][0], points[j][1]);
            printf("%c->%c:%f\n", 'A'+i,'A'+j,dst);
            fprintf(f2,"%c->%c:%f\n", 'A'+i,'A'+j,dst);
        }
    }
    
    //Output the time of transportation if speed is 20km/h
//    for(int i=0;i<10;i++){
//        for(int j=i+1;j<10;j++){
//            float dst = get_distance(points[i][0], points[i][1], points[j][0], points[j][1]);
//            printf("%c->%c:%d\n", 'A'+i,'A'+j,(int)(dst/20.0+0.5));
//            fprintf(f2,"%c->%c:%d\n", 'A'+i,'A'+j,(int)(dst/20.0+0.5));
//        }
//    }
    return 0;
}
