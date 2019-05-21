#pragma once

#include "types.h"

/* Keys */
#ifdef _WIN
#	define KEY_HOME (0xe047)
#	define KEY_UPARROW (0xe048)
#	define KEY_PAGEUP (0xe049)
#	define KEY_LEFTARROW (0xe04b)
#	define KEY_RIGHTARROW (0xe04d)
#	define KEY_END (0xe04f)
#	define KEY_DOWNARROW (0xe050)
#	define KEY_PAGEDOWN (0xe051)
#	define KEY_INSERT (0xe052)
#	define KEY_DELETE (0xe053)
#else
#	define KEY_UPARROW (0x1B5B41)
#	define KEY_DOWNARROW (0x1B5B42)
#	define KEY_RIGHTARROW (0x1B5B43)
#	define KEY_LEFTARROW (0x1B5B44)
#	define KEY_END (0x1B5B46)
#	define KEY_HOME (0x1B5B48)
#	define KEY_INSERT (0x1B5B327E)
#	define KEY_DELETE (0x1B5B337E)
#	define KEY_PAGEUP (0x1B5B357E)
#	define KEY_PAGEDOWN (0x1B5B367E)
#endif

/* Ask yes no question `{question} [y/n]: ` */
bool_t m_askYN(const char* question);

/* Ask yes no question `{question} [y/n]: ` (non-interactive) */
bool_t m_askYN_plain(const char* question);

/* Read int from stdin (`INTERACTIVE`?) */
long m_readInt(const char* query);

/* Read int from stdin (non-interactive) */
long m_readInt_plain(const char* query);

/* Read string from stdin up to lengh N */
void m_readStr(const char* query, char* target, ulong_t maxLen);

/* Read string from stdin up to lengh N (non-interactive) */
void m_readStr_plain(const char* query, char* target, ulong_t maxLen);

/* List selection, separate options by newline */
long m_ioSelection(const char* title, const char* options, ...);

/* List selection, separate options by newline (non-interactive) */
long m_ioSelection_plain(const char* title, const char* options, ...);

/* Get char blocking, can handle special keys */
int m_getCharB();

/* Get char non-blocking (returns 0 if there is no char, can handle special keys (like arrows)) */
int m_getCharNB();

/* Clears the console and sets cursor to 0:0 */
void m_clearConsole();
