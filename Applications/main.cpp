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


    char* something1 = (char*) malloc(440);
    char* something0 = (char*) malloc(60);
    char* something2 = (char*) malloc(160);
    char* something3 = (char*) malloc(450);

    free(something2);
    free(something0);
    free(something1);
    free(something3);
    
    return 0;
}