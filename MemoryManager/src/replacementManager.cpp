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
#include "replacementManager.h"


// Private structs
struct mem
{
    // void* ptr;
    bool isAllocated;
    size_t size;
    size_t shift;
};

// Function signitures
bool initHeap();

// Global variables
void* space;
std::list<mem> heap;
bool initialized = initHeap();


// yoyoyo
bool initHeap(){
    space = (void*) malloc(HEAPSIZE);
    

    // Hard coded test cases
    #if !EMPTY_HEAP
    // #if ALGORITHM_CHOICE == FIRST_FIT
    heap.push_back({false,200,0});     // 0
    heap.push_back({true,500,200});    // 1
    heap.push_back({false,240,700});   // 2
    heap.push_back({true,150,940});    // 3
    heap.push_back({false,260,1090});  // 4
    heap.push_back({false,500,1350});  // 5
    heap.push_back({false,250,1850});  // 6
    heap.push_back({false,450,2100});  // 7 
    heap.push_back({false,450,2550});   // 8
    // #endif
    #else
    heap.push_back({false,HEAPSIZE,0});
    #endif





    
    printf("Initialized fake heap with size %d.\n", HEAPSIZE);
    printHeapMap();
    
    return true;
}


// prints out a “heap
// map” giving the list of allocated and free space on your heap.
// Add a “verbose” state variable to your memory manager so that when in “verbose” mode the
// memory manager prints the heap map following each memory allocating or freeing operation.
void printHeapMap(){
    printf("\nMemory Status:\nSize:%d\n", HEAPSIZE);
    int index=0;
    for (const auto &item : heap){
        std::string status;
        if (item.isAllocated)
            status = "Allocated";
        else
            status = "Free";
        printf("Seg %d: Size (%ld) - ", index, item.size);
        std::cout << status << std::endl;
        index++;
    }
    printf("\n");
}


// The  malloc()  function  allocates  size bytes and returns a pointer to the allocated memory.
// The memory is not initialized.
void *fakeMalloc(size_t size){
    
    // The pointer to the allocated memory
    void* requested = nullptr;

    // Handle illegal calls
    if (size <= 0)
        return requested;

    // To comapare available sizes
    size_t best=HEAPSIZE+1, worst=0;
    // To hold the indecies of best and worst segments
    int smallest_index=0, largest_index=0;

    // Search for available segments
    int index = 0;
    for (auto it = heap.begin(); it != heap.end(); ++it) {
        mem item = *it;

        // Catch an available memory segment
        if (!item.isAllocated && item.size >= size){
            // In case of a perfect fit
            // Allocate and return the pointer immedietly
            if (item.size == size){
                item.isAllocated = true;
                it = heap.erase(it);
                it = heap.insert(it, item);
                requested = static_cast<void*>(static_cast<char*>(space) + item.shift);
                return requested;
            }

            // First fit case
            // Allocate and return the first available memory segment
            #if ALGORITHM_CHOICE == FIRST_FIT
                mem newItem{
                    true,
                    size,
                    item.shift
                };
                mem newHole{
                    false,
                    item.size - size,
                    item.shift + size
                };

                it = heap.erase(it);
                it = heap.insert(it, newItem);
                it++;
                it = heap.insert(it, newHole);

                requested = static_cast<void*>(static_cast<char*>(space) + item.shift);
                break;
            #endif

            if (item.size < best){
                best = item.size;
                smallest_index = index;
            }

            if (item.size > worst){
                worst = item.size;
                largest_index = index;
            }
            
        }
        index++;
    }

    #if ALGORITHM_CHOICE == WORST_FIT
        // std::list<mem>::iterator it = std::next(heap.begin(), 2);
        // heap.erase(it);
        auto item = heap.begin();
        std::advance(item, largest_index);
        mem seg = *item;

        mem newItem{
            true,
            size,
            seg.shift
        };
        mem newHole{
            false,
            seg.size - size,
            seg.shift + size
        };

        item = heap.erase(item);
        item = heap.insert(item, newItem);
        item++;
        item = heap.insert(item, newHole);

        requested = static_cast<void*>(static_cast<char*>(space) + seg.shift);

    #endif

    #if ALGORITHM_CHOICE == BEST_FIT
        auto item = heap.begin();
        std::advance(item, smallest_index);
        mem seg = *item;

        mem newItem{
            true,
            size,
            seg.shift
        };
        mem newHole{
            false,
            seg.size - size,
            seg.shift + size
        };

        item = heap.erase(item);
        item = heap.insert(item, newItem);
        item++;
        item = heap.insert(item, newHole);

        requested = static_cast<void*>(static_cast<char*>(space) + seg.shift);


    #endif


    

    return requested;
}

// allocates memory for an array of nmemb elements of size bytes each and returns a pointer to the allocated memory.
// The memory is set to zero.
void *fakeCalloc(size_t nmemb, size_t size){
    if (size <= 0 || nmemb <= 0)
        return nullptr;
    int fullSize = nmemb * size;
    return nullptr;
}

// The free() function frees the memory space pointed to by ptr, which must have been returned by a previous call to malloc(), calloc(), or re‐
// alloc().  Otherwise, or if free(ptr) has already been called before, undefined behavior occurs.  If ptr is NULL, no operation is performed.
void fakeFree(void* ptr){
    if (ptr != nullptr){

    }
}



