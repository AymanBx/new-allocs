/// The source file replacementManager.cpp will contain all the functions dealing with
/// the management of the list of memory blocks and hole-finding strategy.
/// The companion header file, replacementManager.h is loaded in replacementMalloc.cpp (and
/// in that file only).


#include <list>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "heapSize.h"


// Private structs
struct mem
{
    int index;
    void* ptr;
    bool isAllocated;
    size_t size;
    size_t shift;
};

// Function signitures
bool initHeap();
void printHeapMap();

// Global variables
void* spcae;
std::list<mem> heap;

bool initialized = initHeap();

// yoyoyo
bool initHeap(){
    spcae = (void*) malloc(HEAPSIZE);
    heap.push_back({0,spcae,false,HEAPSIZE,0});
    printf("Initialized fake heap.\n");
    printHeapMap();
    return true;
}


// prints out a “heap
// map” giving the list of allocated and free space on your heap.
// Add a “verbose” state variable to your memory manager so that when in “verbose” mode the
// memory manager prints the heap map following each memory allocating or freeing operation.
void printHeapMap(){
    printf("\nMemory Status:\nSize:%d\n", HEAPSIZE);
    for (const auto &item : heap){
        std::string status;
        if (item.isAllocated)
            status = "Allocated";
        else
            status = "Free";
        printf("Seg %d: Size (%ld) - ", item.index, item.size);
        std::cout << status << std::endl;

    }
    // return;
}