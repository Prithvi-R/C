#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define INT_MAX 1000
typedef enum
{
    WHITE,
    GREY,
    BLACK
} Color;
typedef int Type;
typedef struct node_t *Node;
typedef struct graph_t *Graph;
typedef struct queue_t *Queue;

struct queue_t
{
    int front, rear;
    unsigned int capacity, size;
    Type *data;
};

Queue createQueue(int capacity)
{
    Queue queue = (Queue)calloc(1, sizeof(struct queue_t));
    queue->capacity = capacity;
    queue->size = 0;
    queue->front = 0;
    queue->rear = 0;
    queue->data = calloc(capacity, sizeof(Type));
    return queue;
}

int isFull(Queue queue)
{
    return (queue->capacity == queue->size);
}

int isEmpty(Queue queue)
{
    return (!queue->size);
}

int enqueue(Queue queue, Type data)
{
    if (queue->size == queue->capacity)
        return 0;
    queue->data[queue->rear] = data;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->size++;
    return 1;
}

int dequeue(Queue queue, Type *pdata)
{
    if (queue->size == 0)
        return 0;
    *pdata = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return 1;
}

struct graph_t
{
    Node point[10];
};

struct node_t
{
    Color color;
    int d;
    Node parent;
    Type value;
    Node next;
};

struct link
{
    Type source, destination;
};

Graph make_Graph(struct link edges[], int x)
{
    int i;
    Graph graph = (Graph)malloc(sizeof(struct graph_t));
    for (i = 0; i < 10; i++)
    {
        graph->point[i] = NULL;
    }

    for (i = 0; i < x; i++)
    {
        int source = edges[i].source;
        int destination = edges[i].destination;
        Node node = (Node)malloc(sizeof(struct node_t));
        node->value = destination;
        node->color = WHITE;
        node->d = INT_MAX;
        node->parent = NULL;
        node->next = graph->point[source];
        graph->point[source] = node;
    }
    return graph;
}

void displayGraph(Graph graph)
{
    int i;
    for (i = 0; i < 10; i++)
    {
        Node ptr = graph->point[i];
        printf("%d)\t", i);
        while (ptr)
        {
            printf("(%d -> %d) ", i, ptr->value);
            ptr = ptr->next;
        }
        printf("\n");
    }
}

int search(Graph graph, Type key)
{
    for (int i = 0; i < 10; i++)
    {
        Node ptr = graph->point[i];
        while (ptr)
        {
            if (ptr != NULL && key == ptr->value)
                return i;
            ptr = ptr->next;
        }
    }
    return -1;
}

int breadthSearch(Type key, Graph graph)
{
    Queue q = createQueue(100);
    int k=search(graph,key);
    if (k == -1)
    {
        printf("Key not found in the graph.\n");
        return -1;
    }
    Node ptr ;
    // ptr= graph->point[k];
    // ptr->d = 0;
    // ptr->color = GREY;
    // ptr->parent = NULL;
    int d = 0;

    enqueue(q, key);
    while (!isEmpty(q))
    {
        dequeue(q, &k);
        ptr = graph->point[k];
        if(k==key) 
            ptr->d=0;
        else
            ptr->d = d+1;


        if (!ptr)
            continue;

        Node u = ptr;
        while (u && u->color == WHITE)
        {
            d=ptr->d;
            u->color = GREY;
            u->d = d;
            u->parent = ptr;
            printf("(%d --> %d) ", k, u->value);
            if (u)
                enqueue(q, u->value);
            u = u->next;
        }
        ptr->color = BLACK;
    }
    return d;
}

int main()
{
    struct link edges[] = {
        {0, 1}, {0, 3}, {0,8},{1, 7},{7,2},{2,5},{3,2},{5,6},{3,4},{8,4},
        {1, 0}, {3,0}, {8,0},{7, 1},{2 ,7},{5,2},{2,3},{6,5},{4,3},{4,8}};
    int n = sizeof(edges) / sizeof(edges[0]);
    Graph graph = make_Graph(edges, n);
    displayGraph(graph);
    int strt;
    printf("Enter starting Node: ");
    scanf("%d",&strt);
    printf("---------------------------------------------\n");
    printf("\nTotal Steps: %d\n ", breadthSearch(strt, graph));
    return 0;
}