#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 20
#define MAX_EDGES 100

// --- Disjoint Set Utilities (Integrated for Kruskal's) ---
int parent_k[MAX_VERTICES];
int rank_k[MAX_VERTICES];
int kruskal_num_V = 0;

void makeSet_kruskal(int n) {
    kruskal_num_V = n;
    for (int i = 0; i < n; i++) {
        parent_k[i] = i; 
        rank_k[i] = 0;
    }
}

int findSet_kruskal(int i) {
    if (parent_k[i] == i) return i;
    parent_k[i] = findSet_kruskal(parent_k[i]);
    return parent_k[i];
}

void unionSets_kruskal(int i, int j) {
    int root_i = findSet_kruskal(i);
    int root_j = findSet_kruskal(j);

    if (root_i != root_j) {
        if (rank_k[root_i] < rank_k[root_j]) {
            parent_k[root_i] = root_j;
        } else if (rank_k[root_i] > rank_k[root_j]) {
            parent_k[root_j] = root_i;
        } else {
            parent_k[root_j] = root_i;
            rank_k[root_i]++;
        }
    }
}
// --- End Disjoint Set Utilities ---

// Edge structure and global edge array
struct Edge {
    int src, dest, weight;
};

struct Edge edges[MAX_EDGES];
int kruskal_num_E = 0;

// Comparator function for sorting edges by weight (used by qsort)
int compareEdges(const void* a, const void* b) {
    struct Edge* edgeA = (struct Edge*)a;
    struct Edge* edgeB = (struct Edge*)b;
    return edgeA->weight - edgeB->weight;
}

// Function to run Kruskal's MST algorithm
void kruskalMST_run() {
    if (kruskal_num_V == 0 || kruskal_num_E == 0) {
        printf("Error: Please input vertices and edges first (Option 1).\n");
        return;
    }
    
    // Step 1: Sort all edges by weight
    qsort(edges, kruskal_num_E, sizeof(struct Edge), compareEdges);

    // Step 2: Initialize Disjoint Sets
    makeSet_kruskal(kruskal_num_V);

    struct Edge result[MAX_VERTICES]; 
    int e = 0; // Index for result[]
    int i = 0; // Index for sorted edges
    int minimumCost = 0;

    printf("\n--- Kruskal's Algorithm Output ---\n");
    printf("Selected Edges for MST:\n");

    // Step 3: Iterate through sorted edges, checking for cycles
    while (e < kruskal_num_V - 1 && i < kruskal_num_E) {
        struct Edge next_edge = edges[i++];

        int x = findSet_kruskal(next_edge.src);
        int y = findSet_kruskal(next_edge.dest);

        // If including this edge does NOT form a cycle
        if (x != y) {
            result[e++] = next_edge;
            unionSets_kruskal(x, y); 
            minimumCost += next_edge.weight;
            printf("(%d -- %d) with weight %d\n", next_edge.src, next_edge.dest, next_edge.weight);
        }
    }

    if (e != kruskal_num_V - 1) {
        printf("\nWARNING: The graph is not connected. A Spanning Forest was found.\n");
    }

    printf("\nTotal Minimum Cost of Spanning Tree: %d\n", minimumCost);
}

// Function for user input
void input_graph_kruskal() {
    int V, E, src, dest, weight;
    printf("Enter number of Vertices (max %d): ", MAX_VERTICES);
    scanf("%d", &V);
    if (V < 1 || V > MAX_VERTICES) {
        printf("Invalid number of vertices.\n");
        return;
    }
    kruskal_num_V = V;
    kruskal_num_E = 0;
    
    printf("Enter number of Edges (max %d): ", MAX_EDGES);
    scanf("%d", &E);
    if (E < 1 || E > MAX_EDGES) {
        printf("Invalid number of edges.\n");
        return;
    }

    printf("Enter edges in the format: source destination weight (e.g., 0 1 10)\n");
    for (int i = 0; i < E; i++) {
        printf("Edge %d: ", i + 1);
        if (scanf("%d %d %d", &src, &dest, &weight) != 3) {
            printf("Invalid input format. Skipping edge.\n");
            while (getchar() != '\n');
            i--;
            continue;
        }
        if (src < 0 || src >= V || dest < 0 || dest >= V) {
             printf("Invalid vertex index (%d or %d). Skipping edge.\n", src, dest);
             i--;
             continue;
        }
        edges[kruskal_num_E].src = src;
        edges[kruskal_num_E].dest = dest;
        edges[kruskal_num_E].weight = weight;
        kruskal_num_E++;
    }
    printf("Graph input complete. Ready to run Kruskal's algorithm.\n");
}


int main() {
    int choice;
    while (1) {
        printf("\n======= KRUSKAL'S MST MENU =======\n");
        printf("1. Input Graph Edges and Weights\n");
        printf("2. Run Kruskal's Algorithm\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                input_graph_kruskal();
                break;
            case 2:
                kruskalMST_run();
                break;
            case 3:
                printf("Exiting Kruskal's Algorithm program.\n");
                return 0;
            default:
                printf("Invalid choice. Please enter a number between 1 and 3.\n");
        }
    }
}