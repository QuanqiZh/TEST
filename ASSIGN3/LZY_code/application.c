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
#include "config.h"


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


// global, master list of components
struct {
    int ComponentType;  // GENERATOR, QUEUE_STATION, FORK, EXIT
    void *Comp;         // Pointer to information on component (Generator, Exit struct, etc.)
} Component_read[MAXCOMPONENTS];


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

	d->EventType = GENERATE;
	d->Cust = NULL;
	d->CompID = GenID;
	Schedule(randexp(IntTime), d);   // need to use random draw
}

// Make Fork Component
void mkFork(int ForkID, int num, double* probability, int *DestID){
	struct Fork *p;

	Component[ForkID].ComponentType = FORK;

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

	if((p=malloc (sizeof(struct Queue_Station))) == NULL){
		fprintf(stderr, "malloc error\n");
		exit(1);
	}

	p->totalWait = 0;
	p->AvgWaitTime = avgTime;
	p->DestComp = DestID;
	p->inLine = 0;

	if((p->Q=malloc (sizeof(struct FIFOQueue))) == NULL){
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
	double sum = 0;
	for (int i=0; i <p->num;i++){
		sum += probability[i];
		if(sum >=prob){
			return Dest[i];
		}
	}
	return Dest[p->num-1];
}

//Make Exit Component
void mkExit(int ExitID){
	struct Exit *p;
	Component[ExitID].ComponentType = EXIT;

	// Allocate space for component, fill in parameters
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
	if (c == NULL){
		printf("Cannot add a customer to the line.");
	}
	if (isEmpty(p)==1) {
	    p->Q->first = c;
	    p->Q->last = c;
	    return;
	   // p->Q->first->next = NULL;
	}

	(p->Q->last)->next = c;
	p->Q->last = c;
	return;

}

// Remove the first customer from the line
void* removeFromLine(struct Queue_Station *p) {
	 if (isEmpty(p)==1) {
	    printf("Line is empty\n");
	    return NULL;
	  }
	  struct Customer *temp = p->Q->first;
	  p->Q->first = p->Q->first->next;

	  if (p->Q->first == NULL) {
	    p->Q->last = NULL;
	  }
	  return temp;
}


/*
 * Event Handler: Generate, Arrival and Departure
 */
// Generate Event
void Generate (struct EventData *e){
	struct EventData *d;
	struct Customer *NewCust;
	double ts;
	struct Generator *pGen;

	if(e->EventType != GENERATE){
		fprintf (stderr, "Unexpected event type\n");
		exit(1);
	}

	printf ("Processing Generate event at time %f, Component=%d\n", CurrentTime(), e->CompID);

	if (Component[e->CompID].ComponentType != GENERATOR) {
		fprintf(stderr, "bad componenet type\n");
		exit(1);
	}

	pGen = (struct Generator *) Component[e->CompID].Comp;
	if((NewCust = malloc (sizeof(struct Customer)))== NULL){
		fprintf(stderr, "malloc error\n");
		exit(1);
	}
	NewCust->CreationTime = CurrentTime();
	NewCust->tempArrTime = 0.0;
	NewCust->totalWait = 0.0;
	NewCust->next = NULL;

	CustomerNode* newNode = malloc(sizeof(CustomerNode));
	newNode->cust = NewCust;
	newNode->next = CustList->head;
	CustList->head = newNode;
	CustList->amount++;
	printf("A customer has been generated!");

	// Schedule arrival event at component connected
	if ((d = malloc(sizeof(struct EventData))) == NULL){
		fprintf (stderr, "Illegal event found\n");
		exit(1);
	}
	d->EventType = ARRIVAL;
	d->Cust = NewCust;
	d->CompID = pGen->DestComp;
	ts = CurrentTime();
	Schedule (ts, d);

	// Schedule next generation event
	if ((d=malloc (sizeof(struct EventData))) == NULL) {
		fprintf(stderr, "malloc error\n");
		exit(1);
	}

	d->EventType = GENERATE;
	d->CompID = e->CompID;
	ts = CurrentTime() + randexp(pGen->IntArrTime);       // need to modify to exponential random number
	Schedule (ts, d);

}

// Arrival Event
void Arrival(struct EventData *e){
	struct EventData *d;
	double ts;

	struct Queue_Station *pStation;
	struct Exit *pExit;
	struct Fork *pFork;


	if(e->EventType != ARRIVAL){
		fprintf (stderr, "Unexpected event type\n");
		exit(1);
	}

	printf ("Processing Arrival event at time %f, Component=%d\n", CurrentTime(), e->CompID);

	if(Component[e->CompID].ComponentType == QUEUE_STATION){
		pStation = (struct Queue_Station *) Component[e->CompID].Comp;

		if(isEmpty(pStation) == 1){

			ts = CurrentTime()+randexp(pStation->AvgWaitTime);

			// make departure;
			if ((d = malloc(sizeof(struct EventData))) == NULL){
					fprintf (stderr, "Illegal event found\n");
					exit(1);
				}
				d->EventType = DEPARTURE;
				d->Cust = e->Cust;
				d->CompID = e->CompID;
				Schedule (ts, d);
		}
		else {
			e->Cust->tempArrTime = CurrentTime();
		}
		addToLine(pStation, e->Cust);
	}
	else if (Component[e->CompID].ComponentType == FORK){
		pFork = (struct Fork *) Component[e->CompID].Comp;

		ts = CurrentTime();

		if ((d = malloc(sizeof(struct EventData))) == NULL){
			fprintf (stderr, "Illegal event found\n");
			exit(1);
		}
		d->EventType = ARRIVAL;
		d->Cust = e->Cust;


		int fork = randomFork(pFork);
		d->CompID = fork;

		Schedule(ts, d);

	}
	else if (Component[e->CompID].ComponentType == EXIT){
		pExit = (struct Exit *) Component[e->CompID].Comp;
		recordExit(pExit, CurrentTime(), e->Cust);
		//free(e->Cust);
	}
	else{
		fprintf (stderr, "Bad component type for arrival event\n");
		exit(1);
	}

}

// Departure Event
void Departure(struct EventData *e){
	struct EventData *d;
	double ts;

	struct Queue_Station *pStation;


	if(e->EventType != DEPARTURE){
		fprintf (stderr, "Unexpected event type\n");
		exit(1);
	}

	printf ("Processing Departure event at time %f, Component=%d\n", CurrentTime(), e->CompID);

	if(Component[e->CompID].ComponentType == QUEUE_STATION){
		pStation = (struct Queue_Station *) Component[e->CompID].Comp;

		struct Customer *customer = (struct Customer *)removeFromLine(pStation);

		if ((d = malloc(sizeof(struct EventData))) == NULL){
			fprintf (stderr, "Illegal event found\n");
			exit(1);
		}

		d->EventType = ARRIVAL;
		d->Cust = customer;
		d->CompID = pStation->DestComp;

		Schedule(CurrentTime(),d);

		if(isEmpty(pStation) == 0){
			struct Customer *next = pStation->Q->first;
			ts = CurrentTime() + randexp(pStation->AvgWaitTime);

			double waitTime = CurrentTime() - (next->tempArrTime);
			next->totalWait = next->totalWait + waitTime;
			pStation->totalWait = pStation->totalWait + waitTime;
			pStation->inLine++;

			if ((d = malloc(sizeof(struct EventData))) == NULL){
				fprintf (stderr, "Illegal event found\n");
				exit(1);
				}
			d->EventType = DEPARTURE;
			d->Cust = pStation->Q->first;
			d->CompID = e->CompID;

			Schedule(ts,d);
		}
		printf(" Customer has departed\n" );
	}
	else {
	    printf("Error: customer not departing from a Station\n");
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
void reportStatistics(char* filename){
	FILE *f = fopen(filename, "w");
	if (f == NULL) {
	    printf("Creating a new file\n");
	}
	fprintf(f, "Stats for the whole network\n");
	fprintf(f, "  No. of components in system: %d\n", numComponents);
	fprintf(f, "  No. of customers entered: %d\n", CustList->amount);
	fprintf(f, "  No. of customers exited: %d\n", totalExits);
	fprintf(f, "  Max total wait time among customers: %.1f\n", maxWaitTime(CustList));
	fprintf(f, "  Min total wait time among customers: %.1f\n", minWaitTime(CustList));
	fprintf(f, "  Avg total wait time among customers: %.1f\n", avgWaitTime(CustList));

	fprintf(f, "\n");
	fclose(f);
}

// Report the total wait time in a station
void reportStation(int id, char* filename) {
  FILE* f = fopen(filename, "a");
  if (f == NULL) {
    printf("Creating new file\n");
  }
  if ( Component[id].ComponentType != QUEUE_STATION){
	  printf("Not a station component!");
	  return;
  }

  struct Queue_Station *pStation = Component[id].Comp;

  fprintf(f, "Stats for Station (id = %d)\n", id);
  fprintf(f, "  Total number of instances of waiting in line: %d\n",
         pStation->inLine);

  double avgWaitTime;
  if (pStation->inLine == 0){
	  avgWaitTime = 0.0;
  }
  else{
	  avgWaitTime = (pStation->totalWait)/pStation->inLine;
  }
  fprintf(f, "  Average line wait time: %.1f\n", avgWaitTime);
  fprintf(f, "\n");

  fclose(f);
}

// Record the total duration in exit
void recordExit(struct Exit* p, double time, struct Customer* c){
	p->Count++;
	totalExits++;
	double duration = time - (c->CreationTime);
	p->totalTime = p->totalTime + duration;

	if (p->minTime < 0) {
		p->minTime = duration;
	}
	else if (duration < p->minTime) {
		p->minTime = duration;
	}
	else if (duration > p->maxTime) {
		p->maxTime = duration;
	}

	printf("  One customer has exited\n");

}

// Report the the maximum, minimum and the average number of total time a customer in the system
void reportExit(int id, char* filename) {
  FILE* f = fopen(filename, "a");
  if (f == NULL) {
    printf("Creating a new file\n");
  }

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
  fprintf(f, "Stats of Exit (id = %d)\n", id);
  fprintf(f, "  Number of customers exited: %d\n", pExit->Count);
  fprintf(f, "  Min time in the system: %.1f\n", pExit->minTime);
  fprintf(f, "  Max time in the system: %.1f\n", pExit->maxTime);
  fprintf(f, "  Avg time in the system: %.1f\n", avgDuration);
  fprintf(f, "\n");
  fclose(f);
}
