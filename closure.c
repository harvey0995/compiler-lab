
#include <stdio.h>

#define MAX 20

int n, na;
char alphabet[MAX];
int e[MAX][MAX];
int visited[MAX];

void epsilonClosure(int state)
{
    int i;

    visited[state] = 1;
    printf("q%d ", state);

    for (i = 0; i < n; i++)
    {
        if (e[state][i] && !visited[i])
            epsilonClosure(i);
    }
}

int main()
{
    int i, j, m;
    int from, to;
    char symbol;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of alphabets (including e): ");
    scanf("%d", &na);

    printf("Enter alphabets (e must be last): ");
    for (i = 0; i < na; i++)
        scanf(" %c", &alphabet[i]);

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            e[i][j] = 0;

    printf("Enter number of transitions: ");
    scanf("%d", &m);

    printf("Enter transitions (from symbol to):\n");

    for (i = 0; i < m; i++)
    {
        scanf("%d %c %d", &from, &symbol, &to);

        if (symbol == 'e')
            e[from][to] = 1;
    }

    printf("\nEpsilon Closures:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            visited[j] = 0;

        printf("E-Closure(q%d) = { ", i);
        epsilonClosure(i);
        printf("}\n");
    }

    return 0;
}






gcc epsilon.c -o epsilon
./epsilon



Enter number of states: 3
Enter number of alphabets (including e): 3
Enter alphabets (e must be last): a b e
Enter number of transitions: 3
Enter transitions (from symbol to):
0 e 1
1 a 2
1 e 2