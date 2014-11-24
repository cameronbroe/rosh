%{
// basic lex parsing

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "parse.tab.h"
extern YYSTYPE yylval;

%}

%option noyywrap
delim [ \t]
whitesp {delim}+
digit [0-9]
alpha .*
number [-]?{digit}*[.]?{digit}+
%%

{number} { sscanf(yytext, "%lf", &yylval); return NUMBER; }
"+" { return PLUS; }
"-" { return MINUS; }
"/" { return DIVIDE; }
"%" { return MODULUS; }
"*" { return MULTIPLY; }
"(" { return LPAREN; }
")" { return RPAREN; }
"\n" { return NEWLINE; }
"#((" { return OPEN_MATH; }
"))" { return END_MATH; }
"sin(" { return SINE; }
"cos(" { return COSINE; }
"tan(" { return TANGENT; }
"^" { return EXP; }
{whitesp} { }
\"{alpha}\" { return DOUBLE_STR; }
'{alpha}' { return SINGLE_STR; }
