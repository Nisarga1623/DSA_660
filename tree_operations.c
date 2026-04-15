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
