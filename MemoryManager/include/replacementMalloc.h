#ifndef REPLACEMENT_MALLOC_H
#define REPLACEMENT_MALLOC_H


void *myMalloc(std::size_t size);
void *myCalloc(std::size_t nmemb, std::size_t size);
void myFree(void* ptr);

#endif