#pragma once

#if defined _WIN32 || defined _WIN64
#	define _WIN
#else
#endif

#ifndef DISABLE_INTERACTIVE
#	define INTERACTIVE
#endif


// Type defines

typedef char bool_t;
#define TRUE 1
#define FALSE 0

typedef unsigned int  uint_t;
typedef unsigned long ulong_t;

typedef struct _vector2_t
{
	long x;
	long y;
} vector2_t;
