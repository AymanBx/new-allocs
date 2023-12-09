/// Your replacement malloc and free functions will be implemented in the source file
/// replacementMalloc.cpp. These functions will be declared in the companion header
/// replacementMalloc.h (the latter is loaded in the main program when in replacement
/// manager mode).

// #include "heapSize.h"
#include <stdio.h>
#include "mallocChoice.h"
#include "replacementManager.h"


// The  malloc()  function  allocates  size bytes and returns a pointer to the allocated memory.
// The memory is not initialized.
void *myMalloc(int size){
    if (size <= 0)
        return nullptr;
    
    #if REPLACEMENT_MANAGER_VERBOSE
        printf("Hello form the other side. Size %d.\n", size);
    #endif
    return nullptr;
}

// allocates memory for an array of nmemb elements of size bytes each and returns a pointer to the allocated memory.
// The memory is set to zero.
void *myCalloc(int nmemb, int size){
    if (size <= 0 || nmemb <= 0)
        return nullptr;
    int fullSize = nmemb * size;
    return nullptr;
}

// The free() function frees the memory space pointed to by ptr, which must have been returned by a previous call to malloc(), calloc(), or re‐
// alloc().  Otherwise, or if free(ptr) has already been called before, undefined behavior occurs.  If ptr is NULL, no operation is performed.
void myFree(void* ptr){
    // if (ptr == nullptr)
}




