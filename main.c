// System includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

// Local includes
#include "env.h"
#include "input.h"
#include "alias.h"

shell_env env;

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
