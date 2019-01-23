/*
 * application.c
 *
 *  Created on: Oct 12, 2018
 *      Author: mrisleyz
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "engine.h"
#include "random.h"
#include "application.h"


//global CustomerList;
typedef struct CustomerNode CustomerNode;
struct CustomerList *CustList;
int totalExits;
int numComponents;

// global, master list of components
struct {
    int ComponentType;  // GENERATOR, QUEUE_STATION, FORK, EXIT
    void *Comp;         // Pointer to information on component (Generator, Exit struct, etc.)
} Component[MAXCOMPONENTS];

// Initialize the global variables
void initialize(int num){
    
    if((CustList = malloc (sizeof(struct CustomerList)))==NULL){
        fprintf(stderr, "malloc error\n");
        exit(1);
    }
    CustList->amount = 0;
    CustList->head = NULL;
    totalExits = 0;
    numComponents = num;
}

/*
 * Make the components
 */
// Make Generator Component
void mkGenerator(int GenID, double IntTime, int DestID){
    struct Generator *p;
    struct EventData *d;
    
    Component[GenID].ComponentType = GENERATOR;
    
    // Make a new Generator component
    if((p=malloc (sizeof(struct Generator))) == NULL){
        fprintf(stderr, "malloc error\n");
        exit(1);
    }
    p->IntArrTime = IntTime;
    p->DestComp = DestID;
    Component[GenID].Comp = p;
    
    if((d = malloc (sizeof(struct EventData)))== NULL){
        fprintf(stderr, "malloc error\n");
        exit(1);
    }
    
    // Schedule the first event
    d->EventType = GENERATE;
    d->Cust = NULL;
    d->CompID = GenID;
    Schedule(randexp(IntTime), d);   // Random draw
}

// Make Fork Component
void mkFork(int ForkID, int num, double* probability, int *DestID){
    struct Fork *p;
    
    Component[ForkID].ComponentType = FORK;
    
    // Make a new Fork component
    if((p=malloc (sizeof(struct Fork))) == NULL){
        fprintf(stderr, "malloc error\n");
        exit(1);
    }
    p->num = num;
    p->probability = probability;
    p->DestComp = DestID;
    
    Component[ForkID].Comp = p;
}


// Make Station Component

void mkStation(int StationID, double avgTime, int DestID){
    struct Queue_Station *p;
    
    Component[StationID].ComponentType = QUEUE_STATION;
    
    // Make a mew Station component
    if((p=malloc (sizeof(struct Queue_Station))) == NULL){
        fprintf(stderr, "malloc error\n");
        exit(1);
    }
    
    p->totalWait = 0;
    p->AvgWaitTime = avgTime;
    p->DestComp = DestID;
    p->inLine = 0;
    
    // Initialize the FIFO queue in the Station
    if ((p->Q = malloc(sizeof(FIFOQueue))) == NULL){
        fprintf(stderr, "malloc error\n");
        exit(1);
    }
    
    p->Q->first = NULL;
    p->Q->last = NULL;
    
    Component[StationID].Comp = p;
}

// Randomly select fork port
int randomFork(struct Fork *p){
    double *probability = p->probability;
    int *Dest = p->DestComp;
    double prob = urand();
    double cumulativeP = 0;
    for (int i=0; i <p->num;i++){
        cumulativeP += probability[i];
        if(cumulativeP >=prob){
            return Dest[i];
        }
    }
    return Dest[p->num-1];
}

//Make Exit Component
void mkExit(int ExitID){
    struct Exit *p;
    Component[ExitID].ComponentType = EXIT;
    
    // Make a new Exit component
    if ((p=malloc (sizeof(struct Exit))) == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(1);
    }
    
    p->Count = 0;
    p->totalTime = 0;
    p->minTime = -1;
    p->maxTime = 0;
    Component[ExitID].Comp = p;
    
}

// Check if the FIFO Queue is empty
int isEmpty(struct Queue_Station* p) {
    if(p->Q->first == NULL && p->Q->last ==NULL){
        return 1;
    }
    return 0;
}

