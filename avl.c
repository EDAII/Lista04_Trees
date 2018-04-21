#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int value;
    struct Node * left;
    struct Node * right;
    int height;
}node;

int max(int a, int b)
{
    return (a >= b ? a : b);
}

int height(node * N)
{
    if (N == NULL)
        return 0;
    else
        return N->height;
}

int getBalance(node * N)
{
    if (N == NULL)
        return 0;
    else
        return height(N->left) - height(N->right);
}

node * newNode(int value)
{
    node * new = (node *)malloc(sizeof(node));
    new->value = value;
    new->left = NULL;
    new->right = NULL;
    new->height = 1;

    return new;
}

node * leftRotate(node * no)
{
    node * y = no->right;
    node * t = y->left;

    y->left = no;
    no->right = t;

    no->height = max(height(no->left), height(no->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

node * rightRotate(node * no)
{
    node * y = no->left;
    node * t = y->right;

    //time to rotate
    y->right = no;
    no->left = t;

    no->height = max(height(no->left), height(no->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

node * insert(node * tree, int value)
{
    //insertion
    if (tree == NULL)
        return newNode(value);

    if (value < tree->value)
        tree->left = insert(tree->left, value);
    else if (value > tree->value)
        tree->right = insert(tree->right, value);
    else
    {
        puts("Repeated values are not allowed in a BST");
        return tree;
    }

    tree->height = max(height(tree->left), height(tree->right)) + 1;

    int balance = getBalance(tree);

    //left left
    if (balance > 1 && value < tree->left->value)
        return rightRotate(tree);
    //right right
    if (balance < -1 && value > tree->right->value)
        return leftRotate(tree);
    //left right
    if (balance > 1 && value > tree->left->value){
        tree->left = leftRotate(tree->left);
        return rightRotate(tree);
    }
    //right left
    if (balance < -1 && value < tree->right->value){
        tree->right = rightRotate(tree->right);
        return leftRotate(tree);
    }

    return tree;
}

void preOrder(node * root)
{
    if (root != NULL)
    {
        printf("%d ", root->value);
        preOrder(root->left);
        preOrder(root->right);
    }
    
}

int main()
{
    node * tree1 = NULL;

    tree1 = insert(tree1, 10);
    tree1 = insert(tree1, 20);
    tree1 = insert(tree1, 30);
    tree1 = insert(tree1, 40);
    tree1 = insert(tree1, 50);
    tree1 = insert(tree1, 25);

    preOrder(tree1);
    return 0;
}
