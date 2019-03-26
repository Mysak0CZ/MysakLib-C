#include "mysakLib.h"

MysakLib* MysakLib_new()
{
	return MysakLib_new_lli(NULL, 2, 0);
}

MysakLib* MysakLib_new_l(char* logfile)
{
	return MysakLib_new_lli(logfile, 2, 0);
}

MysakLib* MysakLib_new_ll(char* logfile, int logLevel)
{
	return MysakLib_new_lli(logfile, logLevel, 0);
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
	} else
		self->logfile = NULL;
	return self;
}

void MysakLib_delete(MysakLib* self)
{
	if (self == NULL)
		return;
	if (self->logfile != NULL)
		fclose((self->logfile));
	free(self);
}

ulong_t MysakLib_randUInt(MysakLib* self, ulong_t min, ulong_t max)
{
	if (self == NULL)
		return 0;
	self->randSeed = ((1103515245ULL * self->randSeed) + 12345ULL) % (1ULL << 31);
	return (self->randSeed % (max - min)) + min;
}

long MysakLib_randInt(MysakLib* self, int min, int max)
{
	return MysakLib_randUInt(self, 0, max - min) + min;
}

MysakLib* MysakLib_logError(MysakLib* self, char* format, ...)
{
	char buffer[1025];
	va_list args;
	va_start(args, format);
	vsnprintf(buffer, 1024, format, args);
	if (self != NULL && self->loglevel >= 0) {
		buffer[1024] = '\0';
		fprintf(self->logfile != NULL ? self->logfile : stderr, "[%10ld] [ERROR] %s\n", time(NULL), buffer);
	}
	va_end(args);
	return self;
}

MysakLib* MysakLib_logWarning(MysakLib* self, char* format, ...)
{
	char buffer[1025];
	va_list args;
	va_start(args, format);
	vsnprintf(buffer, 1024, format, args);
	if (self != NULL && self->loglevel >= 0) {
		buffer[1024] = '\0';
		fprintf(self->logfile != NULL ? self->logfile : stderr, "[%10ld] [WARN]  %s\n", time(NULL), buffer);
	}
	va_end(args);
	return self;
}

MysakLib* MysakLib_logInfo(MysakLib* self, char* format, ...)
{
	char buffer[1025];
	va_list args;
	va_start(args, format);
	vsnprintf(buffer, 1024, format, args);
	if (self != NULL && self->loglevel >= 0) {
		buffer[1024] = '\0';
		fprintf(self->logfile != NULL ? self->logfile : stderr, "[%10ld] [INFO]  %s\n", time(NULL), buffer);
	}
	va_end(args);
	return self;
}

MysakLib* MysakLib_logDebug(MysakLib* self, char* format, ...)
{
	char buffer[1025];
	va_list args;
	va_start(args, format);
	vsnprintf(buffer, 1024, format, args);
	if (self != NULL && self->loglevel >= 0) {
		buffer[1024] = '\0';
		fprintf(self->logfile != NULL ? self->logfile : stderr, "[%10ld] [DEBUG] %s\n", time(NULL), buffer);
	}
	va_end(args);
	return self;
}
