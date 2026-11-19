

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to determine operator precedence
int precedence(char op)
{
    if (op == '*' || op == '/')
        return 2;

    if (op == '+' || op == '-')
        return 1;

    return 0;
}

int main()
{
    char expr[100];
    char postfix[100];
    char stack[100];
    char operand[100][20];

    int top = -1;
    int k = 0;
    int n = 0;
    int i;

    printf("Enter expression: ");
    scanf("%99s", expr);

    // Convert infix to postfix
    for (i = 0; expr[i] != '\0'; i++)
    {
        char ch = expr[i];

        if (isalnum((unsigned char)ch))
        {
            postfix[k++] = ch;
        }
        else if (ch == '(')
        {
            stack[++top] = ch;
        }
        else if (ch == ')')
        {
            while (top != -1 && stack[top] != '(')
                postfix[k++] = stack[top--];

            if (top != -1)
                top--;
        }
        else
        {
            while (top != -1 && stack[top] != '(' &&
                   precedence(stack[top]) >= precedence(ch))
            {
                postfix[k++] = stack[top--];
            }

            stack[++top] = ch;
        }
    }

    while (top != -1)
        postfix[k++] = stack[top--];

    postfix[k] = '\0';

    // Generate three-address code
    for (i = 0; postfix[i] != '\0'; i++)
    {
        char ch = postfix[i];

        if (isalnum((unsigned char)ch))
        {
            sprintf(operand[n++], "%c", ch);
        }
        else
        {
            char op2[20], op1[20], result[20];

            strcpy(op2, operand[--n]);
            strcpy(op1, operand[--n]);

            sprintf(result, "t%d", n + 1);

            printf("%s = %s %c %s\n",
                   result, op1, ch, op2);

            strcpy(operand[n++], result);
        }
    }

    printf("Result = %s\n", operand[0]);

    return 0;
}






gcc intermediate.c -o intermediate
./intermediate

