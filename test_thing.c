#include "parse.tab.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern double result;

char* parse_math(char* input) {
  char* cp = input;
  int strpos = 0;
  int math_flag = 0;
  int start, end;
  while(*cp != '\0') {
    if(strpos < strlen(input)) {
      if(!(*(cp+1) == '\0') && *cp == '#' && *(cp+1) == '{') {
        start = strpos+2;
        printf("DEBUG: %c\n", input[start]);
        math_flag = 1;
      }
    }
    if(math_flag == 1 && *cp == '}') {
      end = strpos;
      char* buf = malloc(sizeof(char) * 1024);
      math_flag = 0;
      strncpy(buf, input+start, end-start);
      printf("%s\n", buf);

      yy_scan_string(buf);
      yyparse();
      char* rep = input + start;
      char* new = malloc(sizeof(char) * strlen(input) + 1);
      int new_pos = 0;
      strncpy(new, input, start-2);
      printf("Part 1: %s\n", new);
      new_pos = start;
      char* double_str = malloc(sizeof(char) * 1024);
      sprintf(double_str, "%.0f", result);
      //printf("%s\n", double_str);
      new_pos += strlen(double_str);
      strcat(new, double_str);
      printf("Part 2: %s\n", new);
      int end_c = (input+strlen(input)) - (input+end);
      strcat(new, strncpy(new+new_pos, input+end+1, end_c));
      printf("Part 3: %s\n", new);
      input = new;
      cp = new + strpos;
    }
    strpos++;
    cp++;
  }
  return input;
}

int main(int argc, char** argv) {
  char* input = "cat #{10^2}.txt | tail -#{2+2}";
  input = parse_math(input);
  printf("%s\n", input);
  exit(0);
}
