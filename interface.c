#include "interface.h"
#include "internals.h"
#include "misc.h"

bool_t m_askYN(char* question)
{
	char answer;
	MysakLib_internals_assertInitialized();
	while (TRUE) {
		printf("%s [y/n]: ", question);
		scanf(" %c", &answer);
		answer = tolower(answer);
		if (answer == 'y') {
			MysakLib_internals_logInfo("askYN \"%s\": TRUE", question);
			return TRUE;
		}
		if (answer == 'n') {
			MysakLib_internals_logInfo("askYN \"%s\": FALSE", question);
			return FALSE;
		}
		puts("Invalid option!");
	}
}

long m_readInt(char* query)
{
	bool_t negative = FALSE;
	long num = 0;
	char c;
	MysakLib_internals_assertInitialized();
#ifdef INTERACTIVE
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
			MysakLib_internals_logInfo("readInt \"%s\": %ld", query, negative ? -num : num);
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
	MysakLib_internals_logInfo("readInt \"%s\": %ld", query, negative ? -num : num);
	return num;
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
	vector2 consoleSize, newConsoleSize;
	MysakLib_internals_assertInitialized();
	for (i = 0; options[i] != '\0'; i++) {
		if (options[i] == '\n')
			optionsCount++;
	}

	consoleSize.x = 0;
	consoleSize.y = 0;

	while (TRUE) {
		newConsoleSize = m_getConsoleSize();
		if (consoleSize.x != newConsoleSize.x || consoleSize.y != newConsoleSize.y) {
			consoleSize = newConsoleSize;
#ifdef _WIN32
			system("cls");
#else
			system("clear");
#endif
			YSpace = (consoleSize.y - m_strCountChar(title, '\n') - optionsCount - 2) / 2;
			m_setConsolePos((consoleSize.x - strlen(title)) / 2, YSpace);
			puts(title);
		}
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
		c = getch();
		switch (c) {
			case '8':
				currentOption--;
				break;
			case '2':
				currentOption++;
				break;
			case '\n':
			case '\r':
			case ' ':
#ifdef _WIN32
				system("cls");
#else
				system("clear");
#endif
				MysakLib_internals_logInfo("ioSelections \"%s\": %ld", title, currentOption);
				return currentOption;
			case 0xe0:  // Multichar command
				c = getch();
				if (c == 'H') {  // Up arrow
					currentOption--;
					break;
				} else if (c == 'P') {  // Down arrow
					currentOption++;
					break;
				}
			default:
				fprintf(stderr, "Invalid key %c (%x)", c, c);
				break;
		}
	}
}
