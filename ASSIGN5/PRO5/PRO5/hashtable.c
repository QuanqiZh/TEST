//*******************************************************
//
//This file is used to calculate the shortest paths.
//The input should be a map and the srouce city, target city.
//
//*******************************************************
#include "hashtable.h"

//This function is the Hashfunction of the HashMap.It can generate the index in the
//Hashtable.
int HashFunction(int key, int SIZE) {
    //Use mode as the Hash map value
    return key % SIZE;
}

//This function is the Initialization of a Hashtable, which can generate a
//Hashtable with assigned size.
struct Element** HashInit(int SIZE){
    
    struct Element** HashArray = malloc(SIZE*sizeof(struct Element*));
    
    if(HashArray==NULL){
        fprintf(stderr, "malloc error\n"); exit(1);
    }
    
    for(int i=0; i<SIZE; i++){
        HashArray[i] = (struct Element*) malloc(sizeof(struct Element));
        HashArray[i] = NULL;
    }
    
    return HashArray;
}

//This function can return the number of the exsiting elements in a Hashtable.
//The input SIZE is the initialization size.
int HashMapSize(struct Element** HashArray, int SIZE){
    if(HashArray==NULL){
        fprintf(stderr, "read error\n"); exit(1);
    }
    
    int count = 0;
    for(int i=0; i<SIZE; i++){
        int hashIndex = HashFunction(i,SIZE);
        if(HashArray[hashIndex] != NULL){
        int* temp = HashArray[hashIndex]->data;
        if((*temp) != -1)
            count++;
        }
    }
    return count;
}

//This function can clear all the elements in the Hashtable and let them be NULL.
void HashMapClear(struct Element** HashArray, int SIZE){
    if(HashArray==NULL){
        fprintf(stderr, "read error\n"); exit(1);
    }
    int count = 0;
    for(int i=0; i<SIZE; i++){
        int hashIndex = HashFunction(i,SIZE);
        if(HashArray[hashIndex] != NULL){
            free(HashArray[hashIndex]);
            HashArray[hashIndex] = NULL;
        }
    }
}

//This function can search the special element in a Hashtable.If there is no
//Such element. It will return NULL.
struct Element *search(int key,struct Element** HashArray, int SIZE) {
    //get the hash
    int hashIndex = HashFunction(key,SIZE);
    
    //move in array until an empty
    while(HashArray[hashIndex] != NULL) {
        
        if(HashArray[hashIndex]->key == key)
            return HashArray[hashIndex];
        else{
        hashIndex++;
        hashIndex %= SIZE;
        }
    }
    
    return NULL;
}


//This function can insert an element into a HashTable if the HashTable is not
//Filled.
void insert(int key,void* data,struct Element** HashArray, int SIZE) {
    if(HashArray == NULL || data == NULL){
        fprintf(stderr, "read error\n"); exit(1);
    }
    
    struct Element *ele = (struct Element*) malloc(sizeof(struct Element));
    
    if(ele==NULL){
        fprintf(stderr, "read error\n"); exit(1);
    }
    
    ele->data = data;
    ele->key = key;
    
    //get the hash
    int hashIndex = HashFunction(key,SIZE);
    
    //move in array until an empty or deleted cell
    while(HashArray[hashIndex] != NULL && HashArray[hashIndex]->key != -1) {
        //go to next cell
        hashIndex++;
        //wrap around the table
        hashIndex %= SIZE;
    }
    
    HashArray[hashIndex] = ele;
}


//This function can delete a special element in a Hashtable. If there is no such
//element return null.
struct Element* delete(struct Element* ele,struct Element** HashArray, int SIZE) {
    if(HashArray == NULL){
        fprintf(stderr, "read error\n"); exit(1);
    }
    
    if(ele==NULL){
        fprintf(stderr, "read error\n"); exit(1);
    }
    
    int key = ele->key;
    
    //get the hash
    int hashIndex = HashFunction(key,SIZE);
    
    struct Element* dummyElement;
    
    int dummyData = -1;
    dummyElement = (struct Element*) malloc(sizeof(struct Element));
    
    if(dummyElement == NULL){
        fprintf(stderr, "read error\n"); exit(1);
    }
    
    dummyElement->data = &dummyData;
    dummyElement->key = -1;
    //move in array until an empty
    while(HashArray[hashIndex] != NULL) {
        
        if(HashArray[hashIndex]->key == key) {
            struct Element* temp = HashArray[hashIndex];
            
            //assign a dummy ele at deleted position
            HashArray[hashIndex] = dummyElement;
            return temp;
        }
        
        //go to next cell
        ++hashIndex;
        
        //wrap around the table
        hashIndex %= SIZE;
    }
    
    return NULL;
}


//This function can print all the elements in a HashTable.
void display(struct Element** HashArray, int SIZE) {
    if(HashArray == NULL){
        fprintf(stderr, "read error\n"); exit(1);
    }
    
    int i = 0;
    
    for(i = 0; i<SIZE; i++) {

        if(HashArray[i] != NULL){
            int* datavalue;
            datavalue = HashArray[i]->data;
            printf(" (%d,%d)",HashArray[i]->key,*datavalue);
        }
        else
            printf(" ~~ ");
    }
    
    printf("\n");
}


//Below are

//int main() {
//    printf("!!!");
//   
//
//    struct Element** HashArray = malloc(SIZE*sizeof(struct Element*));
//
//    for(int i=0; i<SIZE; i++){
//        HashArray[i] = (struct Element*) malloc(sizeof(struct Element));
//        HashArray[i] = NULL;
//    }
//
//    int a = 1;
//    int b = 2;
//    int c = 3;
//
//    insert(1, &a,HashArray);
//    insert(2, &b,HashArray);
//    insert(42, &c,HashArray);
////
//    display(HashArray);
////    struct Element* Element_test;
////    Element_test = search(37);
////
////    if(Element_test != NULL) {
////        int* ele_data = Element_test->data;
////        printf("Element found: %d\n", *ele_data);
////    } else {
////        printf("Element not found\n");
////    }
////
//    printf("Size is %d\n",HashMapSize(HashArray));
//    HashMapClear(HashArray);
//    printf("Size is %d\n",HashMapSize(HashArray));
////    delete(ele);
////    ele = search(37);
////
////    if(ele != NULL) {
////        printf("Element found: %d\n", *(ele->data));
////    } else {
////        printf("Element not found\n");
////    }
//    return 0;
//}
