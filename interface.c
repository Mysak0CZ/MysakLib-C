#include "interface.h"
#include "internals.h"
#include "misc.h"

#include <ctype.h>
#include <string.h>

#ifdef _WIN
#else
#	include <sys/ioctl.h>
#	include <termios.h>
#endif

bool_t m_askYN(char* question)
{
	char answer;
	MysakLib_internals_assertInitialized();
	printf("%s [y/n]: ", question);
	while (TRUE) {
		fflush(stdout);
		answer = tolower(m_getCharB());
#ifndef INTERACTIVE
		if (!isalnum(answer))
			continue;
#endif
		if (answer == 'y') {
			MysakLib_internals_logInfo("askYN \"%s\": true", question);
#ifdef INTERACTIVE
			putchar('\n');
#endif
			return TRUE;
		}
		if (answer == 'n') {
			MysakLib_internals_logInfo("askYN \"%s\": false", question);
#ifdef INTERACTIVE
			putchar('\n');
#endif
			return FALSE;
		}
#ifndef INTERACTIVE
		puts("Invalid option!");
		printf("%s [y/n]: ", question);
#endif
	}
}

long m_readInt(char* query)
{
	long num = 0;
	MysakLib_internals_assertInitialized();
#ifdef INTERACTIVE
	bool_t negative = FALSE;
	char c;
	while (TRUE) {
		if (query != NULL) {
			printf("\r%s> %c%ld  ", query, negative ? '-' : ' ', num);
		} else {
			printf("\r> %c%ld  ", negative ? '-' : ' ', num);
		}
		fflush(stdout);
		c = m_getCharB();
		if (c == '-') {
			negative = !negative;
		} else if (c == '\n' || c == '\r') {
			putchar('\n');
			if (query != NULL) {
				MysakLib_internals_logInfo("readInt \"%s\": %ld", query, negative ? -num : num);
			} else {
				MysakLib_internals_logInfo("readInt NULL: %ld", negative ? -num : num);
			}
			return negative ? -num : num;
		} else if (c == '\b') {
			num /= 10;
		} else if (c >= '0' && c <= '9') {
			num *= 10;
			num += c - '0';
		}
	}
#else
	if (query != NULL) {
		printf("%s> ", query);
	} else {
		printf("> ");
	}
	fflush(stdout);
	while (scanf("%ld", &num) != 1)
		getchar();
	if (query != NULL) {
		MysakLib_internals_logInfo("readInt \"%s\": %ld", query, num);
	} else {
		MysakLib_internals_logInfo("readInt NULL: %ld", num);
	}
	return num;
#endif
}

void m_readStr(char* query, char* target, ulong_t maxLen)
{
	MysakLib_internals_assertInitialized();
#ifdef INTERACTIVE
	ulong_t cLen = 0;
	int c;
	target[0] = '\0';
	while (TRUE) {
		if (query != NULL) {
			printf("\r%s> %s  ", query, target);
		} else {
			printf("\r> %s  ", target);
		}
		fflush(stdout);
		c = m_getCharB();
		if (c == '\n' || c == '\r') {
			putchar('\n');
			if (query != NULL) {
				MysakLib_internals_logInfo("readStr \"%s\": \"%s\"", query, target);
			} else {
				MysakLib_internals_logInfo("readStr NULL: \"%s\"", target);
			}
			return;
		} else if (c == '\b' && cLen > 0) {
			cLen--;
			target[cLen] = '\0';
		} else if (c >= ' ' && c <= '~' && cLen < maxLen) {
			target[cLen] = c;
			cLen++;
			target[cLen] = '\0';
		}
	}
#else
	char buf[21];
	if (query != NULL) {
		printf("\r%s> ", query);
	} else {
		printf("\r> ");
	}
	fflush(stdout);
	snprintf(buf, 20, "%%%lu[^\n]", maxLen);
	fscanf(stdin, buf, target);
	if (query != NULL) {
		MysakLib_internals_logInfo("readStr \"%s\": \"%s\"", query, target);
	} else {
		MysakLib_internals_logInfo("readStr NULL: \"%s\"", target);
	}
#endif
}

