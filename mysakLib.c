#include "mysakLib.h"
#include "internals.h"

#include <stdarg.h>
#include <time.h>

bool_t MysakLib_initialize()
{
	return MysakLib_initialize_li(M_LOGLEVEL_INFO, M_LOGLEVEL_WARNING);
}

bool_t MysakLib_initialize_l(int logLevel)
{
	return MysakLib_initialize_li(logLevel, M_LOGLEVEL_WARNING);
}

bool_t MysakLib_initialize_li(int logLevel, int internalLoglevel)
{
	MysakLib_internals_initialized = TRUE;
	MysakLib_internals_mlib.randSeed = time(NULL);
	MysakLib_internals_mlib.startTime = time(NULL);
	MysakLib_internals_mlib.loglevel = logLevel;
	MysakLib_internals_mlib.internalLoglevel = internalLoglevel;
	MysakLib_internals_mlib.logfile = fopen(M_LOGFILE_NAME, "w");
	if (MysakLib_internals_mlib.logfile == NULL) {
		MysakLib_internals_logWarning("Failed to open logfile");
	}
#if defined INTERACTIVE && !defined _WIN
	tcgetattr(STDIN_FILENO, &(MysakLib_internals_mlib.oldTerminos));
	tcgetattr(STDIN_FILENO, &(MysakLib_internals_mlib.newTerminos));
	MysakLib_internals_mlib.newTerminos.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
	MysakLib_internals_mlib.newTerminos.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	MysakLib_internals_mlib.newTerminos.c_cflag &= ~(CSIZE | PARENB);
	MysakLib_internals_mlib.newTerminos.c_cflag |= CS8;
	makeRawConsole();
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
	makeNormalConsole();
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
	MysakLib_internals_assertInitialized();
	ulong_t oldSeed = MysakLib_internals_mlib.randSeed;
	MysakLib_internals_mlib.randSeed = ((1103515245ULL * MysakLib_internals_mlib.randSeed) + 12345ULL) % (1ULL << 31);
	MysakLib_internals_logInfo("ranUInt %lu -> %lu %ld~%ld = %ld", oldSeed, MysakLib_internals_mlib.randSeed, min, max, (MysakLib_internals_mlib.randSeed % (max - min)) + min);
	return (MysakLib_internals_mlib.randSeed % (max - min)) + min;
}

bool_t m_prob(ulong_t probability)
{
	MysakLib_internals_assertInitialized();
	ulong_t oldSeed = MysakLib_internals_mlib.randSeed;
	MysakLib_internals_mlib.randSeed = ((1103515245ULL * MysakLib_internals_mlib.randSeed) + 12345ULL) % (1ULL << 31);
	bool_t result = (MysakLib_internals_mlib.randSeed % 100) < probability ? TRUE : FALSE;
	MysakLib_internals_logInfo("prob (%lu%%) %lu -> %lu (%lu%%) = %s", probability, oldSeed, MysakLib_internals_mlib.randSeed, (MysakLib_internals_mlib.randSeed % 100), result ? "true" : "false");
	return result;
}

void MysakLib_logError(const char* format, ...)
{
	char    buffer[1025];
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

void MysakLib_logWarning(const char* format, ...)
{
	char    buffer[1025];
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

void MysakLib_logInfo(const char* format, ...)
{
	char    buffer[1025];
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

void MysakLib_logDebug(const char* format, ...)
{
	char    buffer[1025];
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
