#include "internals.h"
#include "mysakLib.h"

#include <stdarg.h>
#include <time.h>

void MysakLib_internals_assertInitialized()
{
	if (MysakLib_internals_initialized)
		return;
	fprintf(stderr, "CRITICAL: MysakLib used while not initialized!\n");
	exit(1);
}

void MysakLib_internals_logError(const char* format, ...)
{
	char    buffer[1025];
	va_list args;
	MysakLib_internals_assertInitialized();
	va_start(args, format);
	vsnprintf(buffer, 1024, format, args);
	if (MysakLib_internals_mlib.internalLoglevel >= M_LOGLEVEL_ERROR) {
		buffer[1024] = '\0';
		fprintf(MysakLib_internals_mlib.logfile != NULL ? MysakLib_internals_mlib.logfile : stderr, "%5ld I ERROR %s\n", time(NULL) - MysakLib_internals_mlib.startTime, buffer);
	}
	va_end(args);
	if (MysakLib_internals_mlib.logfile != NULL)
		fflush(MysakLib_internals_mlib.logfile);
}

void MysakLib_internals_logWarning(const char* format, ...)
{
	char    buffer[1025];
	va_list args;
	MysakLib_internals_assertInitialized();
	va_start(args, format);
	vsnprintf(buffer, 1024, format, args);
	if (MysakLib_internals_mlib.internalLoglevel >= M_LOGLEVEL_WARNING) {
		buffer[1024] = '\0';
		fprintf(MysakLib_internals_mlib.logfile != NULL ? MysakLib_internals_mlib.logfile : stderr, "%5ld I WARN  %s\n", time(NULL) - MysakLib_internals_mlib.startTime, buffer);
	}
	va_end(args);
	if (MysakLib_internals_mlib.logfile != NULL)
		fflush(MysakLib_internals_mlib.logfile);
}

void MysakLib_internals_logInfo(const char* format, ...)
{
	char    buffer[1025];
	va_list args;
	MysakLib_internals_assertInitialized();
	va_start(args, format);
	vsnprintf(buffer, 1024, format, args);
	if (MysakLib_internals_mlib.internalLoglevel >= M_LOGLEVEL_INFO) {
		buffer[1024] = '\0';
		fprintf(MysakLib_internals_mlib.logfile != NULL ? MysakLib_internals_mlib.logfile : stderr, "%5ld I INFO  %s\n", time(NULL) - MysakLib_internals_mlib.startTime, buffer);
	}
	va_end(args);
	if (MysakLib_internals_mlib.logfile != NULL)
		fflush(MysakLib_internals_mlib.logfile);
}

void MysakLib_internals_logDebug(const char* format, ...)
{
	char    buffer[1025];
	va_list args;
	MysakLib_internals_assertInitialized();
	va_start(args, format);
	vsnprintf(buffer, 1024, format, args);
	if (MysakLib_internals_mlib.internalLoglevel >= M_LOGLEVEL_DEBUG) {
		buffer[1024] = '\0';
		fprintf(MysakLib_internals_mlib.logfile != NULL ? MysakLib_internals_mlib.logfile : stderr, "%5ld I DEBUG %s\n", time(NULL) - MysakLib_internals_mlib.startTime, buffer);
	}
	va_end(args);
	if (MysakLib_internals_mlib.logfile != NULL)
		fflush(MysakLib_internals_mlib.logfile);
}

void makeRawConsole()
{
#if defined INTERACTIVE && !defined _WIN
	tcsetattr(STDIN_FILENO, TCSANOW, &(MysakLib_internals_mlib.newTerminos));
#endif
}

void makeNormalConsole()
{
#if defined INTERACTIVE && !defined _WIN
	tcsetattr(STDIN_FILENO, TCSANOW, &(MysakLib_internals_mlib.oldTerminos));
#endif
}
