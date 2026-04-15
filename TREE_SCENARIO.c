#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left, *right;
};

// Create Node
struct node* create(int val) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = val;
    temp->left = temp->right = NULL;
    return temp;
}

// Insert Function
struct node* insert(struct node* root, int val) {
    if (root == NULL)
        return create(val);

    if (val < root->data)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);

    return root;
}

// Search Function
struct node* search(struct node* root, int key) {
    if (root == NULL || root->data == key)
        return root;

    if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}

// Find Minimum (for deletion)
struct node* findMin(struct node* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

// Delete Function
struct node* deleteNode(struct node* root, int val) {
    if (root == NULL)
        return root;

    if (val < root->data)
        root->left = deleteNode(root->left, val);
    else if (val > root->data)
        root->right = deleteNode(root->right, val);
    else {
        // One child or no child
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }

        // Two children
        struct node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Inorder Traversal
void inorder(struct node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Main Menu
int main() {
    struct node* root = NULL;
    int choice, val;

    do {
        printf("\n--- BST MENU ---");
        printf("\n1. Insert");
        printf("\n2. Search");
        printf("\n3. Delete");
        printf("\n4. Display (Inorder)");
        printf("\n5. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &val);
                root = insert(root, val);
                break;

            case 2:
                printf("Enter value to search: ");
                scanf("%d", &val);
                if (search(root, val))
                    printf("Found!");
                else
                    printf("Not Found!");
                break;

            case 3:
                printf("Enter value to delete: ");
                scanf("%d", &val);
                root = deleteNode(root, val);
                break;

            case 4:
                printf("Inorder Traversal: ");
                inorder(root);
                break;

            case 5:
                printf("Exiting...");
                break;

            default:
                printf("Invalid choice!");
        }

    } while(choice != 5);

    return 0;
}
