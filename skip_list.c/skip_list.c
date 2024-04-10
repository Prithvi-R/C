#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
//it would help in writing -inf nd +inf in printing function
#define POS_INF 1000000
#define NEG_INF -1000000

typedef struct skip_list *SkipList;
typedef struct skip_list_entry *SkipListEntry;
typedef int Type;

struct skip_list
{
    int level;
    SkipListEntry head, tail;
};
struct skip_list_entry
{
    Type value;
    int key;
    int height;
    SkipListEntry right, left, up, down;
    int offset;
};

SkipListEntry newEntry(int key, Type value)
{
    SkipListEntry node = (SkipListEntry)calloc(1, sizeof(struct skip_list_entry));
    node->value = value;
    node->key = key;
    node->right = NULL;
    node->left = NULL;
    node->up = NULL;
    node->down = NULL;
    node->height = 0;
    return node;
}

SkipList newLevel()
{
    SkipList new = (SkipList)calloc(1, sizeof(struct skip_list));
    new->level = 0;
    new->head = newEntry(NEG_INF, 0);
    new->tail = newEntry(POS_INF, 0);
    new->head->right = new->tail;
    new->tail->left = new->head;
    return new;
}

SkipListEntry searchSkipList(SkipList skip, int key)
{
    SkipListEntry node = skip->head;

    while (1)
    {
        // to find the key or just smaller node than key
        for (;node->right->key != POS_INF && node->right->key <= key; node = node->right)
            ;
        // to traverse down
        if (node->down)
            node = node->down;
        else // if it is lowest level-->exit
            break;
    }
    return node;
}

//random no. generator
int random(int min, int max) {
    return min + rand() % (max - min + 1);
}

int insert(SkipList skip, Type value, int key)
{
    // if key is already there we just update value
    SkipListEntry e, node;
    e = searchSkipList(skip, key);
    // if key exist
    if (e->key == key)
    {
        Type tem = e->value;
        e->value = value;
        return tem;
    }
    // key is not there we have to add it
    node = newEntry(key, value);
    // new node created
    node->right = e->right;
    node->left = e;
    e->right->left=node;
    e->right=node;

    /**************************************
    To Do:     adjust level of node
    **************************************/
   int level=0;
   //seed random no. from time to get diff random values everytime
   srand(time(NULL));
   while(random(1,10)>5){
        if (level >= skip->level) {
            //create new level
            SkipListEntry p1, p2;
            skip->level++;
            p1 = newEntry(NEG_INF, 0);
            p2 = newEntry(POS_INF, 0);
            p1->right = p2;
            p2->left  = p1;
            p1->down = skip->head;
            p2->down = skip->tail;
            skip->head->up = p1;
            skip->tail->up = p2;
            skip->head = p1;
            skip->tail = p2;
        }
        //going to head
        while(!e->up){
            e=e->left;
        }
        //reached head node
        e=e->up;
        //creating new node nd joining with inserted node
        SkipListEntry k=newEntry(key,0);
        k->left=e;
        k->right=e->right;
        k->down=node;
        e->right->left=k;
        e->right=k;
        //joining node with newly created node on another level
        node->up=k;
        node=k;
        //level increment
        level++;
   }
    return 0;
}

Type removeSkipList(SkipList skip, int key)
{
    SkipListEntry e = searchSkipList(skip, key);
    //if key is not there it would give just smaller key
    if (e->key != key){
        printf("%d key not found!\n",key);
        return 0;
    }
    // deleting the whole column
    while (e)
    {
        e->right->left = e->left;
        e->left->right = e->right;
        SkipListEntry up = e->up;
        free(e);
        e = up;
    }
}

// copied the printing skiplist function from teachers code
void printSkipListForDebug(SkipList skipList)
{
    SkipListEntry e1 = skipList->head;
    while (e1)
    {
        SkipListEntry e2 = e1;
        while (e2)
        {
            if (e2->key == POS_INF)
            {
                printf("+oo", e2->key, e2->value);
            }
            else if (e2->key == NEG_INF)
            {
                printf("-oo", e2->key, e2->value);
            }
            else
            {
                printf("(%d, %d, %d)", e2->key, e2->value, e2->offset);
            }
            e2 = e2->right;
            if (e2)
            {
                printf(" <-> ");
            }
        }
        printf("\n");
        e1 = e1->down;
    }
}

