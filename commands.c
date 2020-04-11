#include "commands.h"
#include "history.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
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
		char file_name[strlen(token) + 1];
		strcpy(file_name, token);
		char *args[255];
		args[0] = file_name;
		int count = 1;
		while ((token = strtok(NULL, COMMAND_DELIM)) != NULL) {
			args[count] = token;
			count++;
		}
		args[count] = NULL;
		execute_external_command(file_name, args);
	}
	add_history(buffer, errno);
}

int execute_external_command(char *file_name, char *args[]) {
	int pid = fork();
	if (pid == 0) {
		int status = execvp(file_name, args);
		if (status)
			perror(NULL);
	} else if (pid > 0) {
		wait(NULL);
	} else {
	}
	return 0;
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
