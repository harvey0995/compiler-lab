
#include <stdio.h>
#include <string.h>

char st[100];
int n = 0;

char *rule[] = {"id", "E+E", "E*E", "(E)"};

int reduce()
{
    for (int r = 0; r < 4; r++)
    {
        int len = strlen(rule[r]);

        if (n >= len &&
            strncmp(st + n - len, rule[r], len) == 0)
        {
            n -= len;
            st[n++] = 'E';
            st[n] = '\0';

            printf("%-20s REDUCE\n", st);
            return 1;
        }
    }

    return 0;
}

int main()
{
    char in[100];

    printf("Enter the input string: ");
    scanf("%99s", in);

    printf("\n%-20s %s\n", "Stack", "Action");

    for (int i = 0; in[i] != '\0'; i++)
    {
        if (in[i] == 'i' && in[i + 1] == 'd')
        {
            st[n++] = 'i';
            st[n++] = 'd';
            i++;
        }
        else
        {
            st[n++] = in[i];
        }

        st[n] = '\0';

        printf("%-20s SHIFT\n", st);

        while (reduce());
    }

    if (n == 1 && st[0] == 'E')
        printf("\nInput string is ACCEPTED.\n");
    else
        printf("\nInput string is REJECTED.\n");

    return 0;
}





gcc shift.c -o shift
./shift