/** This function prints the skip list nicely. This is not exactly a part
    of skip list. */
#define MAXLEVEL 100
#define BUFFER_SIZE 10000
void printSkipList(SkipList skipList)
{
    char s[MAXLEVEL][BUFFER_SIZE];
    char lastRow[BUFFER_SIZE] = "";
    char buffer[BUFFER_SIZE];
    int length = strlen(lastRow);
    SkipListEntry e1 = skipList->head;
    while (e1->down)
    {
        e1 = e1->down;
    }
    while (e1)
    {
        length = strlen(lastRow);
        e1->offset = length + 2;
        if (e1->key == NEG_INF)
        {
            sprintf(buffer, "-oo");
        }
        else if (e1->key == POS_INF)
        {
            sprintf(buffer, " <-> +oo [LEVEL: %d]", 1);
        }
        else
        {
            sprintf(buffer, " <-> (%d, %d)", e1->key, e1->value);
        }
        strcat(lastRow, buffer);
        e1 = e1->right;
    }
    int level = skipList->level + 1;
    for (e1 = skipList->head; e1->down; e1 = e1->down)
    {
        for (SkipListEntry e2 = e1; e2; e2 = e2->right)
        {
            if (e2->key == NEG_INF)
            {
                length = printf("-oo");
                continue;
            }
            SkipListEntry e3;
            for (e3 = e2; e3->down; e3 = e3->down)
                ;
            int offset = e3->offset;
            length += printf(" <");
            while (length <= offset)
            {
                length += printf("-");
            }
            if (e2->key == POS_INF)
            {
                printf("> +oo [LEVEL: %d]\n", level);
            }
            else
            {
                length += printf("> (%d, %d)", e2->key, e2->value);
            }
        }
        level--;
    }
    printf("%s\n", lastRow);
}


void help()
{
    printf("INSERT(KEY,VALUE)   Inserts the integer value VALUE in the skip list with the\n"
           "                    key KEY. If KEY is already present in the list, it modifies\n"
           "                    corresponding value to VALUE.\n"
           "DELETE KEY          Deletes the key KEY from the skip list.\n"
           "SEARCH KEY          Searches for the key KEY in the skip list.\n"
           "PRINT               Prints the skip list.\n"
           "HELP                Shows this help.\n"
           "EXIT                Exits the program.\n");
}
//comparing two strings (toupper is used to uppercase even alphanumeric character)
int compareIgnoreCase(char *pa, char *pb)
{
    for (;; pa++, pb++)
    {
        int difference = toupper((unsigned char)*pa) - toupper((unsigned char)*pb);
        if (difference != 0 || !*pa)
        {
            return difference;
        }
    }
}

int main()
{
    help();
    fflush(stdout);
    SkipList skip = newLevel();
    char input[10];
    while (1)
    {
        printf("Choice: ");
        scanf("%s", input);
        if (!compareIgnoreCase(input, "insert"))
        {
            int key;
            Type value;
            scanf("%d %d", &key, &value);
            insert(skip, value, key);
            printf("Modified Skip list:\n");
            printSkipList(skip);
        }
        else if (!compareIgnoreCase(input, "delete"))
        {
            int key = 0;
            scanf("%d", &key);
            printf("Deleting the key %d from skip list...\n", key);
            removeSkipList(skip, key);
            printf("Modified Skip list:\n");
            printSkipList(skip);
        }
        else if (!compareIgnoreCase(input, "search"))
        {
            int key;
            scanf("%d", key);
            printf("The %d key has the value: %d\n", key, searchSkipList(skip, key)->value);
        }
        else if (!compareIgnoreCase(input, "help"))
        {
            help();
        }
        else if (!compareIgnoreCase(input, "exit"))
            break;
    }

    return 0;
}