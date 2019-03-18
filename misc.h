#pragma once

#include "types.h"

/* Wait for X milliseconds */
void wait(ulong_t milliseconds);

/* Ask yes no question `{question} [y/n]: ` */
bool_t m_askYN(char* question);

/* Read int from stdin (`INTERACTIVE`?) */
long m_readInt(char* query);
