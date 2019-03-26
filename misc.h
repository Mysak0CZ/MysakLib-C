#pragma once

#include "types.h"

/* Wait for X milliseconds */
void wait(ulong_t milliseconds);

/* Ask yes no question `{question} [y/n]: ` */
bool_t m_askYN(char* question);

/* Read int from stdin (`INTERACTIVE`?) */
long m_readInt(char* query);

/* Get size of the console (real, not buffer) */
vector2 m_getConsoleSize();

/* set cursor position in console (top-left <=> 0, 0) */
void m_setConsolePos(long x, long y);

/* Count target in string str */
ulong_t m_strCountChar(char* str, char target);

/* Find position of first target in string str (-1 if not found) */
ulong_t m_strIndexOf(char* str, char target);
