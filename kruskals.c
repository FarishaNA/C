#include <stdio.h>

#define MAX 30

struct Edge {
    int u, v, w;
};

int parent[MAX];

int findSet(int x) {
    if (parent[x] == -1)
        return x;
    return parent[x] = findSet(parent[x]);
}

void unionSet(int x, int y) {
    int rootX = findSet(x);
    int rootY = findSet(y);
    parent[rootX] = rootY;
}

int main() {
    struct Edge edges[MAX], result[MAX], temp;
    int n, e;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &e);

    printf("Enter edges (u v weight):\n");
    for (int i = 0; i < e; i++)
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);

    // Sort edges by weight
    for (int i = 0; i < e - 1; i++) {
        for (int j = i + 1; j < e; j++) {
            if (edges[i].w > edges[j].w) {
                temp = edges[i];
                edges[i] = edges[j];
                edges[j] = temp;
            }
        }
    }

    // Initialize disjoint set
    for (int i = 0; i < n; i++)
        parent[i] = -1;

    int count = 0, total = 0;

    printf("\nEdges in Minimum Spanning Tree:\n");

    for (int i = 0; i < e; i++) {
        int u = edges[i].u;
        int v = edges[i].v;

        if (findSet(u) != findSet(v)) {
            result[count++] = edges[i];
            total += edges[i].w;
            unionSet(u, v);
        }

        if (count == n - 1)
            break;
    }

    for (int i = 0; i < count; i++)
        printf("%d -- %d : %d\n", result[i].u, result[i].v, result[i].w);

    printf("\nTotal Minimum Cost = %d\n", total);

    return 0;
}
