#include <stdio.h>
#include <stdlib.h>

typedef struct tree_t *Tree;
typedef char Type;

struct tree_t
{
    Tree parent;
    Type key;
    Tree left, right;
};

Tree newTree(Tree parent, Type key, Tree left, Tree right)
{
    Tree tree = (Tree)calloc(1, sizeof(struct tree_t));
    tree->parent = parent;
    tree->key = key;
    tree->left = left;
    tree->right = right;
    return tree;
}

int max(int a, int b)
{
    return a > b ? a : b;
}
int min(int a, int b)
{
    return a < b ? a : b;
}
Tree insertIntoBT(Tree tree, int key, Tree parent,int a)
{
    if (!tree){
        a=1000;
        return newTree(parent, key, NULL, NULL);
        }
    if(a==1000){
        printf("In which node u want to enter:(0-Left||1-Right)");
        scanf("%d",&a);
    }
    if (!a){
        a=1000;
        tree->left = insertIntoBT(tree->left, key, tree,NULL);
    }
    else{
        a=1000;
        tree->right = insertIntoBT(tree->right, key, tree,NULL);
    }
    return tree;
}

void printInOrder(Tree tree)
{
    if (!tree)
        return;
    printInOrder(tree->left);
    printf("%c ", tree->key);
    printInOrder(tree->right);
}

void printPreOrder(Tree tree)
{
    if (!tree)
        return;
    printf("%c ", tree->key);
    printPreOrder(tree->left);
    printPreOrder(tree->right);
}

void printPostOrder(Tree tree)
{
    if (!tree)
        return;
    printPostOrder(tree->left);
    printPostOrder(tree->right);
    printf("%c ", tree->key);
}

void printZigZag(Tree tree, int n)
{
    if (!tree)
        return;
    int i, j;
    for (i = 1, j = 0; i <= n; j++, i++)
    {
        printLevel(tree, i, j);
        printf("\n");
    }
}
void printLevel(Tree tree, int level, int j)
{
    if (!tree)
        return;
    if (level == 1)
        printf("%d ", tree->key);
    else if (level > 1)
    {
        if (j % 2)
        {
            printLevel(tree->right, level - 1, j);
            printLevel(tree->left, level - 1, j);
        }
        else
        {
            printLevel(tree->left, level - 1, j);
            printLevel(tree->right, level - 1, j);
        }
    }
}
void printLevelOrder(Tree tree)
{
    int h = height(tree);
    int i;
    for (i = 1; i <= h; i++)
    {
        printCurrentLevel(tree, i);
        printf("\n");
    }
}
void printCurrentLevel(Tree tree, int level)
{
    if (!tree)
        return;
    if (level == 1)
        printf("%d ", tree->key);
    else if (level > 1)
    {
        printCurrentLevel(tree->left, level - 1);
        printCurrentLevel(tree->right, level - 1);
    }
}

Tree findMinNode(Tree tree)
{
    if (tree == NULL)
        return NULL;
    Tree minLeft = findMinNode(tree->left);
    Tree minRight = findMinNode(tree->right);
    Tree min = tree;
    if (minLeft != NULL && minLeft->key < min->key)
        min = minLeft;
    if (minRight != NULL && minRight->key < min->key)
        min = minRight;
    return min;
}

Tree findMaxNode(Tree tree)
{
    if (tree == NULL)
        return NULL;
    Tree maxLeft = findMaxNode(tree->left);
    Tree maxRight = findMaxNode(tree->right);
    Tree max = tree;
    if (maxLeft != NULL && maxLeft->key > max->key)
        max = maxLeft;
    if (maxRight != NULL && maxRight->key > max->key)
        max = maxRight;
    return max;
}

Tree findNode(Tree tree, Type key)
{
    if (tree == NULL)
        return NULL;
    if (tree->key == key)
        return tree;
    Tree foundLeft = NULL, foundRight = NULL;
    if (tree->left)
        foundLeft = findNode(tree->left, key);
    if (tree->right)
        foundRight = findNode(tree->right, key);
    if (foundLeft != NULL)
        return foundLeft;
    return foundRight;
}

int height(Tree tree)
{
    if (!tree)
        return 0;
    int heightLeft = height(tree->left);
    int heightRight = height(tree->right);
    return max(heightLeft, heightRight) + 1;
}

int depth(Tree tree)
{
    int depth = 0;
    for (; tree->parent; tree = tree->parent)
        depth++;
    return depth;
}

