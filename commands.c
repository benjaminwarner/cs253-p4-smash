#include "commands.h"
#include "history.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

void execute_command(char *str) {
	char buffer[strlen(str) + 1];
	strncpy(buffer, str, sizeof(buffer));
	char *token = strtok(str, COMMAND_DELIM);
	if (token == NULL)
		return;
	if (strncmp("exit", token, 4) == 0) {
		exit(0);
	} else if (strncmp("cd", token, 2) == 0) {
		token = strtok(NULL, COMMAND_DELIM);
		change_working_dir(token);
	} else if (strncmp("pwd", token, 2) == 0) {
		print_working_dir();
	} else if (strncmp("history", token, 7) == 0) {
		print_history();
	} else {
		char buffer[50];
		sprintf(buffer, "[0] %s", token);
		puts(buffer);
		int count = 1;
		while ((token = strtok(NULL, COMMAND_DELIM)) != NULL) {
			sprintf(buffer, "[%d] %s", count, token);
			puts(buffer);
			count++;
		}
		errno = 127;
	}
	add_history(buffer, errno);
}

void change_working_dir(char *dir) {
	if (dir == NULL)
		return;
	int status = chdir(dir);
	if (status != 0) {
		perror(NULL);
		errno = 1;
	} else {
		puts(dir);
		errno = 0;
	}
}

void print_working_dir() {
	char buffer[4096];
	if (getcwd(buffer, sizeof(buffer)) != NULL) {
		puts(buffer);
		errno = 0;
	} else {
		perror(NULL);
	}
}
