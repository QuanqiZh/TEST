//*******************************************************
//
//This file is the head file of hashtable.c
//
//*******************************************************
#ifndef HASHTABLE_H__
#define HASHTABLE_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct Element {
    void* data;
    int key;
};

//struct Element* HashArray[SIZE];
//struct Element* dummyElement;

//Hashfunction that can generate the index in a HashTable.
int HashFunction(int key, int SIZE);

//This function is the free of a Hashtable.
void HashFree(struct Element** HashArray, int SIZE);

//Initialization function that can initialize and generate a Hashtable with assigned size.
struct Element** HashInit(int SIZE);

//This function can return the number of exsiting elements in a HashTable.
int HashMapSize(struct Element** HashArray, int SIZE);

//This function can clear all the elements in the HashTable.
void HashMapClear(struct Element** HashArray, int SIZE);

//This function can search a special element in a HashTable.
struct Element *search(int key,struct Element** HashArray, int SIZE);

//This function can insert an element in a Hashtable.
void insert(int key,void* data,struct Element** HashArray, int SIZE);

//This function can delete an element in a Hashtable.
struct Element* delete(struct Element* ele,struct Element** HashArray, int SIZE);

//This function can print all elements in a HashTable.
void display(struct Element** HashArray, int SIZE);

#endif
