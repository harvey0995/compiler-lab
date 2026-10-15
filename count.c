
%{
#include <stdio.h>

int lines = 0, words = 0, chars = 0;
%}

%%

END\n       { return 0; }

\n         { lines++; chars++; }

[ \t]+     { chars += yyleng; }

[^\t \n]+  {
               words++;
               chars += yyleng;
           }

%%

int yywrap()
{
    return 1;
}

int main()
{
    printf("Enter the text (Type END on a new line to stop):\n");
    yylex();

    printf("\nNumber of Lines    : %d\n", lines);
    printf("Number of Words    : %d\n", words);
    printf("Number of Characters : %d\n", chars);

    return 0;
}




flex count.l
gcc lex.yy.c -o count -lfl
./count

