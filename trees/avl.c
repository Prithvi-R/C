#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct tree_t *Tree;
typedef char Type;

struct tree_t
{
    Tree parent;
    Type key;
    Tree left, right;
    int height;
};
int max(int a, int b)
{
    return a > b ? a : b;
}
int min(int a, int b)
{
    return a < b ? a : b;
}
int height(Tree tree)
{
    if (!tree)
        return 0;
    int heightLeft = height(tree->left);
    int heightRight = height(tree->right);
    return max(heightLeft, heightRight) + 1;
}
Tree rotateLeft(Tree tree)
{
    Tree y = tree;

    Tree x = tree->right;
    tree->right = NULL;
    if (x->left)
        y->right = x->left;
    else
        x->left = NULL;
    x->left = y;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));
    return x;
}
Tree rotateRight(Tree tree)
{
    Tree x = tree;
    Tree y = tree->left;
    tree->left = NULL;
    if (y->right)
        x->left = y->right;
    else
        y->right = NULL;
    y->right = x;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));
    return y;
}
Tree newTree(Tree parent, Type key, Tree left, Tree right)
{
    Tree tree = (Tree)calloc(1, sizeof(struct tree_t));
    assert(tree);
    tree->parent = parent;
    tree->key = key;
    tree->left = left;
    tree->right = right;
    tree->height = 1 + max(height(tree->left), height(tree->right));
    return tree;
}

void printPreOrder(Tree tree)
{
    if (!tree)
        return;
    printf("%c ", tree->key);
    printPreOrder(tree->left);
    printPreOrder(tree->right);
}
void printInOrder(Tree tree)
{
    if (!tree)
        return;
    printInOrder(tree->left);
    printf("%c ", tree->key);
    printInOrder(tree->right);
}
void printPostOrder(Tree tree)
{
    if (!tree)
        return;
    printPostOrder(tree->left);
    printPostOrder(tree->right);
    printf("%c ", tree->key);
}
void printTree(Tree tree)
{
    printf("PreOrder: ");
    printPreOrder(tree);
    printf("\n");
    printf("InOrder: ");
    printInOrder(tree);
    printf("\n");
    printf("PostOrder: ");
    printPostOrder(tree);
    printf("\n");
}

int balance(Tree tree)
{

    if (!tree)
        return 0;
    return height(tree->left) - height(tree->right);
}
Tree balancedTree(Tree tree)
{
    int balanceFactor = balance(tree);
    if (balanceFactor > 1 && balance(tree->left) >= 0) // LL
        tree = rotateRight(tree);
    else if (balanceFactor < -1 && balance(tree->right) <= 0) // RR
        tree = rotateLeft(tree);
    else if (balanceFactor > 1 && balance(tree->right) <= 0)
    { // LR
        tree->left = rotateLeft(tree->left);
        tree = rotateRight(tree);
    }
    else if (balanceFactor < -1 && balance(tree->left) >= 0)
    { // RL
        tree->right = rotateRight(tree->right);
        tree = rotateLeft(tree);
    }

    if (tree)
    {
        tree->height = 1 + max(height(tree->left), height(tree->right));
    }
    // printf("PreOrder: ");
    return tree;
}

Tree insertIntoAVL(Tree tree, Type key, Tree parent)
{
    // printf("0rder: ");
    if (!tree)
        return newTree(parent, key, NULL, NULL);
    if (key < tree->key)
        tree->left = insertIntoAVL(tree->left, key, tree);
    else
        tree->right = insertIntoAVL(tree->right, key, tree);

    tree = balancedTree(tree);
    return tree;
}

Tree findMinTreeInAVL(Tree tree)
{
    for (; tree->left; tree = tree->left)
        ;
    return tree;
}
Tree findMaxTreeInAVL(Tree tree)
{
    for (; tree->right; tree = tree->right)
        ;
    return tree;
}
int _print_t(Tree tree, int is_left, int offset, int depth, char s[20][255], int height)
{
    char b[20];
    int width = 5;

    if (!tree || depth >= height)
        return 0;

    sprintf(b, "(%03c)", tree->key);

    int left = _print_t(tree->left, 1, offset, depth + 1, s, height);
    int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s, height);

    for (int i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left)
    {
        for (int i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width / 2 + i] = '-';
        s[2 * depth - 1][offset + left + width / 2] = '.';
    }
    else if (depth && !is_left)
    {
        for (int i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width / 2 + i] = '-';
        s[2 * depth - 1][offset + left + width / 2] = '+';
        s[2 * depth - 1][offset - width / 2 - 1] = '+';
    }

    return left + width + right;
}
void print_tree(Tree tree)
{
    int h = height(tree);
    char s[20][255];
    for (int i = 0; i < 20; i++)
        sprintf(s[i], "%80s", " ");

    _print_t(tree, 0, 0, 0, s, h);

    for (int i = 0; i < h * 2; i++)
        printf("%s\n", s[i]);
}

Tree deleteTreeFromAVL(Tree tree, Type key)
{
    if (!tree)
    {
        printf("KEY NOT FOUND\n");
        return NULL;
    }
    if (key < tree->key)
    {
        printf("At %c, going left to delete %c\n", tree->key, key);
        tree->left = deleteTreeFromAVL(tree->left, key);
        return tree;
    }
    if (key > tree->key)
    {
        printf("At %c, going right to delete %c\n", tree->key, key);
        tree->right = deleteTreeFromAVL(tree->right, key);
        return tree;
    }
    printf("Found %c\n", tree->key);
    Tree t = tree;
    if (!tree->left && !tree->right)
    {
        printf("At %c with no children, going to delete %c\n", tree->key, key);
        free(tree);
        return NULL;
    }
    else if (!tree->left)
    {
        printf("At %c with only right child, going to delete %c\n", tree->key, key);
        t = tree->right;
        t->parent = tree->parent;
        free(tree);
    }
    else if (!tree->right)
    {
        printf("At %c with only left child, going to delete %c\n", tree->key, key);
        t = tree->left;
        t->parent = tree->parent;
        free(tree);
    }
    else
    {
        Tree successor = findMinTreeInAVL(t->right);
        printf("At %c with both children, going to delete %c & successor is %c\n", t->key, key, successor->key);
        t->key = successor->key;
        t->right = deleteTreeFromAVL(t->right, successor->key);
    }
    t = balancedTree(t);
    return t;
}
Tree deleteNode(Tree tree, Type key)
{
    tree = deleteTreeFromAVL(tree, key);
    return balancedTree(tree);
}
int main()
{
    Type keys[] = {'g','s','e','t','a','v','t','q','z','d','c','y'};
    int i, n, k;
    // printf("Enter the no. of elements you want to add in BST: ");
    // scanf("%c", &n);
    Tree bst = NULL;
    for (i = 0; i < 12; i++)
    {
        bst = insertIntoAVL(bst, keys[i], NULL);
        print_tree(bst);
        printf("\n");
    }
    printTree(bst);
    print_tree(bst);
    printf("\n");

    printf("\n");
    bst = deleteNode(bst, 20);
    print_tree(bst);
    printTree(bst);
    printf("\n");
    bst = deleteNode(bst, 45);
    print_tree(bst);
    printTree(bst);
    printf("\n");
}