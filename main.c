// System includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

// Local includes
#include "env.h"
#include "input.h"

shell_env env;

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

int main(int argc, int argv) {
	system("clear"); // Clear the terminal
	load_env(&env, NULL);
	char* input = malloc(1024 * sizeof(char)); // Allocate a kilobyte of memory for the input for the shell, this should be sufficient for commands
	do {
		printf("%s%s:   ", env.prompt, env.pwd);
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

		// Try to exec
		shell_exec(arr[0], arr);
		//printf("COMMAND: %s\n", arr[0]);
	} while(strcmp("exit", input) != 0);
	return 0;
}