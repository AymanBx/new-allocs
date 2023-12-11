/// The source file of the main program will be modified to check if USE REPLACEMENT MANAGER
/// has been defined, to know whether it should be compiled in “replacement malloc” or regular mode.
/// When in USE REPLACEMENT MANAGER mode, your program should make
/// an initialization call to the memory manager to allocate “heap space.” At the end of the
/// program, when in USE REPLACEMENT MANAGER mode, the main function should make
/// a “shut down” call to the memory manager to free the “heap” that it had allocated. At this
/// point, the memory manager should verify that all space allocated has been freed, and print a
/// warning if some space was not freed.

#include <cstdio>
#include <iostream>
#include "mallocChoice.h"

using namespace std;

int main(){

    printf("0\n");
    char* something1 = (char*) malloc(440);
    printf("1\n");
    char* something0 = (char*) malloc(60);
    printf("2\n");
    char* something2 = (char*) malloc(160);
    printf("3\n");
    char* something3 = (char*) malloc(450);
    printf("4\n");

    free(something2);
    printf("5\n");
    #if USE_REPLACEMENT_MANAGER
    extern void *space;
    free(static_cast<void*>(static_cast<char*>(space) + (size_t)685));
    #endif
    free(something0);
    printf("6\n");
    free(something1);
    printf("7\n");
    free(something3);
    printf("8\n");
    
    
    
    #if USE_REPLACEMENT_MANAGER
    // free(static_cast<void*>(static_cast<char*>(space) + (size_t)0));
    free(static_cast<void*>(static_cast<char*>(space) + (size_t)210));
    // free(static_cast<void*>(static_cast<char*>(space) + (size_t)230));
    // free(static_cast<void*>(static_cast<char*>(space) + (size_t)1210));
    free(static_cast<void*>(static_cast<char*>(space) + (size_t)1450));
    // free(static_cast<void*>(static_cast<char*>(space) + (size_t)1600));
    free(static_cast<void*>(static_cast<char*>(space) + (size_t)1860));
    // free(static_cast<void*>(static_cast<char*>(space) + (size_t)1880));
    free(static_cast<void*>(static_cast<char*>(space) + (size_t)2030));
    // free(static_cast<void*>(static_cast<char*>(space) + (size_t)2050));
    free(static_cast<void*>(static_cast<char*>(space) + (size_t)2550));
    // free(static_cast<void*>(static_cast<char*>(space) + (size_t)2570));
    free(static_cast<void*>(static_cast<char*>(space) + (size_t)2820));
    // free(static_cast<void*>(static_cast<char*>(space) + (size_t)2830));
    free(static_cast<void*>(static_cast<char*>(space) + (size_t)3290));
    // free(static_cast<void*>(static_cast<char*>(space) + (size_t)3300));
    #if REPLACEMENT_MANAGER_VERBOSE
    terminateFakeHeap(true);
    #else
    terminateFakeHeap(false);
    #endif
    #endif

    return 0;
}