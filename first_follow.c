#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100
#define SET 128

typedef struct {
    char lhs;
    char rhs[SET];
} Production;

Production p[MAX];
int n = 0;
char first[26][SET], follow[26][SET];
int nt[26] = {0};

int add(char *set, char c) {
    if (strchr(set, c) != NULL)
        return 0;

    int len = strlen(set);
    set[len] = c;
    set[len + 1] = '\0';
    return 1;
}

int isNonTerminal(char c) {
    return c >= 'A' && c <= 'Z';
}

void findFirst() {
    int changed;

    do {
        changed = 0;

        for (int i = 0; i < n; i++) {
            int a = p[i].lhs - 'A';
            char *rhs = p[i].rhs;
            int nullable = 1;

            if (strcmp(rhs, "#") == 0) {
                changed |= add(first[a], '#');
                continue;
            }

            for (int j = 0; rhs[j] != '\0'; j++) {
                char c = rhs[j];

                if (!isNonTerminal(c)) {
                    changed |= add(first[a], c);
                    nullable = 0;
                    break;
                }

                int b = c - 'A';

                for (int k = 0; first[b][k]; k++) {
                    if (first[b][k] != '#')
                        changed |= add(first[a], first[b][k]);
                }

                if (strchr(first[b], '#') == NULL) {
                    nullable = 0;
                    break;
                }
            }

            if (nullable)
                changed |= add(first[a], '#');
        }
    } while (changed);
}

void findFollow(char start) {
    add(follow[start - 'A'], '$');

    int changed;

    do {
        changed = 0;

        for (int i = 0; i < n; i++) {
            int a = p[i].lhs - 'A';
            char *rhs = p[i].rhs;
            int len = strlen(rhs);

            for (int j = 0; j < len; j++) {
                char c = rhs[j];

                if (!isNonTerminal(c))
                    continue;

                int b = c - 'A';
                int nullable = 1;

                for (int k = j + 1; k < len; k++) {
                    char d = rhs[k];

                    if (!isNonTerminal(d)) {
                        changed |= add(follow[b], d);
                        nullable = 0;
                        break;
                    }

                    int x = d - 'A';

                    for (int t = 0; first[x][t]; t++) {
                        if (first[x][t] != '#')
                            changed |= add(follow[b], first[x][t]);
                    }

                    if (strchr(first[x], '#') == NULL) {
                        nullable = 0;
                        break;
                    }
                }

                if (nullable) {
                    for (int k = 0; follow[a][k]; k++)
                        changed |= add(follow[b], follow[a][k]);
                }
            }
        }
    } while (changed);
}

int main() {
    int lines;
    char input[SET];
    char start = '\0';

    printf("Enter number of production lines: ");
    scanf("%d", &lines);
    getchar();

    printf("Enter productions (use # for epsilon):\n");

    for (int i = 0; i < lines; i++) {
        if (!fgets(input, sizeof(input), stdin))
            return 1;

        char clean[SET];
        int k = 0;

        for (int j = 0; input[j]; j++) {
            if (!isspace((unsigned char)input[j]))
                clean[k++] = input[j];
        }
        clean[k] = '\0';

        char *eq = strchr(clean, '=');

        if (!eq || !isNonTerminal(clean[0])) {
            printf("Invalid production format.\n");
            return 1;
        }

        char lhs = clean[0];

        if (start == '\0')
            start = lhs;

        nt[lhs - 'A'] = 1;
        char *rhs = eq + 1;
        char *part = strtok(rhs, "|");

        while (part != NULL) {
            if (n >= MAX) {
                printf("Too many productions.\n");
                return 1;
            }

            p[n].lhs = lhs;
            strcpy(p[n].rhs, part);

            for (int j = 0; part[j]; j++) {
                if (isNonTerminal(part[j]))
                    nt[part[j] - 'A'] = 1;
            }

            n++;
            part = strtok(NULL, "|");
        }
    }

    findFirst();
    findFollow(start);

    printf("\nFIRST sets:\n");

    for (int i = 0; i < 26; i++) {
        if (nt[i]) {
            printf("FIRST(%c) = { ", 'A' + i);

            for (int j = 0; first[i][j]; j++)
                printf("%c ", first[i][j]);

            printf("}\n");
        }
    }

    printf("\nFOLLOW sets:\n");

    for (int i = 0; i < 26; i++) {
        if (nt[i]) {
            printf("FOLLOW(%c) = { ", 'A' + i);

            for (int j = 0; follow[i][j]; j++)
                printf("%c ", follow[i][j]);

            printf("}\n");
        }
    }

    return 0;
}





gcc first_follow.c -o first_follow
./first_follow

