#include "commands.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

void execute_command(char *str) {
	char *token = strtok(str, COMMAND_DELIM);
	if (strncmp("exit", token, 4) == 0) {
		exit(0);
	} else if (strncmp("cd", token, 2) == 0) {
		token = strtok(NULL, COMMAND_DELIM);
		change_working_dir(token);
	} else if (strncmp("pwd", token, 2) == 0) {
		print_working_dir();
	}
}

void change_working_dir(char *dir) {
	if (dir == NULL)
		return;
	int status = chdir(dir);
	if (status != 0) {
		perror(NULL);
	} else {
		puts(dir);
	}
}

void print_working_dir() {
	char buffer[4096];
	if (getcwd(buffer, sizeof(buffer)) != NULL) {
		puts(buffer);
	} else {
		perror(NULL);
	}
}
