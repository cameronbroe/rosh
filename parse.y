%{
#define YYSTYPE double
#include <malloc.h>
#include <stdlib.h>
#include <math.h>

double result;
%}

%token DOUBLE_STR SINGLE_STR NEWLINE NUMBER PLUS MINUS DIVIDE MULTIPLY MODULUS LPAREN RPAREN OPEN_MATH END_MATH ALPHA
%token SINE COSINE TANGENT EXP

// Grammar declarations
%%
input:
  | input line
  ;

line: expr { $$ = $1; result = $1; }
  ;

expr: math_expr { $$ = $1; }
  ;

math_expr: math_expr PLUS term { $$ = $1 + $3; }
  | math_expr MINUS term { $$ = $1 - $3; }
  | term
  ;

term: term MULTIPLY factor { $$ = $1 * $3; }
  | term DIVIDE factor { $$ = $1 / $3; }
  | term MODULUS factor { $$ = (int) $1 % (int) $3; }
  | factor
  ;

factor: LPAREN math_expr RPAREN { $$ = $2; }
  | SINE math_expr RPAREN { $$ = sin($2); }
  | COSINE math_expr RPAREN { $$ = cos($2); }
  | TANGENT math_expr RPAREN { $$ = tan($2); }
  | math_expr EXP math_expr { $$ = pow($1, $3); }
  | NUMBER
  ;

%%

#include <stdio.h>
int yyerror(char *s) {
  printf("%s\n", s);
  return(0);
}
/*
int main(void) {
  char input[1024] = "10/20";
  yy_scan_string(input);
  char* res = yyparse();
  exit(0);
}
*/
