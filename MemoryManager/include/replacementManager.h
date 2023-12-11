#ifndef REPLACEMENT_MANAGER_H
#define REPLACEMENT_MANAGER_H


#define FIRST_FIT   					100
#define BEST_FIT    					200
#define WORST_FIT    					300
#define ALGORITHM_CHOICE 				BEST_FIT
#define EMPTY_HEAP                      0



#include <cstdio>

void printHeapMap();
void *fakeMalloc(std::size_t size);
void *fakeCalloc(std::size_t nmemb, std::size_t size);
void fakeFree(void* ptr);
bool initHeap();

#endif