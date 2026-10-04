#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Node {
    int vertex;
    struct Node *next;
};

int main() {
    int n, e, u, v;
    int matrix[MAX][MAX] = {0};
    struct Node *list[MAX] = {NULL};

    printf("Enter number of buildings: ");
    scanf("%d", &n);

    printf("Enter number of pathways: ");
    scanf("%d", &e);

    for (int i = 0; i < e; i++) {
        scanf("%d %d", &u, &v);

        matrix[u][v] = 1;
        matrix[v][u] = 1;

        struct Node *p = malloc(sizeof(struct Node));
        p->vertex = v;
        p->next = list[u];
        list[u] = p;

        p = malloc(sizeof(struct Node));
        p->vertex = u;
        p->next = list[v];
        list[v] = p;
    }

    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }

    printf("\nAdjacency List:\n");
    for (int i = 0; i < n; i++) {
        printf("%d: ", i);
        struct Node *p = list[i];
        while (p) {
            printf("%d ", p->vertex);
            p = p->next;
        }
        printf("\n");
    }

    return 0;
}
