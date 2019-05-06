#pragma once

#include "types.h"

/* Wait for X milliseconds */
void wait(ulong_t milliseconds);

/* Get size of the console (real, not buffer) */
vector2_t m_getConsoleSize();

/* set cursor position in console (top-left <=> 0, 0) */
void m_setConsolePos(long x, long y);

/* Count target in string str */
ulong_t m_strCountChar(char* str, char target);

/* Find position of first target in string str (-1 if not found) */
ulong_t m_strIndexOf(char* str, char target);
