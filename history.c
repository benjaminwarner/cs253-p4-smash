#include "history.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static struct history_entry **entries;
static int count = 0;

void init_history() {
	entries = malloc(MAX_HISTORY * sizeof(struct history_entry*));
	for (int i = 0; i < MAX_HISTORY; i++)
		entries[i] = malloc(sizeof(struct history_entry));
}

void clear_history() {
	for (int i = 0; i < MAX_HISTORY; i++) {
		free(entries[i]);
		entries[i] = NULL;
	}
}

void add_history(char *cmd, int exit_status) {
	int position = count % MAX_HISTORY;
	entries[position]->cmd = malloc(strlen(cmd) + 1);
	strncpy(entries[position]->cmd, cmd, strlen(cmd) + 1);
	entries[position]->exit_status = exit_status;
	entries[position]->number = count + 1;
	count++;
}

void print_history() {
	int position;
	int ending;
	if (count < MAX_HISTORY) {
		position = 0;
		ending = count;
	} else {
		position = (count - MAX_HISTORY) % MAX_HISTORY;
		ending = MAX_HISTORY;
	}
	
	for (int i = 0; i < ending; i++) {
		print_history_entry(position);
		position = (position + 1) % MAX_HISTORY;
	}
	errno = 0;
}

void print_history_entry(int p) {
	char buffer[256];
	sprintf(buffer, "%d [%d] %s", entries[p]->number, entries[p]->exit_status, entries[p]->cmd);
	puts(buffer);
}
