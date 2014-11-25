%{
// basic lex parsing

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "string.tab.h"
extern YYSTYPE yylval;

%}

%option noyywrap
delim [ \t]
whitesp {delim}+
alpha [a-zA-Z0-9]*
%%

"\n" { return NEWLINE; }
\" { return DOUBLE_STR; }
' { return SINGLE_STR; }
{whitesp} { return WHITESPACE; }
{alpha} { yylval = (char*) strdup(yytext); return ALPHA; }
