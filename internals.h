#pragma once
#include "mysakLib.h"
#include "types.h"

/* Globals */
MysakLib MysakLib_internals_mlib;
bool_t MysakLib_internals_initialized = FALSE;

/* Functions */

/* Assert the library is initialized */
void MysakLib_internals_assertInitialized();

/* log error into logfile */
void MysakLib_internals_logError(char* format, ...);

/* log warning into logfile */
void MysakLib_internals_logWarning(char* format, ...);

/* log info into logfile */
void MysakLib_internals_logInfo(char* format, ...);

/* log debug message into logfile */
void MysakLib_internals_logDebug(char* format, ...);
