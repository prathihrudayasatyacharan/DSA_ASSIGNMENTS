#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node *createNode(int value)
{
    struct Node *newNode;

    newNode = (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

struct Node *insert(struct Node *root, int value)
{
    if (root == NULL)
        return createNode(value);

    if (value < root->data)
        root->left = insert(root->left, value);

    else if (value > root->data)
        root->right = insert(root->right, value);

    else
        printf("Duplicate value %d ignored.\n", value);

    return root;
}

void inorder(struct Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

/*
 * Find the smallest node in a subtree.
 * This is used as the inorder successor.
 */
struct Node *findMin(struct Node *root)
{
    struct Node *current = root;

    while (current != NULL && current->left != NULL)
        current = current->left;

    return current;
}

struct Node *deleteNode(struct Node *root, int key)
{
    struct Node *temp;

    if (root == NULL)
        return root;

    /* Search for the node */
    if (key < root->data)
    {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->data)
    {
        root->right = deleteNode(root->right, key);
    }

    /*
     * Node found
     */
    else
    {
        /* Case 1: No child */
        if (root->left == NULL && root->right == NULL)
        {
            printf("Deleting leaf node %d\n", root->data);
            free(root);
            return NULL;
        }

        /* Case 2: Only right child */
        else if (root->left == NULL)
        {
            temp = root->right;

            printf("Deleting node %d with one child\n",
                   root->data);

            free(root);
            return temp;
        }

        /* Case 2: Only left child */
        else if (root->right == NULL)
        {
            temp = root->left;

            printf("Deleting node %d with one child\n",
                   root->data);

            free(root);
            return temp;
        }

        /*
         * Case 3: Two children
         */
        else
        {
            temp = findMin(root->right);

            printf("Deleting node %d with two children\n",
                   root->data);

            root->data = temp->data;

            root->right = deleteNode(root->right,
                                     temp->data);
        }
    }

    return root;
}

void preorder(struct Node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

int main()
{
    struct Node *root = NULL;
    int n, value, key;
    int i;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter the values:\n");

    for (i = 0; i < n; i++)
    {
        scanf("%d", &value);
        root = insert(root, value);
    }

    printf("\nOriginal inorder traversal: ");
    inorder(root);

    printf("\nOriginal preorder traversal: ");
    preorder(root);

    printf("\n\nEnter value to delete: ");
    scanf("%d", &key);

    root = deleteNode(root, key);

    printf("\nInorder traversal after deletion: ");
    inorder(root);

    printf("\nPreorder traversal after deletion: ");
    preorder(root);

    printf("\n");

    return 0;
}