long m_ioSelection(char* title, char* options)
{
	long optionsCount = 1;
	long currentOption = 0;
	long i;
	long step;
	int c;
	long YSpace;
	long tmp;
	vector2_t consoleSize, newConsoleSize;
	MysakLib_internals_assertInitialized();
	for (i = 0; options[i] != '\0'; i++) {
		if (options[i] == '\n')
			optionsCount++;
	}

	consoleSize.x = 0;
	consoleSize.y = 0;

	while (TRUE) {
#ifdef INTERACTIVE
		newConsoleSize = m_getConsoleSize();
		if (consoleSize.x != newConsoleSize.x || consoleSize.y != newConsoleSize.y) {
			consoleSize = newConsoleSize;
			m_clearConsole();
			YSpace = (consoleSize.y - m_strCountChar(title, '\n') - optionsCount - 2) / 2;
			m_setConsolePos((consoleSize.x - strlen(title)) / 2, YSpace);
			puts(title);
			c = 1;  // Trigger redraw
		}
		if (c != 0) {
			step = 0;
			currentOption = (currentOption + optionsCount) % optionsCount;
			for (i = 0; options[i] != '\0'; i++) {
				if (i == 0 || options[i - 1] == '\n') {
					tmp = m_strIndexOf(&(options[i]), '\n');
					if (tmp == -1)
						tmp = strlen(&(options[i]));
					m_setConsolePos((consoleSize.x - (tmp + 4)) / 2, YSpace + step + 2);
					putchar(currentOption == step ? '[' : ' ');
					putchar(' ');
				}
				if (options[i] == '\n') {
					putchar(' ');
					putchar(currentOption == step ? ']' : ' ');
					step++;
				} else {
					putchar(options[i]);
				}
			}
			putchar(' ');
			putchar(currentOption == step ? ']' : ' ');
			step++;
			m_setConsolePos(0, consoleSize.y - 1);
			fflush(stdout);
		}
		c = m_getCharNB();
		switch (c) {
			case '8':
			case KEY_UPARROW:
				currentOption--;
				break;
			case '2':
			case KEY_DOWNARROW:
				currentOption++;
				break;
			case '\n':
			case '\r':
			case ' ':
				m_clearConsole();
				MysakLib_internals_logInfo("ioSelections \"%s\": %ld", title, currentOption);
				return currentOption;
		}
#else
		puts(title);
		tmp = 1;
		printf("%ld) ", tmp);
		for (i = 0; options[i] != '\0'; i++) {
			putchar(options[i]);
			if (options[i] == '\n') {
				tmp++;
				if (tmp <= optionsCount)
					printf("%ld) ", tmp);
			}
		}
		printf("\n>");
		fflush(stdout);
		while (scanf("%ld", &tmp) != 1)
			getchar();
		if (tmp >= 1 && tmp <= optionsCount) {
			getchar();
			MysakLib_internals_logInfo("ioSelections \"%s\": %ld", title, tmp - 1);
			return tmp - 1;
		}
#endif
	}
}

int m_getCharB()
{
	int res;
#ifdef _WIN
	res = _getch();
	if (res == 0 || res == 0xe0) {  // Multichar command
		res <<= 8;
		res |= _getch();
	}
#else
	int chr;

	res = getchar();
	if (res == 0x1b) {  // ESC sequence
		res = getchar();
		if (res != '[') {
			MysakLib_internals_logError("Escape sequence 2nd char is not '[': %x", res);
			return 0;
		}
		res = 0x1b5b;
		do {
			chr = getchar();
			res = ((res << 8) & ~0xff) | chr;
		} while (chr < 0x40 || chr > 0x7E);
	}
#endif
	return res;
}

int m_getCharNB()
{
#ifdef _WIN
	if (!kbhit())
		return 0;
#else
	int n;
	if (ioctl(STDIN_FILENO, FIONREAD, &n) != 0 || n <= 0)
		return 0;
#endif
	return m_getCharB();
}

void m_clearConsole()
{
#ifdef _WIN
	system("cls");
#else
	fprintf(stdout, "%c[2J%c[;f", 0x1B, 0x1B);
	fflush(stdout);
#endif
}
