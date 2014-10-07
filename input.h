#ifndef __INPUT_H_INCLUDE__
#define __INPUT_H_INCLUDE__

#include <string.h>
#include <stdlib.h>

typedef struct {
	char *val;
	size_t length;
} in_str;

char** strsplit(char* str, char* split);

#endif