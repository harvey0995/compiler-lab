
#include <ctype.h>
#include <string.h>
#include <stdio.h>

char expr[100];
int tempCount = 1;

char operands[50][20];
char operators[50];
int topOperand = -1, topOperator = -1;

void newTemp(char *temp)
{
    sprintf(temp, "t%d", tempCount++);
}

int precedence(char op)
{
    if (op == '*' || op == '/')
        return 2;

    if (op == '+' || op == '-')
        return 1;

    return 0;
}

void generate()
{
    char operand[20];
    char operatorsList[50];
    int topOperand = -1, topOperator = -1;

    for (int i = 0; expr[i] != '\0'; i++)
    {
        if (isspace(expr[i]))
            continue;

        if (isalnum(expr[i]))
        {
            int j = 0;

            while (isalnum(expr[i]))
                operand[j++] = expr[i++];

            operand[j] = '\0';
            i--;

            strcpy(operands[++topOperand], operand);
        }
        else if (expr[i] == '(')
        {
            operatorsList[++topOperator] = expr[i];
        }
        else if (expr[i] == ')')
        {
            while (topOperator >= 0 &&
                   operatorsList[topOperator] != '(')
            {
                char op = operatorsList[topOperator--];
                char right[20], left[20], temp[20];

                strcpy(right, operands[topOperand--]);
                strcpy(left, operands[topOperand--]);

                newTemp(temp);
                printf("%s = %s %c %s\n", temp, left, op, right);

                strcpy(operands[++topOperand], temp);
            }

            if (topOperator >= 0)
                topOperator--;
        }
        else if (strchr("+-*/", expr[i]))
        {
            while (topOperator >= 0 &&
                   precedence(operatorsList[topOperator]) >=
                   precedence(expr[i]) &&
                   operatorsList[topOperator] != '(')
            {
                char op = operatorsList[topOperator--];
                char right[20], left[20], temp[20];

                strcpy(right, operands[topOperand--]);
                strcpy(left, operands[topOperand--]);

                newTemp(temp);
                printf("%s = %s %c %s\n", temp, left, op, right);

                strcpy(operands[++topOperand], temp);
            }

            operatorsList[++topOperator] = expr[i];
        }
    }

    while (topOperator >= 0)
    {
        char op = operatorsList[topOperator--];
        char right[20], left[20], temp[20];

        strcpy(right, operands[topOperand--]);
        strcpy(left, operands[topOperand--]);

        newTemp(temp);
        printf("%s = %s %c %s\n", temp, left, op, right);

        strcpy(operands[++topOperand], temp);
    }
}

int main()
{
    printf("Enter an expression: ");
    scanf("%99s", expr);

    printf("\nIntermediate Code:\n");
    generate();

    return 0;
}





gcc intermediate.c -o intermediate
./intermediate

