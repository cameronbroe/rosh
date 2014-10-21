#ifndef ALIAS_H_INCLUDE
#define ALIAS_H_INCLUDE

typedef struct {
  char* key;
  char** cmd;
  int valid_alias;
} alias_t;

alias_t aliases[1024];
int alias_cc;

void define_alias(char* key, char** cmd);

void modify_alias(char* key, char** cmd);

alias_t get_alias(char* key);

char* get_alias_key(int index);

char** get_alias_cmd(int index);

int get_alias_index(char* key);

void list_aliases();

#endif
