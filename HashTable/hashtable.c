#include "hashtable.h"
int HashFunction(int key) {
    //Use mode as the Hash map value
    return key % SIZE;
}

int HashMapSize(struct Element** HashArray){
    int count = 0;
    for(int i=0; i<SIZE; i++){
        int hashIndex = HashFunction(i);
        if(HashArray[hashIndex] != NULL){
        int* temp = HashArray[hashIndex]->data;
        if((*temp) != -1)
            count++;
        }
    }
    return count;
}

void HashMapClear(struct Element** HashArray){
    int count = 0;
    for(int i=0; i<SIZE; i++){
        int hashIndex = HashFunction(i);
        if(HashArray[hashIndex] != NULL){
            free(HashArray[hashIndex]);
            HashArray[hashIndex] = NULL;
        }
    }
}

struct Element *search(int key,struct Element** HashArray) {
    //get the hash
    int hashIndex = HashFunction(key);
    
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

void insert(int key,void* data,struct Element** HashArray) {
    printf("!!!");
    struct Element *ele = (struct Element*) malloc(sizeof(struct Element));
    
    ele->data = data;
    ele->key = key;
    
    //get the hash
    int hashIndex = HashFunction(key);
    
    //move in array until an empty or deleted cell
    while(HashArray[hashIndex] != NULL && HashArray[hashIndex]->key != -1) {
        //go to next cell
        hashIndex++;
        //wrap around the table
        hashIndex %= SIZE;
    }
    
    HashArray[hashIndex] = ele;
}

struct Element* delete(struct Element* ele,struct Element** HashArray) {
    int key = ele->key;
    
    //get the hash
    int hashIndex = HashFunction(key);
    
    struct Element* dummyElement;
    
    int dummyData = -1;
    dummyElement = (struct Element*) malloc(sizeof(struct Element));
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

void display(struct Element** HashArray) {
    
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

int main() {
    printf("!!!");
   

    struct Element** HashArray = malloc(SIZE*sizeof(struct Element*));

    for(int i=0; i<SIZE; i++){
        HashArray[i] = (struct Element*) malloc(sizeof(struct Element));
        HashArray[i] = NULL;
    }

    int a = 1;
    int b = 2;
    int c = 3;

    insert(1, &a,HashArray);
    insert(2, &b,HashArray);
    insert(42, &c,HashArray);
//
    display(HashArray);
//    struct Element* Element_test;
//    Element_test = search(37);
//
//    if(Element_test != NULL) {
//        int* ele_data = Element_test->data;
//        printf("Element found: %d\n", *ele_data);
//    } else {
//        printf("Element not found\n");
//    }
//
    printf("Size is %d\n",HashMapSize(HashArray));
    HashMapClear(HashArray);
    printf("Size is %d\n",HashMapSize(HashArray));
//    delete(ele);
//    ele = search(37);
//
//    if(ele != NULL) {
//        printf("Element found: %d\n", *(ele->data));
//    } else {
//        printf("Element not found\n");
//    }
    return 0;
}
