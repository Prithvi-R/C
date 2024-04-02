#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct tree_t *Tree;
typedef int Type;

struct tree_t
{
    Tree parent;
    Type key;
    Tree left, right;
};

Tree newTree(Tree parent, Type key, Tree left, Tree right)
{
    Tree tree = (Tree)calloc(1, sizeof(struct tree_t));
    assert(tree);
    tree->parent = parent;
    tree->key = key;
    tree->left = left;
    tree->right = right;
    return tree;
}

void printPreOrder(Tree tree)
{
    if (!tree)
        return;
    printf("%d ", tree->key);
    printPreOrder(tree->left);
    printPreOrder(tree->right);
}
void printInOrder(Tree tree)
{
    if (!tree)
        return;
    printInOrder(tree->left);
    printf("%d ", tree->key);
    printInOrder(tree->right);
}
void printPostOrder(Tree tree)
{
    if (!tree)
        return;
    printPostOrder(tree->left);
    printPostOrder(tree->right);
    printf("%d ", tree->key);
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

Tree insertIntoBST(Tree tree, int key, Tree parent)
{
    if (!tree)
        return newTree(parent, key, NULL, NULL);
    if (key < tree->key)
        tree->left = insertIntoBST(tree->left, key, tree);
    else
        tree->right = insertIntoBST(tree->right, key, tree);
    return tree;
}
Tree insertIntoBSTIterative(Tree tree, int key)
{
    if (!tree)
        return newTree(key, NULL, NULL, NULL);
    Tree current = tree;
    Tree parent = tree->parent;
    while (current)
    {
        parent = current;
        if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }
    if (key < parent->key)
        parent->left = newTree(key, NULL, parent, NULL);
    else
        parent->right = newTree(key, NULL, parent, NULL);
    return tree;
}
Tree findTreeInBST(Tree tree, int key)
{
    if (!tree)
        return NULL;
    if (key == tree->key)
        return tree;
    if (key < tree->key)
        return findTreeInBST(tree->left, key);
    return findTreeInBST(tree->right, key);
}
Tree findTreeInBSTIterative(Tree tree, int key)
{
    while (tree)
    {
        if (key == tree->key)
            return tree;
        if (key < tree->key)
            tree = tree->left;
        else
            tree = tree->right;
    }
    return NULL;
}

int isBST(Tree tree)
{
    if (!tree)
        return 1;
    if (tree->left)
        if (tree->key < maxKey(tree->left))
            return 0;
    if (tree->right)
        if (tree->key > minKey(tree->right))
            return 0;

    int x = isBST(tree->left);
    int y = isBST(tree->right);
    // printf("At %d, got: %d & %d\n", tree->key, x, y);
    return x && y;
}
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
    printf("At %3d, Left: %3d, Right: %3d\n", tree->key, heightLeft, heightRight);
    return max(heightLeft, heightRight) + 1;
}
int depth(Tree tree)
{
    int depth = 0;
    for (; tree->parent; tree = tree->parent)
        depth++;
    return depth;
}

Tree findMinTreeInBST(Tree tree)
{
    for (; tree->left; tree = tree->left)
        ;
    return tree;
}
Tree findMaxTreeInBST(Tree tree)
{
    for (; tree->right; tree = tree->right)
        ;
    return tree;
}

int maxKey(Tree tree)
{
    if (!tree)
        return 0;
    if (tree->left == NULL && tree->right == NULL)
        return tree->key;
    if (!tree->left)
        return max(tree->key, maxKey(tree->right));
    if (!tree->right)
        return max(tree->key, maxKey(tree->left));
    int maxLeftRight = max(maxKey(tree->left), maxKey(tree->right));
    return max(tree->key, maxLeftRight);
}
int minKey(Tree tree)
{
    if (!tree)
        return 0;
    if (tree->left == NULL && tree->right == NULL)
        return tree->key;
    if (!tree->left)
        return min(tree->key, minKey(tree->right));
    if (!tree->right)
        return min(tree->key, minKey(tree->left));
    int minLeftRight = min(minKey(tree->left), minKey(tree->right));
    return min(tree->key, minLeftRight);
}

