#include "smash.h"
#include "history.h"
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	init_history();

	char buffer[MAXLINE];
	fputs("$ ", stderr);

	while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
		buffer[strlen(buffer) - 1] = '\0';
		execute_command(buffer);
		fputs("$ ", stderr);
	}
	clear_history();
	return 0;
}