// Add a customer to the line
void addToLine(struct Queue_Station *p, struct Customer *c){
    // Make a new Queue Node
    QNode *new = malloc (sizeof(QNode));
    if (new == NULL){
        fprintf(stderr, "malloc error\n");
        exit(1);
    }
    if (c == NULL){
        printf("Cannot add a customer to the line.");
    }
    new->node = c;
    new->next = NULL;
    if (isEmpty(p)==1) {
        p->Q->first = new;
        p->Q->last = new;
        return;
    }
    
    (p->Q->last)->next = new;
    p->Q->last = new;
    return;
    
}

// Remove the first customer from the line
void* removeFromLine(struct Queue_Station *p) {
    if (isEmpty(p)==1) {
        printf("Line is empty\n");
        return NULL;
    }
    QNode *temp = p->Q->first;
    p->Q->first = p->Q->first->next;
    
    if (p->Q->first == NULL) {
        p->Q->last = NULL;
    }
    return temp->node;
}


/*
 * Event Handler: Generate, Arrival and Departure
 */
// Handle Generate Event
void Generate (struct EventData *e){
    struct EventData *d;
    struct Customer *NewCust;
    double ts;
    struct Generator *pGen;
    
    // Check if it's Generate event
    if(e->EventType != GENERATE){
        fprintf (stderr, "Unexpected event type\n");
        exit(1);
    }
    
    printf ("Processing Generate event at time %f, Component=%d\n", CurrentTime(), e->CompID);
    
    // Check if it's Generate component
    if (Component[e->CompID].ComponentType != GENERATOR) {
        fprintf(stderr, "bad componenet type\n");
        exit(1);
    }
    
    pGen = (struct Generator *) Component[e->CompID].Comp;
    if((NewCust = malloc (sizeof(struct Customer)))== NULL){
        fprintf(stderr, "malloc error\n");
        exit(1);
    }
    // Make a new customer
    NewCust->CreationTime = CurrentTime();
    NewCust->ArrTime = 0.0;
    NewCust->totalWait = 0.0;
    
    
    // Add the customer to Customer List
    CustomerNode* newNode = malloc(sizeof(CustomerNode));
    if(newNode == NULL){
        fprintf(stderr, "malloc error\n");
        exit(1);
    }
    newNode->cust = NewCust;
    newNode->next = CustList->head;
    CustList->head = newNode;
    CustList->amount++;
    printf("customer has been generated!\n");
    
    // Schedule Arrival event at component connected
    if ((d = malloc(sizeof(struct EventData))) == NULL){
        fprintf (stderr, "Illegal event found\n");
        exit(1);
    }
    d->EventType = ARRIVAL;
    d->Cust = NewCust;
    d->CompID = pGen->DestComp;
    ts = CurrentTime();
    Schedule (ts, d);
    
    // Schedule next Generation event
    if ((d=malloc (sizeof(struct EventData))) == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(1);
    }
    
    d->EventType = GENERATE;
    d->CompID = e->CompID;
    ts = CurrentTime() + randexp(pGen->IntArrTime);       // exponential random number
    Schedule (ts, d);
    
}

