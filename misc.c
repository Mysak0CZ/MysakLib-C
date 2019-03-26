#include "misc.h"

void wait(ulong_t milliseconds)
{
#ifndef DISABLE_TIMING
#	ifdef _WIN32
	Sleep(milliseconds);
#	else
	struct timespec ts;
	ts.tv_sec = milliseconds / 1000;
	ts.tv_nsec = (milliseconds % 1000) * 1000000;
	nanosleep(&ts, NULL);
#	endif
#endif
}


bool_t m_askYN(char* question)
{
	char answer;
	while (TRUE) {
		printf("%s [y/n]: ", question);
		scanf(" %c", &answer);
		answer = tolower(answer);
		if (answer == 'y')
			return TRUE;
		if (answer == 'n')
			return FALSE;
		puts("Invalid option!");
	}
}

long m_readInt(char* query)
{
	bool_t negative = FALSE;
	long num = 0;

#ifdef INTERACTIVE
	char c;
	while (1) {
		if (query != NULL) {
			printf("\r%s> %c%ld  ", query, negative ? '-' : ' ', num);
		} else {
			printf("\r> %c%ld  ", negative ? '-' : ' ', num);
		}
		c = getch();
		if (c == '-')
			negative = !negative;
		else if (c == '\n' || c == '\r') {
			putchar('\n');
			return negative ? -num : num;
		} else if (c == '\b')
			num /= 10;
		else if (c >= '0' && c <= '9') {
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
	while (scanf("%ld", &num) != 1)
		getchar();
	return num;
#endif
}

vector2 m_getConsoleSize()
{
	vector2 result;
#ifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	result.x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	result.y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#else
	struct winsize win;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
	result.x = win.ws_row;
	result.y = win.ws_col;
#endif
	return result;
}

void m_setConsolePos(long x, long y)
{
#ifdef _WIN32
	COORD coord;  // coordinates
	coord.X = x;
	coord.Y = y;  // X and Y coordinates
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
	fprintf(stdout, "%c[%ld;%ldf", 0x1B, x + 1, y + 1);
	fflush(stdout);
#endif
}

ulong_t m_strCountChar(char* str, char target)
{
	ulong_t result = 0;
	ulong_t i;
	for (i = 0; str[i] != '\0'; i++)
		if (str[i] == target)
			result++;
	return result;
}

ulong_t m_strIndexOf(char* str, char target)
{
	ulong_t i;
	for (i = 0; str[i] != '\0'; i++)
		if (str[i] == target)
			return i;
	return -1;
}
