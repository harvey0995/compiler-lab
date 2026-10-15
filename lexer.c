
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char str[1000] = "", line[200], token[20];

    char keywords[32][10] = {
        "auto", "break", "case", "char", "const", "continue",
        "default", "do", "double", "else", "enum", "extern",
        "float", "for", "goto", "if", "int", "long",
        "register", "return", "short", "signed", "sizeof",
        "static", "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while"
    };

    FILE *fp;
    int i = 0, j, k, flag;

    fp = fopen("input.c", "r");

    if (fp == NULL)
    {
        printf("Cannot open input.c file.\n");
        return 1;
    }

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        strcat(str, line);
    }

    fclose(fp);

    printf("\nTokens:\n\n");

    while (str[i] != '\0')
    {
        // Ignore spaces, tabs and newlines
        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
        {
            i++;
            continue;
        }

        // Ignore single-line comments
        if (str[i] == '/' && str[i + 1] == '/')
        {
            while (str[i] != '\n' && str[i] != '\0')
                i++;

            continue;
        }

        // Ignore multi-line comments
        if (str[i] == '/' && str[i + 1] == '*')
        {
            i += 2;

            while (str[i] != '\0' &&
                   !(str[i] == '*' && str[i + 1] == '/'))
                i++;

            if (str[i] != '\0')
                i += 2;

            continue;
        }

        // Keyword or Identifier
        if (isalpha((unsigned char)str[i]) || str[i] == '_')
        {
            j = 0;

            while (isalnum((unsigned char)str[i]) ||
                   str[i] == '_')
            {
                if (j < 19)
                    token[j++] = str[i];

                i++;
            }

            token[j] = '\0';
            flag = 0;

            for (k = 0; k < 32; k++)
            {
                if (strcmp(token, keywords[k]) == 0)
                {
                    flag = 1;
                    break;
                }
            }

            if (flag)
                printf("%s : Keyword\n", token);
            else
                printf("%s : Identifier\n", token);
        }

        // Number
        else if (isdigit((unsigned char)str[i]))
        {
            j = 0;

            while (isdigit((unsigned char)str[i]))
            {
                if (j < 19)
                    token[j++] = str[i];

                i++;
            }

            token[j] = '\0';
            printf("%s : Number\n", token);
        }

        // Operator
        else if (strchr("+-*/=%<>", str[i]))
        {
            printf("%c : Operator\n", str[i]);
            i++;
        }

        // Special Symbol
        else if (strchr("(){}[],;", str[i]))
        {
            printf("%c : Special Symbol\n", str[i]);
            i++;
        }

        // Invalid Token
        else
        {
            printf("%c : Invalid Token\n", str[i]);
            i++;
        }
    }

    return 0;
}






create file input.c
lexer.c

gcc lexer.c -o lexer
./lexer

