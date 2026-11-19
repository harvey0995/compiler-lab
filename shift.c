
#include <stdio.h>
#include <stdlib.h>

char stack[100], input[100];
int top = -1, pos = 0;

void printRow(const char *action)
{
    printf("%-20s %-20s %-20s\n",
           stack, input + pos, action);
}

void reduce()
{
    /* E -> i */
    if (top >= 0 && stack[top] == 'i')
    {
        stack[top] = 'E';
        stack[top + 1] = '\0';
        printRow("Reduce E->i");
    }

    /* E -> (E) */
    else if (top >= 2 &&
             stack[top - 2] == '(' &&
             stack[top - 1] == 'E' &&
             stack[top] == ')')
    {
        top -= 2;
        stack[top] = 'E';
        stack[top + 1] = '\0';
        printRow("Reduce E->(E)");
    }

    /* E -> E*E */
    else if (top >= 2 &&
             stack[top - 2] == 'E' &&
             stack[top - 1] == '*' &&
             stack[top] == 'E')
    {
        top -= 2;
        stack[top] = 'E';
        stack[top + 1] = '\0';
        printRow("Reduce E->E*E");
    }

    /* E -> E+E */
    else if (top >= 2 &&
             stack[top - 2] == 'E' &&
             stack[top - 1] == '+' &&
             stack[top] == 'E')
    {
        top -= 2;
        stack[top] = 'E';
        stack[top + 1] = '\0';
        printRow("Reduce E->E+E");
    }
}

int main()
{
    printf("Enter input string: ");
    scanf("%s", input);

    stack[0] = '\0';

    printf("\n%-20s %-20s %-20s\n",
           "Stack", "Input", "Action");

    printf("------------------------------------------------------------\n");

    /* SHIFT operation */
    while (input[pos] != '\0')
    {
        stack[++top] = input[pos++];
        stack[top + 1] = '\0';

        printRow("Shift");

        /* REDUCE operation */
        while (1)
        {
            int oldTop = top;

            reduce();

            if (oldTop == top)
                break;
        }
    }

    /* Final reductions */
    while (1)
    {
        int oldTop = top;

        reduce();

        if (oldTop == top)
            break;
    }

    /* Acceptance condition */
    if (top == 0 && stack[0] == 'E')
        printf("\nAccepted\n");
    else
        printf("\nRejected\n");

    return 0;
}




gcc shift.c -o shift
./shift




