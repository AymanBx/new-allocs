#ifndef REPLACEMENT_MANAGER_H
#define REPLACEMENT_MANAGER_H


#define EMPTY_HEAP                      1
#define FIRST_FIT   					100
#define BEST_FIT    					200
#define WORST_FIT    					300
#define ALGORITHM_CHOICE 				WORST_FIT


// Private structs
struct mem
{
    // void* ptr;
    bool isAllocated;
    size_t size;
    size_t shift;
};


bool initHeap(bool verbose);
void printHeapMap();
void *fakeMalloc(std::size_t size);
void *fakeCalloc(std::size_t nmemb, std::size_t size);
void fakeFree(void* ptr);
void term(bool verbose);

#endif