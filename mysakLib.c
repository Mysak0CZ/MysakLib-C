#include "mysakLib.h"
#include "internals.h"

#include <stdarg.h>
#include <time.h>

bool_t MysakLib_initialize()
{
	return MysakLib_initialize_lli(NULL, M_LOGLEVEL_INFO, M_LOGLEVEL_WARNING);
}

bool_t MysakLib_initialize_l(char* logfile)
{
	return MysakLib_initialize_lli(logfile, M_LOGLEVEL_INFO, M_LOGLEVEL_WARNING);
}

bool_t MysakLib_initialize_ll(char* logfile, int logLevel)
{
	return MysakLib_initialize_lli(logfile, logLevel, M_LOGLEVEL_WARNING);
}

bool_t MysakLib_initialize_lli(char* logfile, int logLevel, int internalLoglevel)
{
	MysakLib_internals_initialized = TRUE;
	MysakLib_internals_mlib.randSeed = time(NULL);
	MysakLib_internals_mlib.startTime = time(NULL);
	MysakLib_internals_mlib.loglevel = logLevel;
	MysakLib_internals_mlib.internalLoglevel = internalLoglevel;
	if (logfile != NULL) {
		MysakLib_internals_mlib.logfile = fopen(logfile, "w");
		if (MysakLib_internals_mlib.logfile == NULL) {
			MysakLib_internals_logWarning("Failed to open logfile");
		}
	} else
		MysakLib_internals_mlib.logfile = NULL;
#if defined INTERACTIVE && !defined _WIN
	struct termios newTerminos;
	tcgetattr(STDIN_FILENO, &(MysakLib_internals_mlib.oldTerminos));
	tcgetattr(STDIN_FILENO, &newTerminos);
	cfmakeraw(&newTerminos);
	tcsetattr(STDIN_FILENO, TCSANOW, &newTerminos);
#endif
	MysakLib_internals_logDebug("MysakLib: initialized");
	return TRUE;
}

void MysakLib_delete()
{
	MysakLib_internals_assertInitialized();
	MysakLib_internals_logDebug("MysakLib: delete");
	if (MysakLib_internals_mlib.logfile != NULL)
		fclose(MysakLib_internals_mlib.logfile);
	MysakLib_internals_initialized = FALSE;
	MysakLib_internals_mlib.logfile = NULL;
#if defined INTERACTIVE && !defined _WIN
	tcsetattr(STDIN_FILENO, TCSANOW, &(MysakLib_internals_mlib.oldTerminos));
#endif
}

ulong_t MysakLib_randUInt(ulong_t min, ulong_t max)
{
	MysakLib_internals_assertInitialized();
	ulong_t oldSeed = MysakLib_internals_mlib.randSeed;
	MysakLib_internals_mlib.randSeed = ((1103515245ULL * MysakLib_internals_mlib.randSeed) + 12345ULL) % (1ULL << 31);
	MysakLib_internals_logInfo("randUInt %lu -> %lu %lu~%lu = %lu", oldSeed, MysakLib_internals_mlib.randSeed, min, max, (MysakLib_internals_mlib.randSeed % (max - min)) + min);
	return (MysakLib_internals_mlib.randSeed % (max - min)) + min;
}

long MysakLib_randInt(long min, long max)
{
	return MysakLib_randUInt(0, max - min) + min;
}

void MysakLib_logError(char* format, ...)
{
	char buffer[1025];
	va_list args;
	MysakLib_internals_assertInitialized();
	va_start(args, format);
	vsnprintf(buffer, 1024, format, args);
	if (MysakLib_internals_mlib.loglevel >= M_LOGLEVEL_ERROR) {
		buffer[1024] = '\0';
		fprintf(MysakLib_internals_mlib.logfile != NULL ? MysakLib_internals_mlib.logfile : stderr, "%5ld   ERROR %s\n", time(NULL) - MysakLib_internals_mlib.startTime, buffer);
	}
	va_end(args);
	if (MysakLib_internals_mlib.logfile != NULL)
		fflush(MysakLib_internals_mlib.logfile);
}

void MysakLib_logWarning(char* format, ...)
{
	char buffer[1025];
	va_list args;
	MysakLib_internals_assertInitialized();
	va_start(args, format);
	vsnprintf(buffer, 1024, format, args);
	if (MysakLib_internals_mlib.loglevel >= M_LOGLEVEL_WARNING) {
		buffer[1024] = '\0';
		fprintf(MysakLib_internals_mlib.logfile != NULL ? MysakLib_internals_mlib.logfile : stderr, "%5ld   WARN  %s\n", time(NULL) - MysakLib_internals_mlib.startTime, buffer);
	}
	va_end(args);
	if (MysakLib_internals_mlib.logfile != NULL)
		fflush(MysakLib_internals_mlib.logfile);
}

void MysakLib_logInfo(char* format, ...)
{
	char buffer[1025];
	va_list args;
	MysakLib_internals_assertInitialized();
	va_start(args, format);
	vsnprintf(buffer, 1024, format, args);
	if (MysakLib_internals_mlib.loglevel >= M_LOGLEVEL_INFO) {
		buffer[1024] = '\0';
		fprintf(MysakLib_internals_mlib.logfile != NULL ? MysakLib_internals_mlib.logfile : stderr, "%5ld   INFO  %s\n", time(NULL) - MysakLib_internals_mlib.startTime, buffer);
	}
	va_end(args);
	if (MysakLib_internals_mlib.logfile != NULL)
		fflush(MysakLib_internals_mlib.logfile);
}

void MysakLib_logDebug(char* format, ...)
{
	char buffer[1025];
	va_list args;
	MysakLib_internals_assertInitialized();
	va_start(args, format);
	vsnprintf(buffer, 1024, format, args);
	if (MysakLib_internals_mlib.loglevel >= M_LOGLEVEL_DEBUG) {
		buffer[1024] = '\0';
		fprintf(MysakLib_internals_mlib.logfile != NULL ? MysakLib_internals_mlib.logfile : stderr, "%5ld   DEBUG %s\n", time(NULL) - MysakLib_internals_mlib.startTime, buffer);
	}
	va_end(args);
	if (MysakLib_internals_mlib.logfile != NULL)
		fflush(MysakLib_internals_mlib.logfile);
}
