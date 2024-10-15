#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stddef.h> //for size_t

typedef struct
{
    int *startOfArray;  //pointer to the array
    size_t size;        //size of array
    size_t capacity;    //max capacity of array
} ArrayList;

// Creates a new arraylist
ArrayList *arraylist_create(size_t initial_capacity);
// Frees up the allocated area
void arraylist_destroy(ArrayList *list);
// Adds a value to the array                            
int arraylist_add(ArrayList *list, int value);
// Returns 
int arraylist_get(const ArrayList *list, size_t index, int *value);
int arraylist_set(ArrayList *list, size_t index, int value);
size_t arraylist_size(const ArrayList *list);
size_t arraylist_capacity(const ArrayList *list);
int arraylist_remove(ArrayList *list, size_t index)

#endif