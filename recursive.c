
#include <stdio.h>
#include <string.h>

char input[100];
int pos = 0;

void E();
void Eprime();
void T();
void Tprime();
void F();

void E()
{
    T();
    Eprime();
}

void Eprime()
{
    if (input[pos] == '+' || input[pos] == '-')
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
    if (input[pos] == '*' || input[pos] == '/')
    {
        pos++;
        F();
        Tprime();
    }
}

void F()
{
    if (input[pos] == '(')
    {
        pos++;
        E();

        if (input[pos] == ')')
            pos++;
        else
            printf("Error: Missing )\n");
    }
    else if (input[pos] == 'i' && input[pos + 1] == 'd')
    {
        pos += 2;
    }
    else
    {
        printf("Error: Invalid input\n");
    }
}

int main()
{
    printf("Enter the input string: ");
    scanf("%99s", input);

    E();

    if (input[pos] == '\0')
        printf("String is accepted.\n");
    else
        printf("String is rejected.\n");

    return 0;
}







gcc parser.c -o parser
./parser


