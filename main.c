// System includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

// Flex and Bison include
#include "parse.tab.h"

// Local includes
#include "env.h"
#include "input.h"
#include "alias.h"
#include "export.h"

shell_env env;
extern double result;

void ignore_sigint() {
	signal(SIGINT, SIG_IGN);
}

void ignore_sigtstp() {
	signal(SIGTSTP, SIG_IGN);
}

void shell_exec(char* command, char** argv) {
	pid_t pid;
	int status;

	if((pid = fork()) < 0) {
		printf("Could not fork process\n");
		exit(1);
	} else if(pid == 0) {
		if(execvp(command, argv) < 0) {
			printf("ERROR: command not found\n");
			exit(1);
		}
	} else {
		while(wait(&status) != pid);
	}
}

char* parse_math(char* input) {
	char* start_of = input; // This will stay the same
	char* cp = input;
	int strpos = 0;
	int math_flag = 0;
	int start, end;
	while(*cp != '\0') {
		if(strpos < strlen(input)) {
			if(!(*(cp+1) == '\0') && *cp == '#' && *(cp+1) == '{') {
				start = strpos+2;
				math_flag = 1;
			}
		}
		if(math_flag == 1 && *cp == '}') {
			end = strpos;
			char* buf = malloc(sizeof(char) * 1024);
			math_flag = 0;
			strncpy(buf, input+start, end-start);
			yy_scan_string(buf);
			yyparse();
			char* rep = input + start;
			char* new = malloc(sizeof(char) * strlen(input) + 1);
			int new_pos = 0;
			strncpy(new, input, start-2);
			new_pos = start;
			char* double_str = malloc(sizeof(char) * 1024);
			sprintf(double_str, "%.0f", result);
			//printf("%s\n", double_str);
			new_pos += strlen(double_str);
			strcat(new, double_str);
			int end_c = (input+strlen(input)) - (input+end);
			char* end_str = malloc(sizeof(char) * strlen(input) + 1);
			end_str = strncpy(end_str, input+end+1, end_c);
			strcat(new, end_str);
			input = new;
			cp = new;
			//printf("DEBUG: %s\n", cp);
			strpos = 0;
		}
		strpos++;
		cp++;
	}
	return input;
}

char* parse_vars(char* input) {
	char* start_of = input; // This will stay the same
	char* cp = input;
	int strpos = 0;
	int var_flag = 0;
	int start, end;
	while(*cp != '\0') {
		if(strpos < strlen(input)) {
			if(*cp == '$') {
				start = strpos+1;
				var_flag = 1;
			}
		}
		if(var_flag == 1 && (*cp == ' ' || *(cp+1) == '\0')) {
			end = strpos;
			if(*(cp+1) == '\0') {
				end++; // We have an off by one error if checking for next value is null
			}
			char* buf = malloc(sizeof(char) * 1024);
			strncpy(buf, input+start, end-start);
			char* val_buf = get_variable(buf).val;
			char* rep = input + (start - 1);
			char* new = malloc(sizeof(char) * strlen(input) + 1);
			int new_pos = 0;
			strncpy(new, input, start - 1);
			new_pos = start;
			new_pos += strlen(val_buf);
			strcat(new, val_buf);
			//printf("%s\n", new);
			int end_c = (input+strlen(input)) - (input + end);
			char* end_str = malloc(sizeof(char) * strlen(input) + 1);
			end_str = strncpy(end_str, input+end+1, end_c);
			strcat(new, " ");
			strcat(new, end_str);
			var_flag = 0;
			input = new;
			cp = new;
			strpos = 0;
		}
		strpos++;
		cp++;
	}
	return input;
}

int main(int argc, char** argv) {
	system("clear"); // Clear the terminal
	load_env(&env, NULL);
	char* input = malloc(1024 * sizeof(char)); // Allocate a kilobyte of memory for the input for the shell, this should be sufficient for commands

	// Handle some basic signals
	struct sigaction handler_sigint;
	handler_sigint.sa_handler = ignore_sigint;
	sigaction(SIGINT, &handler_sigint, NULL);

	struct sigaction handler_sigtstp;
	handler_sigtstp.sa_handler = ignore_sigtstp;
	sigaction(SIGTSTP, &handler_sigtstp, NULL);

	do {
		printf("%s%s: ", env.prompt, env.pwd);
		gets(input);
		// Parse math first
		input = parse_math(input);
		input = parse_vars(input);
		char* split = " ";
		char **arr = malloc(1024 * 1024);
		arr = strsplit(input, split);
		// Check for built in commands
		if(strcmp(arr[0], "exit") == 0) {
			exit(0);
		}

		if(strcmp(arr[0], "cd") == 0) {
			chdir(arr[1]);
			env.pwd = getcwd(NULL, 0);
			continue;
		}

		if(strcmp(arr[0], "alias") == 0) {
			if(arr[1] == NULL) {
				list_aliases();
				continue;
			}
			//fprintf(stderr, "ERROR: not implemented yet\n");
			//continue;

			char** a_parse = malloc(sizeof(arr[1]));
			a_parse = strsplit(arr[1], "=");
			char* a_key = a_parse[0];
			arr[1] = a_parse[1]; // Replace the first part of cmd with the part after the = sign
			++arr; // Increment the array to get rid of the "alias"
			//printf("Defining alias with key: %s\n", a_parse[0]);
			//printf("Command: %s\n", arr[0]);
			define_alias(a_key, arr);
			continue;
		}

		if(strcmp(arr[0], "export") == 0) {
			if(arr[1] == NULL) {
				list_variables();
				continue;
			}
			char* v_val = malloc(8192);
			strcpy(v_val, arr[1]);
			v_val = strchr(v_val, '=');
			v_val++;
			char* v_key = strtok(arr[1], "=");
			define_variable(v_key, v_val);
			continue;
		}

		// Try to exec
		//printf("DEBUG: %s\n", arr[0]);
		alias_t a = (alias_t) get_alias(arr[0]);
		//printf("ALIAS VALID?: %d\n", a.valid_alias);
		if(a.valid_alias != -1) {
			char** a_arr = malloc(1024 * 1024);
			a_arr = strsplit(a.cmd[0], " ");
			shell_exec(a_arr[0], a.cmd);
		} else {
			shell_exec(arr[0], arr);
		}
		//printf("COMMAND: %s\n", arr[0]);
	} while(strcmp("exit", input) != 0);
	return 0;
}
