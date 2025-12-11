#include <stdio.h>

#define INF 9999
#define MAX 20

int main() {
    int n, source;
    int cost[MAX][MAX], dist[MAX], visited[MAX];
    int i, j, count, u, v, min;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter the cost adjacency matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            if (cost[i][j] == 0 && i != j)
                cost[i][j] = INF;   // No edge is represented by INF
        }
    }

    printf("Enter the source vertex (0 to %d): ", n - 1);
    scanf("%d", &source);

    for (i = 0; i < n; i++) {
        dist[i] = cost[source][i];
        visited[i] = 0;
    }

    dist[source] = 0;
    visited[source] = 1;
    count = 1;

    // Main Dijkstra Loop
    while (count < n) {
        min = INF;

        // Select the unvisited vertex with the smallest distance
        for (i = 0; i < n; i++) {
            if (dist[i] < min && visited[i] == 0) {
                min = dist[i];
                u = i;
            }
        }

        visited[u] = 1;

        // Relax edges
        for (v = 0; v < n; v++) {
            if (visited[v] == 0 && dist[u] + cost[u][v] < dist[v]) {
                dist[v] = dist[u] + cost[u][v];
            }
        }

        count++;
    }

    //Output shortest distances
    printf("\nShortest distances from source %d:\n", source);
    for (i = 0; i < n; i++) {
        printf("Vertex %d : %d\n", i, dist[i]);
    }

    return 0;
}
