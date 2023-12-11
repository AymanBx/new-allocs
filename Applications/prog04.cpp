#include <cstdio>
#include <iostream>
#include <vector>
#include "mallocChoice.h"

using namespace std;


int main(int argc, char *argv[]){

    bool verbose = false;


    vector<void *> block;
    for (int i=1; i<argc; i++){
        string arg = argv[i];
        if (arg == "-v")
            verbose = true;
        else if (arg == "m")
            block.push_back((void *) malloc(atoi(argv[++i])));
        else if (arg == "c")
            block.push_back((void *) calloc(atoi(argv[++i]), atoi(argv[++i])));
        else if (arg == "f")
            free(block[atoi(argv[++i])]);
        else{
            printf("Unknown argument %s.\n",argv[i]);
            exit(29);
        }
    }

    #if USE_REPLACEMENT_MANAGER
    if(verbose)
        terminateFakeHeap(true);
    else
        terminateFakeHeap(false);
    #endif

}