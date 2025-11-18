#include <stdio.h>
#include <stdlib.h>

// --- 1. Structure Definition ---
struct node {
    int data;
    struct node *left;
    struct node *right;
};

// --- 2. Utility Functions (from previous program) ---

struct node* createNode(int value) {
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    if (newNode != NULL) {
        newNode->data = value;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}

struct node* insert(struct node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    }
    return root;
}

struct node* find(struct node* root, int key) {
    if (root == NULL || root->data == key) {
        return root;
    }
    if (key < root->data) {
        return find(root->left, key);
    } else {
        return find(root->right, key);
    }
}

void inorderTraversal(struct node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

void preorderTraversal(struct node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

void postorderTraversal(struct node* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}

struct node* minValueNode(struct node* node) {
    struct node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

struct node* deleteNode(struct node* root, int key) {
    if (root == NULL) return root;

    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    }
    else { // Node found
        if (root->left == NULL) {
            struct node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct node *temp = root->left;
            free(root);
            return temp;
        }

        struct node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// --- 3. Menu Display Function ---
void displayMenu() {
    printf("\n==================================\n");
    printf("     BINARY SEARCH TREE MENU      \n");
    printf("==================================\n");
    printf("1. Insert Element\n");
    printf("2. Find (Search) Element\n");
    printf("3. Delete Element\n");
    printf("4. Traversal (Inorder, Preorder, Postorder)\n");
    printf("5. Exit\n");
    printf("----------------------------------\n");
    printf("Enter your choice: ");
}

// --- 4. Main Function ---
int main() {
    struct node *root = NULL;
    int choice, value, key;
    struct node *found_node;

    while (1) {
        displayMenu();
        if (scanf("%d", &choice) != 1) {
            // Handle non-integer input
            printf("\nInvalid input. Please enter a number.\n");
            while (getchar() != '\n'); 
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                printf("Value %d inserted successfully.\n", value);
                break;

            case 2:
                printf("Enter value to search: ");
                scanf("%d", &key);
                found_node = find(root, key);
                if (found_node != NULL) {
                    printf("SUCCESS: Value %d found in the tree.\n", key);
                } else {
                    printf("FAILURE: Value %d not found in the tree.\n", key);
                }
                break;

            case 3:
                printf("Enter value to delete: ");
                scanf("%d", &key);
                if (root == NULL) {
                    printf("Tree is empty. Nothing to delete.\n");
                } else {
                    root = deleteNode(root, key);
                    printf("Attempted to delete %d. Check traversal to confirm.\n", key);
                }
                break;

            case 4:
                if (root == NULL) {
                    printf("Tree is empty. Cannot traverse.\n");
                    break;
                }
                printf("\n--- Traversal Results ---\n");
                printf("Inorder (Sorted):    ");
                inorderTraversal(root);
                printf("\nPreorder:            ");
                preorderTraversal(root);
                printf("\nPostorder:           ");
                postorderTraversal(root);
                printf("\n");
                break;

            case 5:
                printf("\nExiting the program. Goodbye!\n");
                exit(0);

            default:
                printf("\nInvalid choice. Please enter a number between 1 and 5.\n");
        }
    }
    return 0;
}