#include <stdio.h>

#define INF 9999
#define MAX 20

int main() {
    int cost[MAX][MAX], visited[MAX];
    int n, i, j, edges = 0, min, u, v, total = 0;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter cost adjacency matrix (0 for no edge):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            if (cost[i][j] == 0)
                cost[i][j] = INF;
        }
    }

    for (i = 0; i < n; i++)
        visited[i] = 0;

    // Start with vertex 0 (standard textbook choice)
    visited[0] = 1;

    printf("\nEdges in the Minimum Spanning Tree:\n");

    while (edges < n - 1) {
        min = INF;

        for (i = 0; i < n; i++) {
            if (visited[i]) {
                for (j = 0; j < n; j++) {
                    if (!visited[j] && cost[i][j] < min) {
                        min = cost[i][j];
                        u = i;
                        v = j;
                    }
                }
            }
        }

        printf("%d -- %d  :  %d\n", u, v, min);
        total += min;
        visited[v] = 1;
        edges++;
    }

    printf("\nTotal Minimum Cost = %d\n", total);

    return 0;
}