Tree deleteTreeFromBST(Tree tree, int key)
{
    if (!tree)
    {
        printf("KEY NOT FOUND\n");
        return NULL;
    }
    if (key < tree->key)
    {
        printf("At %d, going left to delete %d\n", tree->key, key);
        tree->left = deleteTreeFromBST(tree->left, key);
        return tree;
    }
    if (key > tree->key)
    {
        printf("At %d, going right to delete %d\n", tree->key, key);
        tree->right = deleteTreeFromBST(tree->right, key);
        return tree;
    }
    printf("Found %d\n", tree->key);
    if (!tree->left && !tree->right)
    {
        printf("At %d with no children, going to delete %d\n", tree->key, key);
        free(tree);
        return NULL;
    }
    if (tree->left == NULL)
    {
        printf("At %d with only right child, going to delete %d\n", tree->key, key);
        Tree right = tree->right;
        right->parent = tree->parent;
        free(tree);
        return right;
    }
    if (tree->right == NULL)
    {
        printf("At %d with only left child, going to delete %d\n", tree->key, key);
        Tree left = tree->left;
        left->parent = tree->parent;
        free(tree);
        return left;
    }
    Tree successor = findMinTreeInBST(tree->right);
    printf("At %d with both children, going to delete %d & successor is %d\n", tree->key, key, successor->key);
    tree->key = successor->key;
    tree->right = deleteTreeFromBST(tree->right, successor->key);
    return tree;
}

Tree findSuccessor(Tree tree)
{
    if (!tree)
        return NULL;
    if (tree->right)
        return findMinTreeInBST(tree->right);
    Tree successor = tree->parent;
    while (successor && tree->key > successor->key)
    {
        tree = successor;
        successor = successor->parent;
    }
    return successor;
}
Tree findPredecessor(Tree tree)
{
    if (!tree)
        return NULL;
    if (tree->left)
        return findMaxTreeInBST(tree->left);
    Tree predecessor = tree->parent;
    while (predecessor && tree->key < predecessor->key)
    {
        tree = predecessor;
        predecessor = predecessor->parent;
    }
    return predecessor;
}

int isIdentical(Tree t1, Tree t2)
{
    if (!t1 && !t2)
        return 1;
    if ((!t1 && t2) || (t1 && !t2))
        return 0;
    if (t1->key != t2->key)
        return 0;
    return isIdentical(t1->left, t2->left) && isIdentical(t1->right, t2->right);
}
Tree clone(Tree tree)
{
    if (!tree)
        return NULL;
    Tree left = clone(tree->left);
    Tree right = clone(tree->right);
    Tree t = newTree(tree->key, left, tree, NULL);
    if (left)
        left->parent = t;
    if (right)
        right->parent = t;
    return t;
}

int search(int k, int arr[], int end)
{
    for(int i=0;i<end;i++){
        if(arr[i]==k)
            return i;
    }
    return -1;
}
/*
Tree treeHelper(Tree tree,Type in[], Type post[], int inStrt, int inEnd,int* pIndex)
{
	if (inStrt > inEnd)
		return NULL;

    tree=newTree(NULL,post[*pIndex],NULL,NULL);
	(*pIndex)--;

	if (inStrt < inEnd){
	int iIndex = search(tree->key,in, inEnd);
	tree->right = treeHelper(tree, in, post, iIndex + 1, inEnd, pIndex);
	tree->left	= treeHelper(tree, in, post, inStrt, iIndex - 1, pIndex);
    }
	return tree;
}
Tree buildTree(Tree tree, Type in[], Type post[], int n)
{
	int pIndex = n - 1;
	return treeHelper(tree, in, post, 0, n - 1, &pIndex);
}
*/

