#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void execute_command(char *str) {
	char *token = strtok(str, " ");
	if (strncmp("exit", token, 4) == 0) {
		exit(0);
	}
}
