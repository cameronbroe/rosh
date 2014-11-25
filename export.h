#ifndef EXPORT_H_INCLUDE
#define EXPORT_H_INCLUDE

typedef struct {
  char* key;
  char* val;
  int valid_variable;
} variable_t;

variable_t variables[1024];
int variable_cc;

void define_variable(char* key, char* val);

void modify_variable(char* key, char* val);

variable_t get_variable(char* key);

char* get_variable_key(int index);

char** get_variable_val(int index);

int get_variable_index(char* key);

void list_variables();

#endif
