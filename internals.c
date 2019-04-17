#include "internals.h"

void MysakLib_internals_assertInitialized()
{
	if (MysakLib_internals_initialized)
		return;
	fprintf(stderr, "CRITICAL: MysakLib used while not initialized!\n");
	exit(1);
}

void MysakLib_internals_logError(char* format, ...)
{
	char buffer[1025];
	va_list args;
	MysakLib_internals_assertInitialized();
	va_start(args, format);
	vsnprintf(buffer, 1024, format, args);
	if (MysakLib_internals_mlib.loglevel >= M_LOGLEVEL_ERROR) {
		buffer[1024] = '\0';
		fprintf(MysakLib_internals_mlib.logfile != NULL ? MysakLib_internals_mlib.logfile : stderr, "%10ld I ERROR %s\n", time(NULL), buffer);
	}
	va_end(args);
	if (MysakLib_internals_mlib.logfile != NULL)
		fflush(MysakLib_internals_mlib.logfile);
}

void MysakLib_internals_logWarning(char* format, ...)
{
	char buffer[1025];
	va_list args;
	MysakLib_internals_assertInitialized();
	va_start(args, format);
	vsnprintf(buffer, 1024, format, args);
	if (MysakLib_internals_mlib.loglevel >= M_LOGLEVEL_WARNING) {
		buffer[1024] = '\0';
		fprintf(MysakLib_internals_mlib.logfile != NULL ? MysakLib_internals_mlib.logfile : stderr, "%10ld I WARN  %s\n", time(NULL), buffer);
	}
	va_end(args);
	if (MysakLib_internals_mlib.logfile != NULL)
		fflush(MysakLib_internals_mlib.logfile);
}

void MysakLib_internals_logInfo(char* format, ...)
{
	char buffer[1025];
	va_list args;
	MysakLib_internals_assertInitialized();
	va_start(args, format);
	vsnprintf(buffer, 1024, format, args);
	if (MysakLib_internals_mlib.loglevel >= M_LOGLEVEL_INFO) {
		buffer[1024] = '\0';
		fprintf(MysakLib_internals_mlib.logfile != NULL ? MysakLib_internals_mlib.logfile : stderr, "%10ld I INFO  %s\n", time(NULL), buffer);
	}
	va_end(args);
	if (MysakLib_internals_mlib.logfile != NULL)
		fflush(MysakLib_internals_mlib.logfile);
}

void MysakLib_internals_logDebug(char* format, ...)
{
	char buffer[1025];
	va_list args;
	MysakLib_internals_assertInitialized();
	va_start(args, format);
	vsnprintf(buffer, 1024, format, args);
	if (MysakLib_internals_mlib.loglevel >= M_LOGLEVEL_DEBUG) {
		buffer[1024] = '\0';
		fprintf(MysakLib_internals_mlib.logfile != NULL ? MysakLib_internals_mlib.logfile : stderr, "%10ld I DEBUG %s\n", time(NULL), buffer);
	}
	va_end(args);
	if (MysakLib_internals_mlib.logfile != NULL)
		fflush(MysakLib_internals_mlib.logfile);
}
