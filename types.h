#pragma once

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
#	include <sys/ioctl.h>
#	define DISABLE_INTERACTIVE
#endif

#ifndef DISABLE_INTERACTIVE
#	define INTERACTIVE
#endif


// Type defines

typedef char bool_t;
#define TRUE 1
#define FALSE 0

typedef unsigned int uint_t;
typedef unsigned long ulong_t;

typedef struct _vector2
{
	long x;
	long y;
} vector2;
