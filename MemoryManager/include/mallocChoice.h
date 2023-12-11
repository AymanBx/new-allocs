//
//  Replacement malloc activation
//  User must make the choice of which malloc they want to use here before compiling
//	

#ifndef MALLOC_CHOICE_H
#define MALLOC_CHOICE_H

#define USE_REPLACEMENT_MANAGER			1
#define REPLACEMENT_MANAGER_VERBOSE		1


#if USE_REPLACEMENT_MANAGER
	#undef malloc
	#define malloc myMalloc
	#undef calloc
	#define calloc myCalloc
	#undef free
	#define free myFree
	#include "replacementMalloc.h"

#else
	#include <stdlib.h>

#endif


#endif //	MALLOC_CHOICE_H
