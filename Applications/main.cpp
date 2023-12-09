/// The source file of the main program will be modified to check if USE REPLACEMENT MANAGER
/// has been defined, to know whether it should be compiled in “replacement malloc” or regular mode. When in USE REPLACEMENT MANAGER mode, your program should make
/// an initialization call to the memory manager to allocate “heap space.” At the end of the
/// program, when in USE REPLACEMENT MANAGER mode, the main function should make
/// a “shut down” call to the memory manager to free the “heap” that it had allocated. At this
/// point, the memory manager should verify that all space allocated has been freed, and print a
/// warning if some space was not freed.

#include "mallocChoice.h"


int main(){
    void* something = (void*) malloc(1000);
    return 0;
}