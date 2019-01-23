//
//  config.h
// The functions for read and check configuration file.
//
//  Created by Zhiquan Zhang on 10/13/18.
//  Copyright © 2018 Zhiquan Zhang. All rights reserved.
//

#ifndef config_h
#define config_h
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
// debug path: /Users/zzq/Library/Developer/Xcode/DerivedData/PRO3-byhaaesgrjbnokexbomezceopgzt

// Some special parameters for different memory allocation situations
#define MAXCOMPONENTS    100
#define MAXSTRING   100
#define MIDSTRING   50
#define MINSTRING   20
// Component types
#define     GENERATOR       0
#define     FORK            1
#define     QUEUE_STATION   2
#define     EXIT            3
//
// Generator Component
//
struct Generator {
    double IntArrTime;     // mean interarrival time for generated components
    int DestComp;          // ID of next component customers are sent to
};


//
// Queue_Station Component
//
struct Queue_Station{
    int numCust;
    struct FIFOQueue *Q;
    double AvgWaitTime;
    int DestComp;
};


//
// Fork Component
//
struct Fork{
    int num;
    double* probability;
    int* DestComp;
};


//
// Exit component
//
struct Exit {
    int Count;              // number of customers that exited at this component
};


//The function that can read the useful information from the configuration file
int read_file(FILE* f1);

//The function that print out the information that from the configuration file and saved in the component array.
void print_read(int totalNum1);

//The function that can check whether the probability in the fork component is legal or not.
void check_prob(int len, double* pro, int row);

//The function that can check whether the destination in the fork component is legal or not.
void check_dest_fork(int totalnum, int len, int* des, int row);

//The function that can check whether the probability in the queue station and generator component is legal or not.
void check_dest_queue_gen(int totalnum, int des, int row);

//The function that can check whether the numbers of probability and destination are legal.
void if_numofdest_equal_numofpro(int numofPro, int numofDest, int row);

//The function that can check whether the type character exsit.
void if_type_exsit(char typE, int row);

//The function that can check the fundamental format of every line, e.g., some special characters like '$', '%' and etc.
void check_format(char* ch, int row);
#endif /* config_h */
