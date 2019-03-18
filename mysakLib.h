#pragma once

#include "types.h"
#include "misc.h"

/* Class MysakLib */
typedef struct _MysakLib
{
    ulong_t randSeed;
	FILE* logfile;
	int loglevel;
	int internalLoglevel;
} MysakLib;

/* Create new MysakLib */
MysakLib* MysakLib_new();
MysakLib* MysakLib_new_l(char* logfile);
MysakLib* MysakLib_new_ll(char* logfile, int logLevel);
MysakLib* MysakLib_new_lli(char* logfile, int logLevel, int internalLoglevel);

/* Delete MysakLib */
void MysakLib_delete(MysakLib* self);
