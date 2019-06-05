#pragma once

#include "types.h"

/* Defines */
#define M_LOGLEVEL_ERROR 0
#define M_LOGLEVEL_WARNING 1
#define M_LOGLEVEL_INFO 2
#define M_LOGLEVEL_DEBUG 3

#ifndef M_LOGFILE_NAME
#	define M_LOGFILE_NAME "mLib.log"
#endif

/* Create new MysakLib */
bool_t MysakLib_initialize();
bool_t MysakLib_initialize_l(int logLevel);
bool_t MysakLib_initialize_li(int logLevel, int internalLoglevel);

/* Delete MysakLib */
void MysakLib_delete();

/* random uint */
ulong_t MysakLib_randUInt(ulong_t min, ulong_t max);

/* random int */
long MysakLib_randInt(long min, long max);

/* Probability in percent */
bool_t m_prob(ulong_t probability);

/* log error into logfile */
void MysakLib_logError(const char* format, ...);

/* log warning into logfile */
void MysakLib_logWarning(const char* format, ...);

/* log info into logfile */
void MysakLib_logInfo(const char* format, ...);

/* log debug message into logfile */
void MysakLib_logDebug(const char* format, ...);
