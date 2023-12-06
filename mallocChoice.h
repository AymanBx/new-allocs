//
//  An example of a simple implementation of replacement malloc activation
//
//	Feel free to add more sophisticated preprocessor code

#ifndef MALLOC_CHOICE_H
#define MALLOC_CHOICE_H

#define USE_REPLACEMENT_MANAGER			1
#define REPLACEMENT_MANAGER_VERBOSE		1

#if USE_REPLACEMENT_MANAGER
	#undef malloc
	#define malloc myMalloc
	#undef free
	#define free myFree
	#include "replacementMalloc.h"

#else
	#include <stdlib.h>

#endif


#endif //	MALLOC_CHOICE_H
