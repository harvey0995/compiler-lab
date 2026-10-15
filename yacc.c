

arithmetic.y


%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int yylex();
void yyerror(const char *s);
%}

%token NUMBER
%left '+' '-'
%left '*' '/'

%%

expr:
      expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | '(' expr ')'
    | NUMBER
    ;

%%

int main()
{
    printf("Enter an arithmetic expression:\n");

    if (yyparse() == 0)
        printf("Valid Arithmetic Expression\n");

    return 0;
}

void yyerror(const char *s)
{
    printf("Invalid Arithmetic Expression\n");
}




arithmetic.l


%{
#include "y.tab.h"
%}

%%

[0-9]+      { return NUMBER; }
[ \t\n]+    ;
"+"         { return '+'; }
"-"         { return '-'; }
"*"         { return '*'; }
"/"         { return '/'; }
"("         { return '('; }
")"         { return ')'; }
.           { return yytext[0]; }

%%

int yywrap()
{
    return 1;
}







yacc -d arithmetic.y
lex arithmetic.l
gcc y.tab.c lex.yy.c -o arithmetic -ll
./arithmetic
