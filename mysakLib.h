#pragma once

#include "misc.h"
#include "types.h"

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

/* random uint */
ulong_t MysakLib_randUInt(MysakLib* self, ulong_t min, ulong_t max);

/* random int */
long MysakLib_randInt(MysakLib* self, long min, long max);

/* log error into logfile */
MysakLib* MysakLib_logError(MysakLib* self, char* format, ...);

/* log warning into logfile */
MysakLib* MysakLib_logWarning(MysakLib* self, char* format, ...);

/* log info into logfile */
MysakLib* MysakLib_logInfo(MysakLib* self, char* format, ...);

/* log debug message into logfile */
MysakLib* MysakLib_logDebug(MysakLib* self, char* format, ...);
