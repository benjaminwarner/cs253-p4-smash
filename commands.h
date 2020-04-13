#ifndef COMMANDS_H
#define COMMANDS_H

#define COMMAND_DELIM " "

void change_working_dir(char *dir);
void print_working_dir();
void execute_external_command(char *file_name, char *argv[]);

#endif
