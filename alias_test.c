#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "alias.h"

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

int main (int argc, char const *argv[]) {
  /* code */
  char** test = (char**) malloc(128 * sizeof(char*));
  test[0] = "ls";
  test[1] = "-lh";
  define_alias("test", test);
  alias_t testAlias = (alias_t) get_alias("test");
  //printf("%s\n", testAlias.cmd[1]);
  list_aliases();
  /*
  char* alias_key = (char*) get_alias_key(0);
  char** alias_cmd = (char**) get_alias_cmd(0);
  printf("%s\n", alias_cmd[1]);
  printf("%s\n", alias_key);
  shell_exec(alias_cmd[0], alias_cmd);
  */
  //shell_exec(testAlias.cmd[0], testAlias.cmd);
  return 0;
}
