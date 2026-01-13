#include <stdio.h>
#include <limits.h>

#define MAX 100

int main() {
    int n, i, j, k;
    int cost[MAX][MAX];
    int near[MAX];
    int t[MAX][2];   // to store MST edges
    int min, u, v;
    int mincost = 0;

    // Input number of vertices
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix (0 means no edge):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            if (cost[i][j] == 0)
                cost[i][j] = INT_MAX; // mark no edge
        }
    }

    // Step 1: Find smallest edge
    min = INT_MAX;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (cost[i][j] < min) {
                min = cost[i][j];
                u = i;
                v = j;
            }
        }
    }

    // Add first edge to MST
    t[0][0] = u;
    t[0][1] = v;
    mincost += cost[u][v];

    // Initialize near[]
    for (i = 0; i < n; i++) {
        if (cost[i][u] < cost[i][v])
            near[i] = u;
        else
            near[i] = v;
    }
    near[u] = near[v] = -1; // mark as included in MST

    // Step 2: Find remaining n-2 edges
    for (i = 1; i < n - 1; i++) {
        min = INT_MAX;
        int jmin = -1;

        // Find vertex with minimum edge to MST
        for (j = 0; j < n; j++) {
            if (near[j] != -1 && cost[j][near[j]] < min) {
                min = cost[j][near[j]];
                jmin = j;
            }
        }

        // Add edge to MST
        t[i][0] = jmin;
        t[i][1] = near[jmin];
        mincost += cost[jmin][near[jmin]];
        near[jmin] = -1; // mark as included

        // Update near[]
        for (k = 0; k < n; k++) {
            if (near[k] != -1 && cost[k][jmin] < cost[k][near[k]]) {
                near[k] = jmin;
            }
        }
    }

    // Print MST
    printf("\nEdges in MST:\n");
    for (i = 0; i < n - 1; i++) {
        printf("%d -- %d\n", t[i][0] + 1, t[i][1] + 1); // +1 to show 1-based vertices
    }

    printf("Minimum cost = %d\n", mincost);

    return 0;
}
