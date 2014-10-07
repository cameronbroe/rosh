#ifndef __ENV_H_INCLUDE__
#define __ENV_H_INCLUDE__

typedef struct {
	char* pwd;
	char* prompt;
	char* path;
} shell_env;

void load_env(shell_env *env, char* filename);

#endif