/*
 * application.h
 *
 *  Created on: Oct 12, 2018
 *      Author: mrisleyz
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#define     GENERATE    0
#define     ARRIVAL     1
#define     DEPARTURE   2

// A single data structure is used to handle all three event types
struct EventData {
    int EventType;              // Type of event (GENERATE, ARRIVAL, DEPARTURE)
    struct Customer *Cust;      // Arriving or departing customer; unused for GENERATE events
    int CompID;                 // ID of component where customer created, arrives, or departs
};

/////////////////////////////////////////////////////////////////////////////////////////////
//
// Data Structures for Customers and FIFO queue
//
/////////////////////////////////////////////////////////////////////////////////////////////

// Customers
struct Customer {
    double CreationTime;        // time customer was created
    double ArrTime;            // time customer temply arrived
    double totalWait;
};

// CustomerNode in CustomerList
struct CustomerNode{
    struct Customer *cust;
    struct CustomerNode *next;
};

// A List to record the statistics in customer
struct CustomerList{
    int amount;
    struct CustomerNode *head;
};


// Queue Node in FIFO Queue
typedef struct QNode QNode;

struct QNode{
    void* node;
    QNode* next;
};

// Linked List of customers (FIFO Queue)
typedef struct FIFOQueue FIFOQueue;

struct FIFOQueue {
    struct QNode *first;     // pointer to first customer in queue
    struct QNode *last;      // pointer to last customer in queue
};

/////////////////////////////////////////////////////////////////////////////////////////////
//
// Data Structures for Components
//
/////////////////////////////////////////////////////////////////////////////////////////////

// maximum number of components that can be defined for the simulation
#define MAXCOMPONENTS    100

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
    FIFOQueue* Q;
    double AvgWaitTime;
    double totalWait;
    int inLine;
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
    int Count; // number of customers that exited at this component
    double totalTime;
    double minTime;
    double maxTime;
};


void initialize(int num); // Initialize the global variables
void mkGenerator(int GenID, double IntTime, int DestID); // Make Generator Component
void mkFork(int ForkID, int num, double* probability, int *DestID); // Make Fork Component
void mkStation(int StationID, double avgTime, int DestID); // Make Station Component
int randomFork(struct Fork *p); // Randomly select fork port
void mkExit(int ExitID); //Make Exit Component
int isEmpty(struct Queue_Station* p); // Check if the FIFO Queue is empty
void addToLine(struct Queue_Station *p, struct Customer *c); // Add a customer to the line
void* removeFromLine(struct Queue_Station *p); // Remove the first customer from the line
void Generate (struct EventData *e); // Handle Generate Event
void Arrival(struct EventData *e); // Handle Arrival Event
void Departure(struct EventData *e); // Handle Departure Event
void EventHandler(void *data); // Whole Event Handler
double maxWaitTime(struct CustomerList *p); // Calculate the maximum wait time among customers
double minWaitTime(struct CustomerList *p); // Calculate the minimum wait time among customers
double avgWaitTime(struct CustomerList *p); // Calculate the average wait time among customers
void reportSystem(char* filename); // Report the whole system wait time statistics
void reportStation(int id, char* filename); // Report the total wait time in a station
void reportExit(int id, char* filename); // Report the the maximum, minimum and the average number of total time a customer in the system
void reportStatistics(char* filename); // Report all the statistics in one file
void freeQ(struct FIFOQueue *q);// Free the FIFO Queue
void freeCustList(struct CustomerList *c); // Free Customer List
void freeVariables(void); // Free all the variables that have been allocated memory
#endif /* APPLICATION_H_ */
