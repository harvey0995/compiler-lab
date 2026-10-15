
%{
#include <stdio.h>
#include <string.h>
%}

%%

"END"                           { return 0; }

"int"|"float"|"char"|"if"|"else"|"return"
                                { printf("%s : Keyword\n", yytext); }

[0-9]+                          { printf("%s : Number\n", yytext); }

[a-zA-Z_][a-zA-Z0-9_]*          { printf("%s : Identifier\n", yytext); }

"="|"+"|"-"|"*"|"/"             { printf("%s : Operator\n", yytext); }

";"|","|"("|")"|"{"|"}"         { printf("%s : Symbol\n", yytext); }

[ \t\n]+                        ;

.                               { printf("%s : Unknown\n", yytext); }

%%

int main()
{
    printf("Enter code (type END on a new line to finish):\n");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}





flex lex_tool.l
gcc lex.yy.c -o lex_tool -lfl
./lex_tool


int a = 100;
int b = a-50;
END
