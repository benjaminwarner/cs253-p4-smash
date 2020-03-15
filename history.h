#ifndef HISTORY_H
#define HISTORY_H

#define MAX_HISTORY 10

struct history_entry {
	char *cmd;
	int exit_status;
	int number;
};

void init_history(void);
void add_history(char *cmd, int exit_status);
void clear_history(void);
void print_history();
void print_history_entry(int p);

#endif