Tree mirror(Tree tree)
{
    if (!tree)
        return NULL;
    Tree right = mirror(tree->left);
    Tree left = mirror(tree->right);
    Tree t = newTree(tree->key, left, tree, NULL);
    if (left)
        left->parent = t;
    if (right)
        right->parent = t;
    return t;
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

Tree deleteBinaryTree(Tree tree)
{
    if (!tree)
        return NULL;
    if (tree->left)
        tree->left = deleteBinaryTree(tree->left);
    if (tree->right)
        tree->right = deleteBinaryTree(tree->right);
    tree->parent = NULL;
    free(tree);
    return NULL;
}

Tree findMinTreeInBT(Tree tree)
{
    for (; tree->left; tree = tree->left)
        ;
    return tree;
}

Tree findMaxTreeInBT(Tree tree)
{
    for (; tree->right; tree = tree->right)
        ;
    return tree;
}

Tree findPredecessor(Tree tree)
{
    if (!tree)
        return NULL;
    if (tree->left)
        return findMaxTreeInBT(tree->left);
    Tree predecessor = tree->parent;
    while (predecessor && tree->key < predecessor->key)
    {
        tree = predecessor;
        predecessor = predecessor->parent;
    }
    return predecessor;
}

Tree findSuccessor(Tree tree)
{
    if (!tree)
        return NULL;
    if (tree->right)
        return findMinTreeInBT(tree->right);
    Tree successor = tree->parent;
    while (successor && tree->key > successor->key)
    {
        tree = successor;
        successor = successor->parent;
    }
    return successor;
}

void countLeafNodes(Tree tree, int *cnt)
{
    if (tree->left)
        countLeafNodes(tree->left, cnt);
    if (tree->right)
        countLeafNodes(tree->right, cnt);
    if (!tree->left && !tree->right)
        (*cnt) += 1;
    return;
}

void countNonLeafNodes(Tree tree, int *cnt)
{
    if (tree->left)
        countNonLeafNodes(tree->left, cnt);
    if (tree->right)
        countNonLeafNodes(tree->right, cnt);
    if (tree->left || tree->right)
        (*cnt) += 1;
    return;
}

void printLeafInOrder(Tree tree)
{
    if (!tree)
        return;
    printLeafInOrder(tree->left);
    if (!tree->left && !tree->right)
        printf("%d ", tree->key);
    printLeafInOrder(tree->right);
}

void printNonLeafInOrder(Tree tree)
{
    if (!tree)
        return;
    printNonLeafInOrder(tree->left);
    if (tree->left || tree->right)
        printf("%d ", tree->key);
    printNonLeafInOrder(tree->right);
}

void printTree(Tree tree)
{
    if(!tree)   printf("NULL\n");
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

int search(Type k, Type arr[], int end)
{
    for(int i=0;i<end;i++){
        if(arr[i]==k)
            return i;
    }
    return -1;
}
Tree treeHelp(Tree tree,Type in[], Type pre[], int instrt,int end)
{   
    static int preIndex = 0;
    if(instrt>end)        return NULL;
    tree=newTree(NULL,pre[preIndex++],NULL,NULL);
    if(instrt<end){
        int inIndex = search(tree->key,in, end);
	    tree->left = treeHelp(tree,in, pre, instrt, inIndex - 1);
	    tree->right = treeHelp(tree,in, pre, inIndex + 1, end);
    }
    return tree;
}


Tree treeHelper(Tree tree,Type in[], Type post[], int inStrt, int inEnd,int* pIndex)
{
	if (inStrt > inEnd)
		return NULL;

	/* Pick current tree from Postorder traversal using
	postIndex and decrement postIndex */
    tree=newTree(NULL,post[*pIndex],NULL,NULL);
	(*pIndex)--;

	if (inStrt < inEnd){
	int iIndex = search(tree->key,in, inEnd);
	tree->right = treeHelper(tree, in, post, iIndex + 1, inEnd, pIndex);
	tree->left	= treeHelper(tree, in, post, inStrt, iIndex - 1, pIndex);
    }
	return tree;
}

// This function mainly initializes index of root
// and calls treeHelper()
Tree buildTree(Tree tree, Type in[], Type post[], int n)
{
	int pIndex = n - 1;
	return treeHelper(tree, in, post, 0, n - 1, &pIndex);
}

int main()
{
    // int i, n, k,a;
    // printf("Enter the no. of elements you want to add in BT: ");
    // scanf("%d", &n);
    // Tree tree = NULL, out = NULL;
    // for (i = 0; i < n; i++)
    // {
    //     printf("Key Value: ");
    //     scanf("%d", &k);
    //    
    //     printf("In which node u want to enter:(0-Left||else-Right)");
    //     scanf("%d",&a);
    //     tree = insertIntoBT(tree, k, NULL,a);
    // }
    // while (height(tree) < 5)
    // {
    //     printf("The level is less than req minimum level:\n");
    //     printf("Key Value: ");
    //     scanf("%d", &k);
    //     tree = insertIntoBT(tree, k, NULL);
    // }

    // printTree(tree);
    // printf("Height is: %d\n", height(tree));
    // printf("-----------------Level-Order-------------------\n");
    // printLevelOrder(tree);
    // printf("-------------------Zig-Zag---------------------\n");
    // printZigZag(tree,height(tree));
    // int pp=0;
    // printf("if zig-zag enter 0\n");
    // scanf("%d",&pp);
    // if(!pp)  printZigZag(tree,height(tree));
    // else printLevelOrder(tree);

    Type pre[] = {'5', '3', '1','2','4','7','6'};
    Type post[] = {'1', '2', '3','7','6','4','5'};
    Type in[] = {'1','3','2','5','7','4','6'};
    Tree bst=NULL,bt=NULL;
    bt=treeHelp(bst,in,pre,0,6);
    bst=buildTree(bst,in,post,7);
    printTree(bst);
    printf("\n");
    printTree(bt);
    printf("\n");
    return 0;
}