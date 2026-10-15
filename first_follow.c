
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 50
#define LEN 100
#define SIZE 128

char lhs[MAX];
char rhs[MAX][LEN];
int n;

int first[26][SIZE];
int follow[26][SIZE];

int add(int set[], char c)
{
    if (!set[(unsigned char)c])
    {
        set[(unsigned char)c] = 1;
        return 1;
    }
    return 0;
}

int isNonTerminal(char c)
{
    return c >= 'A' && c <= 'Z';
}

int main()
{
    int i, j, k, changed;
    char production[LEN];

    printf("Enter number of productions: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX)
    {
        printf("Invalid number of productions.\n");
        return 1;
    }

    printf("Enter productions (use # for epsilon):\n");

    for (i = 0; i < n; i++)
    {
        scanf("%99s", production);

        char *p = strchr(production, '=');

        if (p == NULL || p == production ||
            strlen(p + 1) == 0)
        {
            printf("Invalid production format.\n");
            return 1;
        }

        lhs[i] = production[0];
        strcpy(rhs[i], p + 1);
    }

    /* Calculate FIRST sets */
    do
    {
        changed = 0;

        for (i = 0; i < n; i++)
        {
            int A = lhs[i] - 'A';
            int nullable = 1;

            for (j = 0; rhs[i][j] != '\0'; j++)
            {
                char c = rhs[i][j];

                if (c == '#')
                {
                    changed |= add(first[A], '#');
                    break;
                }

                if (!isNonTerminal(c))
                {
                    changed |= add(first[A], c);
                    nullable = 0;
                    break;
                }

                int B = c - 'A';

                for (k = 0; k < SIZE; k++)
                {
                    if (k != '#' &&
                        first[B][k])
                        changed |= add(first[A], (char)k);
                }

                if (!first[B]['#'])
                {
                    nullable = 0;
                    break;
                }
            }

            if (nullable)
                changed |= add(first[A], '#');
        }
    } while (changed);

    /* Start symbol gets $ in FOLLOW */
    add(follow[lhs[0] - 'A'], '$');

    /* Calculate FOLLOW sets */
    do
    {
        changed = 0;

        for (i = 0; i < n; i++)
        {
            int A = lhs[i] - 'A';
            int len = strlen(rhs[i]);

            for (j = 0; j < len; j++)
            {
                char c = rhs[i][j];

                if (!isNonTerminal(c))
                    continue;

                int B = c - 'A';
                int nullable = 1;

                for (k = j + 1; k < len; k++)
                {
                    char next = rhs[i][k];

                    if (next == '#')
                    {
                        break;
                    }

                    if (!isNonTerminal(next))
                    {
                        changed |= add(follow[B], next);
                        nullable = 0;
                        break;
                    }

                    int C = next - 'A';

                    int t;
                    for (t = 0; t < SIZE; t++)
                    {
                        if (t != '#' && first[C][t])
                            changed |= add(follow[B], (char)t);
                    }

                    if (!first[C]['#'])
                    {
                        nullable = 0;
                        break;
                    }
                }

                if (nullable)
                {
                    int t;

                    for (t = 0; t < SIZE; t++)
                    {
                        if (follow[A][t])
                            changed |= add(follow[B], (char)t);
                    }
                }
            }
        }
    } while (changed);

    /* Print FIRST sets */
    printf("\nFIRST sets:\n");

    for (i = 0; i < n; i++)
    {
        int A = lhs[i] - 'A';
        int seen = 0;

        for (j = 0; j < i; j++)
            if (lhs[j] == lhs[i])
                seen = 1;

        if (seen)
            continue;

        printf("FIRST(%c) = { ", lhs[i]);

        for (j = 0; j < SIZE; j++)
            if (first[A][j])
                printf("%c ", j);

        printf("}\n");
    }

    /* Print FOLLOW sets */
    printf("\nFOLLOW sets:\n");

    for (i = 0; i < n; i++)
    {
        int A = lhs[i] - 'A';
        int seen = 0;

        for (j = 0; j < i; j++)
            if (lhs[j] == lhs[i])
                seen = 1;

        if (seen)
            continue;

        printf("FOLLOW(%c) = { ", lhs[i]);

        for (j = 0; j < SIZE; j++)
            if (follow[A][j])
                printf("%c ", j);

        printf("}\n");
    }

    return 0;
}




gcc first_follow.c -o first_follow
./first_follow

