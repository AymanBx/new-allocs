#ifndef REPLACEMENT_MALLOC_H
#define REPLACEMENT_MALLOC_H

void *myMalloc(int size);
void *myCalloc(int nmemb, int size);
void myFree(void* ptr);

#endif