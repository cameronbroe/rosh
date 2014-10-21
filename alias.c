#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "alias.h"

int alias_cc = 0;

void define_alias(char* key, char** cmd) {
  alias_t test;
  test = get_alias(key);
  if(test.valid_alias != -1) {
    fprintf(stderr, "Alias already defined with key: %s\n", key);
    return;
  }
  alias_t a;
  a.key = key;
  a.cmd = malloc(sizeof(cmd));
  a.cmd = cmd;
  a.valid_alias = 1;
  aliases[alias_cc] = a;
  alias_cc++;
}

void modify_alias(char* key, char** cmd) {
  alias_t test;
  test = get_alias(key);
  if(test.key = NULL) {
    define_alias(key, cmd);
    return;
  }
  alias_t a;
  a.key = key;
  a.cmd = malloc(sizeof(cmd));
  a.cmd = cmd;
  int alias_index = get_alias_index(key);
  //aliases[alias_index] = realloc(&aliases[alias_index], sizeof(a));
  aliases[alias_index] = a;
}

alias_t get_alias(char* key) {
  int i = 0;
  for(i = 0; i < alias_cc; i++) {
    if(strcmp(key, aliases[i].key) == 0) {
      return aliases[i];
    }
  }
  alias_t empty;
  empty.valid_alias = -1;
  return empty;
}

char* get_alias_key(int index) {
  return aliases[index].key;
}

char** get_alias_cmd(int index) {
  return aliases[index].cmd;
}

int get_alias_index(char* key) {
  int i = 0;
  for(i = 0; i < alias_cc; i++) {
    if(strcmp(key, aliases[i].key) == 0) {
      return i;
    }
  }
  return -1;
}

int get_alias_count() {
  return alias_cc;
}

void list_aliases() {
  int i;
  for(i = 0; i < alias_cc; i++) {
    printf("%s=", aliases[i].key);
    int j;
    for(j = 0; j <= sizeof(aliases[i].cmd)/sizeof(char*); j++) {
      printf("%s ", aliases[i].cmd[j]);
    }
    printf("\n");
  }
}
