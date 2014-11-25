%{
#define YYSTYPE char*
#include <malloc.h>
#include <stdlib.h>
%}

%token DOUBLE_STR SINGLE_STR ALPHA NEWLINE WHITESPACE

// Grammar definitions
%%
input:
  | input line
  ;

line: NEWLINE { printf("\n"); }
  | expr NEWLINE { printf("%s\n", $1); }
  ;

expr: DOUBLE_STR string DOUBLE_STR { $$ = $2; printf("Double quote string\n"); }
  | SINGLE_STR string SINGLE_STR { $$ = $2; printf("Single quote string\n"); }
  | not_string { $$ = $1; printf("Not a string\n"); }
  ;

string: ALPHA
  | string WHITESPACE string {
    char buf[80];
    snprintf(buf, sizeof(buf), "%s %s", $1, $3);
    $$ = buf;
  }
  ;

not_string: ALPHA
  | WHITESPACE
  | not_string WHITESPACE not_string
  ;

%%

#include <stdio.h>
int yyerror(char *s) {
  printf("%s\n", s);
  return(0);
}

int main(void) {
  yyparse();
  exit(0);
}