// Handle Arrival Event
void Arrival(struct EventData *e){
    struct EventData *d;
    double ts;
    
    struct Queue_Station *pStation;
    struct Exit *pExit;
    struct Fork *pFork;
    
    // Check if it's Arrival event
    if(e->EventType != ARRIVAL){
        fprintf (stderr, "Unexpected event type\n");
        exit(1);
    }
    
    printf ("Processing Arrival event at time %f, Component=%d\n", CurrentTime(), e->CompID);
    
    // Handle the event in Station component
    if(Component[e->CompID].ComponentType == QUEUE_STATION){
        pStation = (struct Queue_Station *) Component[e->CompID].Comp;
        
        if(isEmpty(pStation) == 1){
            
            ts = CurrentTime()+randexp(pStation->AvgWaitTime);
            
            // Make Departure for the event if the queue is empty;
            if ((d = malloc(sizeof(struct EventData))) == NULL){
                fprintf (stderr, "Illegal event found\n");
                exit(1);
            }
            d->EventType = DEPARTURE;
            d->Cust = e->Cust;
            d->CompID = e->CompID;
            Schedule (ts, d);
            printf("customer will depart from %d.\n",d->CompID);
            
        }
        else {
            // Record the Arrival time if the queue is not empty, and put it in the queue
            e->Cust->ArrTime = CurrentTime();
        }
        addToLine(pStation, e->Cust);
        printf("customer add in line.\n");
    }
    // Handle the event in Fork component
    else if (Component[e->CompID].ComponentType == FORK){
        pFork = (struct Fork *) Component[e->CompID].Comp;
        ts = CurrentTime();
        
        // Schedule Arrival event at component connected
        if ((d = malloc(sizeof(struct EventData))) == NULL){
            fprintf (stderr, "Illegal event found\n");
            exit(1);
        }
        d->EventType = ARRIVAL;
        d->Cust = e->Cust;
        
        // Randomly select the port
        int Dest = randomFork(pFork);
        printf("The port number is: %d\n", Dest);
        d->CompID = Dest;
        
        printf("customer will arrive at %d.\n",d->CompID);
        
        Schedule(ts, d);
        
    }
    // Handle the event in Exit component
    else if (Component[e->CompID].ComponentType == EXIT){
        pExit = (struct Exit *) Component[e->CompID].Comp;
        // Record the exit information
        pExit->Count++;
        totalExits++;
        double duration = CurrentTime() - (e->Cust->CreationTime);
        pExit->totalTime = pExit->totalTime + duration;
        
        if (pExit->minTime < 0) {
            pExit->minTime = duration;
        }
        else if (duration < pExit->minTime) {
            pExit->minTime = duration;
        }
        else if (duration > pExit->maxTime) {
            pExit->maxTime = duration;
        }
        printf("one customer has exited.\n");
    }
    else{
        fprintf (stderr, "Bad component type for arrival event\n");
        exit(1);
    }
}

// Handle Departure Event
void Departure(struct EventData *e){
    struct EventData *d;
    struct Queue_Station *pStation;
    double ts;
    
    // Check if it's Departure event
    if(e->EventType != DEPARTURE){
        fprintf (stderr, "Unexpected event type\n");
        exit(1);
    }
    
    printf ("Processing Departure event at time %f, Component=%d\n", CurrentTime(), e->CompID);
    
    // The Departure event only happen in Station component
    if(Component[e->CompID].ComponentType == QUEUE_STATION){
        pStation = (struct Queue_Station *) Component[e->CompID].Comp;
        struct Customer *customer = (struct Customer *)removeFromLine(pStation);
        
        // Make Arrival event for the customer that need to depart
        if ((d = malloc(sizeof(struct EventData))) == NULL){
            fprintf (stderr, "Illegal event found\n");
            exit(1);
        }
        
        d->EventType = ARRIVAL;
        d->Cust = customer;
        d->CompID = pStation->DestComp;
        
        printf("customer will arrive at %d.\n", d->CompID);
        
        ts = CurrentTime();
        Schedule(ts,d);
        
        // If the queue is not empty, make Departure event for the first customer in line
        if(isEmpty(pStation) == 0){
            struct Customer *next = pStation->Q->first->node;
            ts = CurrentTime() + randexp(pStation->AvgWaitTime);
            
            // Calculate the total wait time for each customer and the station
            double waitTime = CurrentTime() - (next->ArrTime);
            next->totalWait = next->totalWait + waitTime;
            pStation->totalWait = pStation->totalWait + waitTime;
            pStation->inLine++;
            
            if ((d = malloc(sizeof(struct EventData))) == NULL){
                fprintf (stderr, "Illegal event found\n");
                exit(1);
            }
            d->EventType = DEPARTURE;
            d->Cust = pStation->Q->first->node;
            d->CompID = e->CompID;
            
            printf("customer will depart from %d.\n", d->CompID);
            
            Schedule(ts,d);
        }
        printf(" customer has departed from station %d\n", e->CompID);
    }
    else {
        printf("Error: customer not depart from a Station\n");
    }
}

// Whole Event Handler
void EventHandler(void *data){
    struct EventData *d;
    
    d = (struct EventData *) data;
    
    if(d->EventType == GENERATE){Generate(d);}
    else if (d->EventType == ARRIVAL) {Arrival(d);}
    else if (d->EventType == DEPARTURE) {Departure(d);}
    else {
        fprintf (stderr, "Illegal event found\n");
        exit(1);
    }
    free(d);
}


/*
 * Statistics calculation
 */
