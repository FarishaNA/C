#include <stdio.h>
#include <stdlib.h>

// Structure for a BST Node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

/* ===================== INSERTION ===================== */
struct Node* insert(struct Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    } else {
        printf("Duplicate values not allowed in BST!\n");
    }

    return root;
}

/* ===================== SEARCH ===================== */
struct Node* search(struct Node* root, int key) {
    if (root == NULL || root->data == key)
        return root;

    if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}

/* ===================== FIND MINIMUM NODE (for deletion) ===================== */
struct Node* findMin(struct Node* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

/* ===================== DELETION ===================== */
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) {
        printf("Value not found!\n");
        return root;
    }

    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } 
    else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } 
    else { 
        // Node found – 3 possible cases

        // CASE 1: No child
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }

        // CASE 2: One child
        else if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
           return temp;
        }

        // CASE 3: Two children
        struct Node* temp = findMin(root->right);
        root->data = temp->data;  
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

/* ===================== TRAVERSALS ===================== */

// Inorder Traversal (Left, Root, Right)
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Preorder Traversal (Root, Left, Right)
void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Postorder Traversal (Left, Right, Root)
void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

/* ===================== MAIN MENU ===================== */
int main() {
    struct Node* root = NULL;
    int choice, value;

    while (1) {
        printf("\n\n====== BINARY SEARCH TREE MENU ======\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search (Find)\n");
        printf("4. Inorder Traversal\n");
        printf("5. Preorder Traversal\n");
        printf("6. Postorder Traversal\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;

            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                break;

            case 3:
                printf("Enter value to search: ");
                scanf("%d", &value);
                if (search(root, value) != NULL)
                    printf("Value %d found in BST!\n", value);
                else
                    printf("Value %d NOT found!\n", value);
                break;

            case 4:
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;

            case 5:
                printf("Preorder Traversal: ");
                preorder(root);
                printf("\n");
                break;

            case 6:
                printf("Postorder Traversal: ");
                postorder(root);
                printf("\n");
                break;

            case 7:
                printf("Exiting program...\n");
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
