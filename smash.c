#include "smash.h"
#include "history.h"
#include <string.h>
#include <stdio.h>

void discard_long_command();

char buffer[MAXLINE];

int main(int argc, char *argv[]) {
	init_history();

	fputs("$ ", stderr);

	while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
		if (strstr(buffer, "\n") != NULL) {
			buffer[strlen(buffer) - 1] = '\0';
			execute_command(buffer);
			fputs("$ ", stderr);
		} else {
			discard_long_command();
		}
	}

	clear_history();
	return 0;
}

void discard_long_command() {
	while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
		if (strstr(buffer, "\n") != NULL)
			break;
	}
}
