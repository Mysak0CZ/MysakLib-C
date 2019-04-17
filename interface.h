#pragma once

#include "mysakLib.h"
#include "types.h"

/* Ask yes no question `{question} [y/n]: ` */
bool_t m_askYN(char* question);

/* Read int from stdin (`INTERACTIVE`?) */
long m_readInt(char* query);

/* List selection, separate options by newline */
long m_ioSelection(char* title, char* options);
