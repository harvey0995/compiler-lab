
#include <stdio.h>
#define MAX 20

int n, symbols;
int epsilon[MAX][MAX];
int trans[MAX][MAX][MAX];
int closure[MAX][MAX];

/* Find epsilon closure of a state */
void findClosure(int state, int start)
{
    int i;

    if (closure[start][state])
        return;

    closure[start][state] = 1;

    for (i = 0; i < n; i++)
    {
        if (epsilon[state][i])
            findClosure(i, start);
    }
}

/* Calculate epsilon closure for all states */
void calculateClosures()
{
    int i;

    for (i = 0; i < n; i++)
        findClosure(i, i);
}

int main()
{
    int i, j, k, s;
    int m, from, to;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols: ");
    scanf("%d", &symbols);

    /* Initialize */
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            epsilon[i][j] = 0;
            closure[i][j] = 0;

            for (s = 0; s < symbols; s++)
                trans[s][i][j] = 0;
        }
    }

    /* Read epsilon transitions */
    printf("Enter number of epsilon transitions: ");
    scanf("%d", &m);

    printf("Enter epsilon transitions (from to):\n");

    for (i = 0; i < m; i++)
    {
        scanf("%d %d", &from, &to);
        epsilon[from][to] = 1;
    }

    /* Calculate epsilon closures */
    calculateClosures();

    printf("\nEpsilon Closures:\n");

    for (i = 0; i < n; i++)
    {
        printf("E-Closure(q%d) = { ", i);

        for (j = 0; j < n; j++)
        {
            if (closure[i][j])
                printf("q%d ", j);
        }

        printf("}\n");
    }

    /* Read transitions for each input symbol */
    for (s = 0; s < symbols; s++)
    {
        printf("\nEnter transitions for input symbol %d.\n", s);
        printf("Enter number of transitions: ");
        scanf("%d", &m);

        printf("Enter transitions (from to):\n");

        for (i = 0; i < m; i++)
        {
            scanf("%d %d", &from, &to);
            trans[s][from][to] = 1;
        }
    }

    /* Convert epsilon-NFA to NFA */
    printf("\nNFA without epsilon transitions:\n");

    for (s = 0; s < symbols; s++)
    {
        printf("\nFor input symbol %d:\n", s);

        for (i = 0; i < n; i++)
        {
            int result[MAX] = {0};

            /* Step 1: Find epsilon closure of current state */
            for (j = 0; j < n; j++)
            {
                if (closure[i][j])
                {
                    /* Step 2: Follow input symbol */
                    for (k = 0; k < n; k++)
                    {
                        if (trans[s][j][k])
                        {
                            /* Step 3: Add epsilon closure of destination */
                            int p;

                            for (p = 0; p < n; p++)
                            {
                                if (closure[k][p])
                                    result[p] = 1;
                            }
                        }
                    }
                }
            }

            printf("q%d -> { ", i);

            for (j = 0; j < n; j++)
            {
                if (result[j])
                    printf("q%d ", j);
            }

            printf("}\n");
        }
    }

    return 0;
}






gcc epsilon_nfa.c -o epsilon_nfa
./epsilon_nfa

