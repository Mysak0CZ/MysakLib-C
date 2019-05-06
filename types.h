#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#if defined _WIN32 || defined _WIN64
#	define _WIN
#	error "Todo!"
#else
#endif

/*
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#	include <windows.h>
#	include <time.h>
#	include <conio.h>
#else
#	include <time.h>
#	include <unistd.h>
#	include <stdarg.h>
#	include <string.h>
#	include <sys/ioctl.h>
#endif
*/

#ifndef DISABLE_INTERACTIVE
#	define INTERACTIVE
#endif


// Type defines

typedef char bool_t;
#define TRUE 1
#define FALSE 0

typedef unsigned int uint_t;
typedef unsigned long ulong_t;

typedef struct _vector2_t
{
	long x;
	long y;
} vector2_t;
