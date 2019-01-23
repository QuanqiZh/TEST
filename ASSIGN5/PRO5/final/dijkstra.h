//*******************************************************
//
//This file is the head file of jijkstra.h
//
//*******************************************************
#ifndef DIJKSTRA_H__
#define DIJKSTRA_H__
#include "read.h"
#include<stdio.h>

//This function return the shortest path between cities.
float dijkstra(int src, int des, int num_city, float** map);

#endif
