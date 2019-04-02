#include "mysakLib.h"

MysakLib* MysakLib_new()
{
	return MysakLib_new_lli(NULL, M_LOGLEVEL_INFO, M_LOGLEVEL_WARNING);
}

MysakLib* MysakLib_new_l(char* logfile)
{
	return MysakLib_new_lli(logfile, M_LOGLEVEL_INFO, M_LOGLEVEL_WARNING);
}

MysakLib* MysakLib_new_ll(char* logfile, int logLevel)
{
	return MysakLib_new_lli(logfile, logLevel, M_LOGLEVEL_WARNING);
}

MysakLib* MysakLib_new_lli(char* logfile, int logLevel, int internalLoglevel)
{
	MysakLib* self = (MysakLib*)malloc(sizeof(MysakLib));
	if (self == NULL)
		return NULL;
	self->randSeed = time(NULL);
	self->loglevel = logLevel;
	self->internalLoglevel = internalLoglevel;
	if (logfile != NULL) {
		self->logfile = fopen(logfile, "w");
		if (self->logfile == NULL && self->internalLoglevel >= M_LOGLEVEL_WARNING) {
			fprintf(stderr, "%10ld I WARN  Failed to open logfile\n", time(NULL));
		}
	} else
		self->logfile = NULL;
	if (self->internalLoglevel >= M_LOGLEVEL_DEBUG) {
		fprintf(self->logfile != NULL ? self->logfile : stderr, "%10ld I DEBUG MysakLib: new - %p\n", time(NULL), self);
		if (self->logfile != NULL)
			fflush(self->logfile);
	}
	return self;
}

void MysakLib_delete(MysakLib* self)
{
	if (self == NULL)
		return;
	if (self->internalLoglevel >= M_LOGLEVEL_DEBUG) {
		fprintf(self->logfile != NULL ? self->logfile : stderr, "%10ld I DEBUG MysakLib: delete - %p\n", time(NULL), self);
		if (self->logfile != NULL)
			fflush(self->logfile);
	}
	if (self->logfile != NULL)
		fclose(self->logfile);
	free(self);
}

ulong_t MysakLib_randUInt(MysakLib* self, ulong_t min, ulong_t max)
{
	if (self == NULL)
		return 0;
	if (self->internalLoglevel >= M_LOGLEVEL_INFO)
		fprintf(self->logfile != NULL ? self->logfile : stderr, "%10ld I INFO  randUInt (%lu -> ", time(NULL), self->randSeed);
	self->randSeed = ((1103515245ULL * self->randSeed) + 12345ULL) % (1ULL << 31);
	if (self->internalLoglevel >= M_LOGLEVEL_INFO) {
		fprintf(self->logfile != NULL ? self->logfile : stderr, "%lu) %lu~%lu = %lu\n", self->randSeed, min, max, (self->randSeed % (max - min)) + min);
		if (self->logfile != NULL)
			fflush(self->logfile);
	}
	return (self->randSeed % (max - min)) + min;
}

long MysakLib_randInt(MysakLib* self, long min, long max)
{
	return MysakLib_randUInt(self, 0, max - min) + min;
}

MysakLib* MysakLib_logError(MysakLib* self, char* format, ...)
{
	char buffer[1025];
	va_list args;
	va_start(args, format);
	vsnprintf(buffer, 1024, format, args);
	if (self != NULL && self->loglevel >= M_LOGLEVEL_ERROR) {
		buffer[1024] = '\0';
		fprintf(self->logfile != NULL ? self->logfile : stderr, "%10ld   ERROR %s\n", time(NULL), buffer);
	}
	va_end(args);
	if (self->logfile != NULL)
		fflush(self->logfile);
	return self;
}

MysakLib* MysakLib_logWarning(MysakLib* self, char* format, ...)
{
	char buffer[1025];
	va_list args;
	va_start(args, format);
	vsnprintf(buffer, 1024, format, args);
	if (self != NULL && self->loglevel >= M_LOGLEVEL_WARNING) {
		buffer[1024] = '\0';
		fprintf(self->logfile != NULL ? self->logfile : stderr, "%10ld   WARN  %s\n", time(NULL), buffer);
	}
	va_end(args);
	if (self->logfile != NULL)
		fflush(self->logfile);
	return self;
}

MysakLib* MysakLib_logInfo(MysakLib* self, char* format, ...)
{
	char buffer[1025];
	va_list args;
	va_start(args, format);
	vsnprintf(buffer, 1024, format, args);
	if (self != NULL && self->loglevel >= M_LOGLEVEL_INFO) {
		buffer[1024] = '\0';
		fprintf(self->logfile != NULL ? self->logfile : stderr, "%10ld   INFO  %s\n", time(NULL), buffer);
	}
	va_end(args);
	if (self->logfile != NULL)
		fflush(self->logfile);
	return self;
}

MysakLib* MysakLib_logDebug(MysakLib* self, char* format, ...)
{
	char buffer[1025];
	va_list args;
	va_start(args, format);
	vsnprintf(buffer, 1024, format, args);
	if (self != NULL && self->loglevel >= M_LOGLEVEL_DEBUG) {
		buffer[1024] = '\0';
		fprintf(self->logfile != NULL ? self->logfile : stderr, "%10ld   DEBUG %s\n", time(NULL), buffer);
	}
	va_end(args);
	if (self->logfile != NULL)
		fflush(self->logfile);
	return self;
}
