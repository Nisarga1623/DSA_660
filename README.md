# DSA_660
DSA
//BASIC TREE OPERATIONS
#include<stdio.h>
#include<stdlib.h>

struct tree
{
    int data;
    struct tree *left;
    struct tree *right;
};
typedef struct tree TREE;

// Function declarations
TREE *insert_into_bst(TREE *,int);
void inorder(TREE*);
void preorder(TREE*);
void postorder(TREE*);
TREE *delete_from_bst(TREE *,int);

// INSERT
TREE *insert_into_bst(TREE *root,int data)
{
    TREE *newnode,*currnode,*parent;

    newnode=(TREE*)malloc(sizeof(TREE));

    if(newnode==NULL)
    {
        printf("Memory allocation failed\n");
        return root;
    }

    newnode->data=data;
    newnode->left=NULL;
    newnode->right=NULL;

    if(root==NULL)
    {
        printf("Root node inserted\n");
        return newnode;
    }

    currnode=root;
    parent=NULL;

    while(currnode!=NULL)
    {
        parent=currnode;
        if(data < currnode->data)
            currnode=currnode->left;
        else
            currnode=currnode->right;
    }

    if(data < parent->data)
        parent->left=newnode;
    else
        parent->right=newnode;

    printf("Node inserted\n");
    return root;
}

// INORDER
void inorder(TREE *root)
{
    if(root!=NULL)
    {
        inorder(root->left);
        printf("%d ",root->data);
        inorder(root->right);
    }
}

// PREORDER
void preorder(TREE *root)
{
    if(root!=NULL)
    {
        printf("%d ",root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// POSTORDER
void postorder(TREE *root)
{
    if(root!=NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ",root->data);
    }
}

// DELETE
TREE *delete_from_bst(TREE *root,int data)
{
    TREE *currnode,*parent,*successor,*p;

    if(root==NULL)
    {
        printf("Tree is empty\n");
        return root;
    }

    parent=NULL;
    currnode=root;

    while(currnode!=NULL && data!=currnode->data)
    {
        parent=currnode;
        if(data < currnode->data)
            currnode=currnode->left;
        else
            currnode=currnode->right;
    }

    if(currnode==NULL)
    {
        printf("Item not found\n");
        return root;
    }

    if(currnode->left==NULL)
        p=currnode->right;
    else if(currnode->right==NULL)
        p=currnode->left;
    else
    {
        successor=currnode->right;
        while(successor->left!=NULL)
            successor=successor->left;

        successor->left=currnode->left;
        p=currnode->right;
    }

    if(parent==NULL)
    {
        free(currnode);
        return p;
    }

    if(currnode==parent->left)
        parent->left=p;
    else
        parent->right=p;

    free(currnode);
    return root;
}

// MAIN FUNCTION
int main()
{
    TREE *root=NULL;
    int choice,data;

    while(1)
    {
        printf("\n\n***** MENU *****\n");
        printf("1. Insert\n");
        printf("2. Inorder\n");
        printf("3. Preorder\n");
        printf("4. Postorder\n");
        printf("5. Delete\n");
        printf("6. Exit\n");

        printf("Enter choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                printf("Enter data: ");
                scanf("%d",&data);
                root=insert_into_bst(root,data);
                break;

            case 2:
                printf("Inorder: ");
                inorder(root);
                break;

            case 3:
                printf("Preorder: ");
                preorder(root);
                break;

            case 4:
                printf("Postorder: ");
                postorder(root);
                break;

            case 5:
                printf("Enter data to delete: ");
                scanf("%d",&data);
                root=delete_from_bst(root,data);
                break;

            case 6:
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }
}

_______________________________________________________________________________________________________________________________________
//HACKERANK QUESTIONS
Q1.Desktop File Indexing System

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int data) {
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

    return root;
}

struct Node* findMin(struct Node* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    int n, x, insertNode, deleteVal;
    struct Node* root = NULL;

    scanf("%d", &n);

    // Initial nodes
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        root = insert(root, x);
    }

    // Extra insertion
    scanf("%d", &insertNode);
    root = insert(root, insertNode);

    // Deletion
    scanf("%d", &deleteVal);
    root = deleteNode(root, deleteVal);

    printf("Current File Index sorted in ascending order: ");
    inorder(root);

    return 0;
}
______________________________________________________________________________________________________________________________________
Q2.Network Routing System

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














