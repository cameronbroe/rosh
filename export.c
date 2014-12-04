#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "export.h"

int variable_cc = 0;

void define_variable(char* key, char* val) {
  variable_t test;
  test = get_variable(key);
  if(test.valid_variable != -1) {
    //fprintf(stderr, "Alias already defined with key: %s\n", key);
    modify_variable(key, val);
    return;
  }
  variable_t a;
  a.key = key;
  a.val = malloc(sizeof(val));
  a.val = val;
  a.valid_variable = 1;
  variables[variable_cc] = a;
  variable_cc++;
}

void modify_variable(char* key, char* val) {
  /*variable_t test;
  test = get_variable(key);
  if(test.key = NULL) {
    define_variable(key, val);
    return;
  }*/
  variable_t a;
  a.key = key;
  char* val_ptr = a.val;
  val_ptr = malloc(sizeof(val));
  a.val = val;
  int variable_index = get_variable_index(key);
  //variablees[variable_index] = realloc(&variablees[variable_index], sizeof(a));
  variables[variable_index] = a;
}

variable_t get_variable(char* key) {
  int i = 0;
  for(i = 0; i < variable_cc; i++) {
    if(strcmp(key, variables[i].key) == 0) {
      return variables[i];
    }
  }
  variable_t empty;
  empty.valid_variable = -1;
  return empty;
}

char* get_variable_key(int index) {
  return variables[index].key;
}

char** get_variable_val(int index) {
  return variables[index].val;
}

int get_variable_index(char* key) {
  int i = 0;
  for(i = 0; i < variable_cc; i++) {
    if(strcmp(key, variables[i].key) == 0) {
      return i;
    }
  }
  return -1;
}

int get_variable_count() {
  return variable_cc;
}

void list_variables() {
  int i;
  for(i = 0; i < variable_cc; i++) {
    printf("%s=", variables[i].key);
    int j;
    for(j = 0; j <= sizeof(variables[i].val)/sizeof(char*); j++) {
      printf("%s ", variables[i].val[j]);
    }
    printf("\n");
  }
}
