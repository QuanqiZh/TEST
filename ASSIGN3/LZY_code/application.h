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
    double tempArrTime;            // time customer departs system
    double totalWait;
    struct Customer *next;      // pointer to next customer when it is queued in a FIFO
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

// Linked List of customers (FIFO Queue)
struct FIFOQueue {
    struct Customer *first;     // pointer to first customer in queue
    struct Customer *last;      // pointer to last customer in queue
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
	struct FIFOQueue *Q;
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



void initialize(int num);
void mkGenerator(int GenID, double IntTime, int DestID);
void mkFork(int ForkID, int num, double* probability, int *DestID);
void mkStation(int StationID, double avgTime, int DestID);
int randomFork(struct Fork *p);
void mkExit(int ExitID);
int isEmpty(struct Queue_Station* p);
void addToLine(struct Queue_Station *p, struct Customer *c);
void* removeFromLine(struct Queue_Station *p);
void Generate (struct EventData *e);
void Arrival(struct EventData *e);
void Departure(struct EventData *e);
void EventHandler(void *data);
double maxWaitTime(struct CustomerList *p);
double minWaitTime(struct CustomerList *p);
double avgWaitTime(struct CustomerList *p);
void reportStatistics(char* filename);
void reportStation(int id, char* filename);
void recordExit(struct Exit* p, double time, struct Customer* c);
void reportExit(int id, char* filename);


#endif /* APPLICATION_H_ */
