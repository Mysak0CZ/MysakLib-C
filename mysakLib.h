#pragma once

#include "misc.h"
#include "types.h"

/* Defines */
#define M_LOGLEVEL_ERROR 0
#define M_LOGLEVEL_WARNING 1
#define M_LOGLEVEL_INFO 2
#define M_LOGLEVEL_DEBUG 3

/* Class MysakLib */
typedef struct _MysakLib
{
	ulong_t randSeed;
	FILE* logfile;
	int loglevel;
	int internalLoglevel;
} MysakLib;

/* Create new MysakLib */
bool_t MysakLib_initialize();
bool_t MysakLib_initialize_l(char* logfile);
bool_t MysakLib_initialize_ll(char* logfile, int logLevel);
bool_t MysakLib_initialize_lli(char* logfile, int logLevel, int internalLoglevel);

/* Delete MysakLib */
void MysakLib_delete();

/* random uint */
ulong_t MysakLib_randUInt(ulong_t min, ulong_t max);

/* random int */
long MysakLib_randInt(long min, long max);

/* log error into logfile */
void MysakLib_logError(char* format, ...);

/* log warning into logfile */
void MysakLib_logWarning(char* format, ...);

/* log info into logfile */
void MysakLib_logInfo(char* format, ...);

/* log debug message into logfile */
void MysakLib_logDebug(char* format, ...);
