#pragma once

#include "mysakLib.h"
#include "types.h"

/* Keys */
#define KEY_HOME (0xe047)
#define KEY_UPARROW (0xe048)
#define KEY_PAGEUP (0xe049)
#define KEY_LEFTARROW (0xe04b)
#define KEY_RIGHTARROW (0xe04d)
#define KEY_END (0xe04f)
#define KEY_DOWNARROW (0xe050)
#define KEY_PAGEDOWN (0xe051)
#define KEY_INSERT (0xe052)
#define KEY_DELETE (0xe053)

/* Ask yes no question `{question} [y/n]: ` */
bool_t m_askYN(char* question);

/* Read int from stdin (`INTERACTIVE`?) */
long m_readInt(char* query);

/* List selection, separate options by newline */
long m_ioSelection(char* title, char* options);

/* Get char blocking, can handle special keys */
int m_getCharB();

/* Get char non-blocking (returns 0 if there is no char, can handle special keys (like arrows)) */
int m_getCharNB();
