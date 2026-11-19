
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char input[100];
int pos = 0;

void E();
void Eprime();
void T();
void Tprime();
void F();
void error();
{
    printf("Invalid Expression:\n");
    exit(0);
}

void E()
{
    T();
    Eprime();
}

void Eprime()
{
    if(input[pos]=='+'||input[pos]=='-')
    {
        pos++;
        T();
        Eprime();
    }
}

void T()
{
    F();
    Tprime();
}

void Tprime()
{
    if(input[pos]=='*'||input[pos]=='/')
    {
        pos++;
        F();
        Tprime();
    }
}

void F()
{
    if(input[pos]=='i')
    {
        pos++
    }

    else if (input[pos]=='(')
    {
        pos++;
        E();

        if(input[pos]==')')

        pos++;

        else{
            error();
        }
    }
    else
    {
        error();
    }
}


int main()
{

printf("Enter expression: ");
scanf("%s", input);
E();


if (input[pos] == '\0')
printf("Valid Expression\n");
else
error();
return 0;
}








gcc parser.c -o parser
./parser


