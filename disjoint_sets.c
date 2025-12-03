#include <stdio.h>

#define MAX 50

int parent[MAX];  // Stores parent of each element
int n;            // Number of elements

/* ========== CREATE SET ========== */
void createSet(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = -1;   // Each element is initially a root (representative)
    }
}

/* ========== FIND OPERATION (WITH PATH COMPRESSION) ========== */
int findSet(int x) {
    if (parent[x] == -1)
        return x;                // x is a representative (root)
    return parent[x] = findSet(parent[x]);   // Path compression
}

/* ========== UNION OPERATION ========== */
void unionSet(int x, int y) {
    int rootX = findSet(x);
    int rootY = findSet(y);

    if (rootX != rootY) {
        parent[rootX] = rootY;  // Attach rootX under rootY
        printf("Union done between %d and %d\n", x, y);
    } else {
        printf("They are already in the same set!\n");
    }
}

/* ========== DISPLAY SETS ========== */
void displaySets() {
    printf("\nElement : Parent\n");
    for (int i = 0; i < n; i++) {
        printf("%d --> %d\n", i, parent[i]);
    }
}

/* ========== MAIN MENU ========== */
int main() {
    int choice, a, b;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    createSet(n);

    while (1) {
        printf("\n====== DISJOINT SET MENU ======\n");
        printf("1. Find Set\n");
        printf("2. Union\n");
        printf("3. Display Sets\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("Enter element to find: ");
                scanf("%d", &a);
                printf("Representative of %d is %d\n", a, findSet(a));
                break;

            case 2:
                printf("Enter two elements to union: ");
                scanf("%d %d", &a, &b);
                unionSet(a, b);
                break;

            case 3:
                displaySets();
                break;

            case 4:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
