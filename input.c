#include "input.h"
//#include "alias.h"
#include <string.h>

char** strsplit(char* string, char* split) {
	char** arr = NULL;
	char *copy = malloc(sizeof(string));
	strcpy(copy, string);
	char *p = strtok(copy, split);
	int count = 0, i;

	while(p) {
		arr = realloc(arr, sizeof (char*) * ++count);
		if(arr == NULL) {
			exit(-1);
		}
		arr[count-1] = p;
		p = strtok(NULL, split);
	}

	// Allocate a space for the end
	arr = realloc(arr, sizeof (char*) * (count+1));
	arr[count] = 0;
	return arr;
}
