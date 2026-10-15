
#include <stdio.h>

#define MAX 10
#define MAX_DFA 100

int main()
{
    int n, m, i, j, k, l, c;
    int nfa[MAX][MAX][MAX], count[MAX][MAX];
    int dfa[MAX_DFA][MAX], trans[MAX_DFA][MAX];
    int final[MAX], dfaFinal[MAX_DFA];
    int total = 1, found;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of symbols: ");
    scanf("%d", &m);

    if (n < 1 || n > MAX || m < 1 || m > MAX)
    {
        printf("Invalid number of states or symbols!\n");
        return 1;
    }

    printf("Enter NFA transitions:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            printf("Number of states from q%d on symbol %d: ", i, j);
            scanf("%d", &count[i][j]);

            if (count[i][j] < 0 || count[i][j] > n)
            {
                printf("Invalid transition count!\n");
                return 1;
            }

            for (k = 0; k < count[i][j]; k++)
            {
                scanf("%d", &nfa[i][j][k]);

                if (nfa[i][j][k] < 0 || nfa[i][j][k] >= n)
                {
                    printf("Invalid destination state!\n");
                    return 1;
                }
            }
        }
    }

    for (i = 0; i < n; i++)
        final[i] = 0;

    printf("Enter number of final states: ");
    scanf("%d", &k);

    if (k < 0 || k > n)
    {
        printf("Invalid number of final states!\n");
        return 1;
    }

    printf("Enter final states: ");
    for (i = 0; i < k; i++)
    {
        int state;
        scanf("%d", &state);

        if (state < 0 || state >= n)
        {
            printf("Invalid final state!\n");
            return 1;
        }

        final[state] = 1;
    }

    for (i = 0; i < MAX_DFA; i++)
        for (j = 0; j < n; j++)
            dfa[i][j] = 0;

    dfa[0][0] = 1;

    for (i = 0; i < total; i++)
    {
        for (j = 0; j < m; j++)
        {
            int temp[MAX] = {0};

            for (k = 0; k < n; k++)
                if (dfa[i][k])
                    for (l = 0; l < count[k][j]; l++)
                        temp[nfa[k][j][l]] = 1;

            found = -1;

            for (k = 0; k < total; k++)
            {
                for (c = 0; c < n && dfa[k][c] == temp[c]; c++);

                if (c == n)
                {
                    found = k;
                    break;
                }
            }

            if (found == -1)
            {
                if (total >= MAX_DFA)
                {
                    printf("Too many DFA states!\n");
                    return 1;
                }

                found = total++;

                for (k = 0; k < n; k++)
                    dfa[found][k] = temp[k];
            }

            trans[i][j] = found;
        }
    }

    printf("\nDFA States:\n");

    for (i = 0; i < total; i++)
    {
        dfaFinal[i] = 0;
        printf("D%d = {", i);

        for (j = 0; j < n; j++)
        {
            if (dfa[i][j])
            {
                printf("q%d ", j);

                if (final[j])
                    dfaFinal[i] = 1;
            }
        }

        if (dfaFinal[i])
            printf("} (Final)\n");
        else
            printf("}\n");
    }

    printf("\nDFA Transition Table:\n");

    for (i = 0; i < total; i++)
        for (j = 0; j < m; j++)
            printf("D%d --%d--> D%d\n", i, j, trans[i][j]);

    printf("\nStart state: D0\n");

    return 0;
}






gcc nfa_dfa.c -o nfa_dfa
./nfa_dfa

