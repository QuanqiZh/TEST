#ifndef HASHTABLE_H__
#define HASHTABLE_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 20

struct Element {
    void* data;
    int key;
};

//struct Element* HashArray[SIZE];
//struct Element* dummyElement;

int HashFunction(int key);
int HashMapSize(struct Element** HashArray);
void HashMapClear(struct Element** HashArray);
struct Element *search(int key,struct Element** HashArray);
void insert(int key,void* data,struct Element** HashArray);
struct Element* delete(struct Element* ele,struct Element** HashArray);
void display(struct Element** HashArray);

#endif