// Calculate the maximum wait time among customers
double maxWaitTime(struct CustomerList *p){
    struct CustomerNode *head = p->head;
    
    if(head == NULL){
        return 0.0;
    }
    double max = head->cust->totalWait;
    struct CustomerNode *curr = p->head->next;
    while( curr != NULL){
        if(curr->cust->totalWait > max){
            max = curr->cust->totalWait;
        }
        curr = curr->next;
    }
    return max;
}

// Calculate the minimum wait time among customers
double minWaitTime(struct CustomerList *p){
    struct CustomerNode *head = p->head;
    
    if(head == NULL){
        return 0.0;
    }
    
    double min = head->cust->totalWait;
    struct CustomerNode *curr = p->head->next;
    while( curr != NULL){
        if(curr->cust->totalWait < min){
            min = curr->cust->totalWait;
        }
        curr = curr->next;
    }
    return min;
    
}

// Calculate the average wait time among customers
double avgWaitTime(struct CustomerList *p){
    struct CustomerNode *cust = p->head;
    
    if(cust == NULL){
        return 0.0;
    }
    
    double sum = 0.0;
    struct CustomerNode *curr = p->head;
    while(curr != NULL){
        sum += curr->cust->totalWait;
        curr = curr->next;
    }
    
    return sum/p->amount;
    
}

// Report the whole system wait time statistics
void reportSystem(char* filename){
    
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        printf("Creating a new file.\n");
        fp = fopen(filename, "w");
        fprintf(fp, "Statistics for the whole system.\n");
        fprintf(fp, "No.of components:\t No.of customers entered:\t No. of customers exited:\t Max wait time:\t Min wait time:\t Avg wait time:\n");
        fprintf(fp, "%d\t%d\t%d\t%.1f\t%.1f\t%.1f", numComponents, CustList->amount, totalExits, maxWaitTime(CustList), minWaitTime(CustList), avgWaitTime(CustList));
        fprintf(fp, "\n");
        fclose(fp);
    }
    
    else{
        fp = fopen(filename, "a");
        fprintf(fp, "%d\t%d\t%d\t%.1f\t%.1f\t%.1f", numComponents, CustList->amount, totalExits, maxWaitTime(CustList), minWaitTime(CustList), avgWaitTime(CustList));
        fprintf(fp, "\n");
        fclose(fp);
    }
    
}

// Report the total wait time in a station
void reportStation(int id, char* filename) {
    FILE* fp = fopen(filename, "r");
    
    if ( Component[id].ComponentType != QUEUE_STATION){
        printf("Not a station component!");
        return;
    }
    
    struct Queue_Station *pStation = Component[id].Comp;
    
    double avgWaitTime;
    if (pStation->inLine == 0){
        avgWaitTime = 0.0;
    }
    else{
        avgWaitTime = (pStation->totalWait)/pStation->inLine;
    }
    
    if (fp == NULL) {
        printf("Creating a new file.\n");
        fp = fopen(filename, "w");
        fprintf(fp, "Statistics for stations.\n");
        fprintf(fp, "Station ID:\t Number of customers in line:\t Average wait time:\n");
        fprintf(fp, "%d\t%d\t%.1f", id, pStation->inLine, avgWaitTime);
        fprintf(fp, "\n");
        fclose(fp);
    }
    else{
        fp = fopen(filename, "a");
        fprintf(fp, "%d\t%d\t%.1f", id, pStation->inLine, avgWaitTime);
        fprintf(fp, "\n");
        fclose(fp);
    }
}

// Report the the maximum, minimum and the average number of total time a customer in the system
void reportExit(int id, char* filename) {
    FILE* fp = fopen(filename, "r");
    
    if ( Component[id].ComponentType != EXIT){
        printf("Not an exit component!");
        return;
    }
    struct Exit *pExit = Component[id].Comp;
    double avgDuration;
    if(pExit->Count == 0){
        avgDuration = 0.0;
    }
    else{
        avgDuration = (pExit->totalTime)/ (pExit->Count);
    }
    
    if (fp == NULL) {
        printf("Creating a new file.\n");
        fp = fopen(filename, "w");
        fprintf(fp, "Statistics for exits.\n");
        fprintf(fp, "Exit ID:\t Number of customers exited:\t Max time in the system:\t Min time in the system:\t Avg time in the system:\n");
        fprintf(fp, "%d\t%d\t%.1f\t%.1f\t%.1f", id, pExit->Count, pExit->maxTime, pExit->minTime, avgDuration);
        fprintf(fp, "\n");
        fclose(fp);
    }
    else{
        fp = fopen(filename, "a");
        fprintf(fp, "%d\t%d\t%.1f\t%.1f\t%.1f", id, pExit->Count, pExit->maxTime, pExit->minTime, avgDuration);
        fprintf(fp, "\n");
        fclose(fp);
    }
}

