//*******************************************************
//
//This file is the head file of read.c
//
//*******************************************************
#ifndef READ_H__
#define READ_H__
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
//Belew all some parameters used when calculating.
#define MIDSTRING 200
#define MAXNUM 1000
#define INF 1000

//This struct is used to save the data read in the file.
struct city_z{
    char name;
    double location_x;
    double location_y;
    int P;
    int I;
    int S;
    int E;
    int R;
}city_z;

//This function can read the basic information of a city like population
int Read_healthmap(char* path);

//This function can read the distance between cities.
float** Read_dis(char* path, int num_city);
#endif
