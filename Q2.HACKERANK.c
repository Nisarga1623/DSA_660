#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};

// Create node
struct Node* createNode(int data) {
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    n->data = data;
    n->left = n->right = NULL;
    return n;
}

// Insert in BST
struct Node* insert(struct Node* root, int data) {
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

    return root;
}

// Inorder traversal (no trailing space)
void inorder(struct Node* root, int *first) {
    if (root) {
        inorder(root->left, first);

        if (!(*first)) printf(" ");
        printf("%d", root->data);
        *first = 0;

        inorder(root->right, first);
    }
}

int main() {
    int n, x, insertVal;
    struct Node* root = NULL;

    scanf("%d", &n);

    // Check invalid input
    if (n == -1) {
        printf("Invalid input");
        return 0;
    }

    // Read n router IDs
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);

        if (x == -1) {
            printf("Invalid input");
            return 0;
        }

        root = insert(root, x);
    }

    // Read value to insert
    scanf("%d", &insertVal);

    if (insertVal == -1) {
        printf("Invalid input");
        return 0;
    }

    root = insert(root, insertVal);

    int first = 1;
    inorder(root, &first);

    return 0;
}
