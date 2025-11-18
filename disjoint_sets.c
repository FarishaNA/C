#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Global arrays for Disjoint Set structure
int parent[MAX_SIZE];
int rank_ds[MAX_SIZE];
int num_elements = 0;

// Function to initialize the disjoint set structure
// Each element is its own parent, and rank is 0.
void makeSet_ds(int n) {
    if (n < 1 || n > MAX_SIZE) {
        printf("Error: Number of elements must be between 1 and %d.\n", MAX_SIZE);
        return;
    }
    num_elements = n;
    for (int i = 0; i < n; i++) {
        parent[i] = i; // Create: Each element is initially in its own set
        rank_ds[i] = 0;
    }
    printf("Successfully created %d disjoint sets (0 to %d).\n", n, n - 1);
}

// Find operation with Path Compression
// Returns the representative (root) of the set containing element 'i'
int findSet_ds(int i) {
    if (i < 0 || i >= num_elements) {
        return -1; // Invalid element
    }
    // Base Case: If 'i' is the root of the tree
    if (parent[i] == i)
        return i;
    
    // Path Compression: Set the parent of 'i' directly to the root
    parent[i] = findSet_ds(parent[i]);
    return parent[i];
}

// Union operation using Union by Rank
void unionSets_ds(int i, int j) {
    if (i < 0 || i >= num_elements || j < 0 || j >= num_elements) {
        printf("Error: Invalid element index.\n");
        return;
    }
    int root_i = findSet_ds(i);
    int root_j = findSet_ds(j);

    // If they are already in the same set, do nothing
    if (root_i != root_j) {
        // Union by Rank: Attach the smaller rank tree under the root of the higher rank tree
        if (rank_ds[root_i] < rank_ds[root_j]) {
            parent[root_i] = root_j;
        } else if (rank_ds[root_i] > rank_ds[root_j]) {
            parent[root_j] = root_i;
        } else {
            // Ranks are the same, make one the root and increment its rank
            parent[root_j] = root_i;
            rank_ds[root_i]++;
        }
        printf("Union successful. Elements %d and %d are now connected.\n", i, j);
    } else {
        printf("Elements %d and %d are already in the same set.\n", i, j);
    }
}

// Utility function to print the current set configuration
void printSets_ds() {
    if (num_elements == 0) {
        printf("No sets created yet.\n");
        return;
    }
    printf("\n--- Current Set Status ---\n");
    printf("Element (Root):\n");
    for (int i = 0; i < num_elements; i++) {
        printf("%d (%d) | ", i, findSet_ds(i));
    }
    printf("\n");
}

int main() {
    int choice, n, i, j, root;
    while (1) {
        printf("\n======= DISJOINT SETS (UNION-FIND) MENU =======\n");
        printf("1. Create Disjoint Sets\n");
        printf("2. Perform Union Operation\n");
        printf("3. Find Representative (Root) of an Element\n");
        printf("4. Print Current Set Status\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter number of elements to create (max %d): ", MAX_SIZE);
                scanf("%d", &n);
                makeSet_ds(n);
                break;
            case 2:
                if (num_elements == 0) {
                    printf("Please create sets first (Option 1).\n");
                    break;
                }
                printf("Enter two elements (i j) to unite their sets (0 to %d): ", num_elements - 1);
                scanf("%d %d", &i, &j);
                unionSets_ds(i, j);
                break;
            case 3:
                if (num_elements == 0) {
                    printf("Please create sets first (Option 1).\n");
                    break;
                }
                printf("Enter element (i) to find its representative (0 to %d): ", num_elements - 1);
                scanf("%d", &i);
                root = findSet_ds(i);
                if (root != -1) {
                    printf("The representative (root) of element %d is %d.\n", i, root);
                }
                break;
            case 4:
                printSets_ds();
                break;
            case 5:
                printf("Exiting Disjoint Sets program.\n");
                return 0;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    }
}