// Report all the statistics in one file
void reportStatistics (char* filename){
    FILE *fp = fopen(filename, "w");
    if(fp == NULL){
        printf("Creating a new file.\n");
    }
    
    fprintf(fp, "Statistics for the whole system:\n");
    fprintf(fp, "Number of components in system: %d\n", numComponents);
    fprintf(fp, "Number of customers entered: %d\n", CustList->amount);
    fprintf(fp, "Number of customers exited: %d\n", totalExits);
    fprintf(fp, "  Maximum total wait time among customers: %.1f\n", maxWaitTime(CustList));
    fprintf(fp, "  Minimum total wait time among customers: %.1f\n", minWaitTime(CustList));
    fprintf(fp, "  Average total wait time among customers: %.1f\n", avgWaitTime(CustList));
    fprintf(fp, "\n");
    
    for (int i = 0; i< numComponents; i++){
        if (Component[i].ComponentType == QUEUE_STATION){
            struct Queue_Station *pStation = Component[i].Comp;
            double avgWaitTime;
            if (pStation->inLine == 0){
                avgWaitTime = 0.0;
            }
            else{
                avgWaitTime = (pStation->totalWait)/pStation->inLine;
            }
            fprintf(fp, "Statistics for Station %d:\n",i);
            fprintf(fp, "  Number of customers waiting in line: %d\n", pStation->inLine);
            fprintf(fp, "  Average waiting time of the whole line: %.1f\n", avgWaitTime);
            fprintf(fp, "\n");
        }
        if(Component[i].ComponentType == EXIT){
            struct Exit *pExit = Component[i].Comp;
            double avgDuration;
            if (pExit->Count == 0){
                avgDuration = 0.0;
            }
            else{
                avgDuration = (pExit->totalTime)/(pExit->Count);
            }
            fprintf(fp, "Statistics for Exit %d:\n", i);
            fprintf(fp, "  Number of customers exited: %d\n", pExit->Count);
            fprintf(fp, "  Maximum time in the system: %.1f\n", pExit->maxTime);
            fprintf(fp, "  Minimum time in the system: %.1f\n", pExit->minTime);
            fprintf(fp, "  Average time in the system: %.1f\n", avgDuration);
            fprintf(fp, "\n");
        }
    }
    fclose(fp);
    
}

// Free the FIFO Queue
void freeQ(struct FIFOQueue *q){
    QNode* head = q->first;
    QNode* tmp;
    
    while (head != NULL) {
        tmp = head;
        head = head->next;
        if (tmp != NULL) {
            free(tmp);
        }
    }
    if (q != NULL) {
        free(q);
    }
}

// Free Customer List
void freeCustList(struct CustomerList *c){
    struct CustomerNode *head = c->head;
    struct CustomerNode *tmp;
    
    while(head != NULL){
        tmp = head;
        head = head->next;
        if(tmp != NULL){
            free(tmp->cust);
            free(tmp);
        }
    }
    
    if (c != NULL){
        free(c);
    }
    
}

// Free all the variables that have been allocated memory
void freeVariables(){
    for(int i = 0 ;i<numComponents; i++){
        if(Component[i].ComponentType == GENERATOR || Component[i].ComponentType == EXIT
           || Component[i].ComponentType == FORK){
            if (Component[i].Comp != NULL){
                free(Component[i].Comp);
            }
        }
        else if(Component[i].ComponentType == QUEUE_STATION){
            if (Component[i].Comp != NULL){
                struct Queue_Station *q = Component[i].Comp;
                freeQ(q->Q);
                free(q);
            }
        }
    }
    freeCustList(CustList);
}