int main()
{
    // int keys[] = {144, 150, 148, 99, 163, 119, 167, 141, 136, 155};
    // int i, n, k;
    // printf("Enter the no. of elements you want to add in BST: ");
    // scanf("%d", &n);
    // Tree bst = NULL;
    // for (i = 0; i < n; i++)
    // {
    //     printf("Key Value: ");
    //     scanf("%d", &k);
    //     bst = insertIntoBST(bst, k, NULL);
    // }
    int postorder[] = {1, 2, 3,7,6,4,5};
    int inorder[] = {1,3,2,5,4,7,6};
    Tree bst=NULL;
    bst=buildTree(bst,inorder,postorder,7);
    printTree(bst);
    printf("\n");
    /*
    int status = 1, option;
    while (status)
    {
        printf("1)Write a function to insert a new node corresponding to a given key in a binary search tree using recursion.\n");
        printf("2)Write a function to insert a new node corresponding to a given key in a binary search tree without recursion.\n");
        printf("3)Write a function to find the node with the minimum key value in a given binary search tree.\n");
        printf("4)Write a function to find the node with the maximum key value in a given binary search tree.\n");
        printf("5)Write a function to find the node with a given key value in a given binary search tree.\n");
        printf("6)Write a function to delete a node corresponding to a given key from a binary search tree.\n");
        printf("7)Write a function to print the keys in a binary tree with in-order traversal.\n");
        printf("8)Write a function to print the keys in a binary tree with pre-order traversal.\n");
        printf("9)Write a function to print the keys in a binary tree with post-order traversal.\n");
        printf("10)Write a function to find the node with the minimum key value in a given binary tree.\n");
        printf("11)Write a function to find the node with the maximum key value in a given binary tree.\n");
        printf("12)Write a function to check whether a binary tree is a binary search tree.\n");
        printf("\nEnter 1 to 12\n");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
        {
            printf("To insert a new node: ");
            printf("Key Value: ");
            scanf("%d", &k);
            bst = insertIntoBST(bst, k, NULL);
            printTree(bst);
            printf("\n");
            break;
        }
        case 2:
        {
            printf("To insert a new node: ");
            printf("Key Value: ");
            scanf("%d", &k);
            bst = insertIntoBST(bst, k, NULL);
            printTree(bst);
            printf("\n");
            break;
        }
        case 3:
        {
            printf("To find the node with the minimum key value: ");
            Tree min = findMinTreeInBST(bst);
            printf("%d\n",min->key);
            break;
        }
        case 4:
        {
            printf("To find the node with the minimum key value: ");
            Tree max = findMaxTreeInBST(bst);
            printf("%d\n",max->key);
            break;
        }
        case 5:
        {
            printf("To find the node with a given key value: ");
            printf("Key Value: ");
            scanf("%d", &k);
            Tree keyTree = findTreeInBST(bst, k);
            printf("keyTree%d\n",keyTree->key);
            printInOrder(keyTree);
            break;
        }
        case 6:
        {
            printf("To delete a node corresponding to a given key: ");
            printf("Key Value: ");
            scanf("%d", &k);
            Tree bst = deleteTreeFromBST(bst, k);
            printTree(bst);
            printf("\n");
            break;
        }
        case 7:
        {
            printf("To print the keys in a binary tree with in-order traversal: ");
            printInOrder(bst);
            printf("\n");
            break;
        }
        case 8:
        {
            printf("To print the keys in a binary tree with pre-order traversal: ");
            printPreOrder(bst);
            printf("\n");
            break;
        }
        case 9:
        {
            printf("To print the keys in a binary tree with post-order traversal: ");
            printPostOrder(bst);
            printf("\n");
            break;
        }
        case 10:
        {
            printf("To find the node with the minimum key value: ");
            Tree node = minKey(bst);
            printTree(node);
            printf("%d\n",node->key);
            break;
        }
        case 11:
        {
            printf("To find the node with the maximum key value: ");
            Tree node = maxKey(bst);
            printTree(node);
            printf("\n",node->key);
            break;
        }
        case 12:
        {
            printf("To check whether a binary tree is a binary search tree: ");
            printf("\nBinary Tree is BINARY SEARCH TREE: %d", isBST(bst));
            printf("\n");
            break;
        }
        default:
            printf("Enter a valid case!");
            break;
        }
        printf("\nEnter 1 to continue 0 to EXIT.");
        scanf("%d", &status);
    }*/
    return 0;
}
