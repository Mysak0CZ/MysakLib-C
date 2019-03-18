#include "misc.h"

void wait(ulong_t milliseconds)
{
#ifndef DISABLE_TIMING
#	ifdef _WIN32
	Sleep(milliseconds);
#	else
	sleep(milliseconds / 1000);
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
	long num        = 0;

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
