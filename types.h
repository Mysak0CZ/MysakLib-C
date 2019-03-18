#pragma once

#include <stdio.h>
#include <ctype.h>

#ifdef _WIN32
#	include <windows.h>
#	include <time.h>
#   include <conio.h>
#else
#	include <time.h>
#	include <unistd.h>
#	include <stdarg.h>
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
