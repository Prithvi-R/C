#include <stdio.h>
#include <stdlib.h>

#define V 9

typedef int Type;
typedef enum {WHITE, GREY, BLACK} Color;
typedef struct node_t *Node;
typedef struct graph_t *Graph;
typedef struct queue_t *Queue;
typedef struct truct_t *Stack;
struct truct_t
{
    int front, rear;
    unsigned int capacity, size;
    Type *data;
};

Stack createStack()
{
    Stack stack=(Stack)calloc(1,sizeof(struct truct_t));
    int capacity=V;
    stack->capacity = capacity;
    stack->size = 0;
    stack->front = 0;
    stack->rear = stack->front - 1;
    stack->data = calloc(capacity, sizeof(Type));
    return stack;
}

int isFullS(Stack stack)
{
    return (stack->capacity == stack->size);
}
int isEmptyS(Stack stack)
{
    return (!stack->size);
}

int push(Stack stack, Type data)
{
    int capacity=V;
    if (stack->size == stack->capacity)
        return 0;
    stack->front++;
    stack->rear++;
    stack->data[stack->size] = data;
    stack->size++;
    return 1;
}
int pull(Stack stack, Type *pdata)
{
    if (stack->size == 0)
        return 0;
    stack->size--;
    stack->front--;
    stack->rear--;
    *pdata = stack->data[stack->size];
    return 1;
}

int peekStack(Stack stack, Type *pdata)
{
    if (stack->size == 0)
        return 0;
    *pdata = stack->data[stack->size - 1];
    return 1;
}

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

int isFullQ(Queue queue)
{
    return (queue->capacity == queue->size);
}

int isEmptyQ(Queue queue)
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
int peek(Queue queue, Type *pdata)
{
    if (queue->size == 0)
        return 0;
    *pdata = queue->data[queue->front];
    return 1;
}

struct graph_t
{
    Node point[V];
};

struct node_t
{
    Color color;
    int d;
    Node parent;
    Type value;
    Node next[V];
};

Graph createGraph(Type adj[][V])
{
    Graph graph = (Graph)calloc(1, sizeof(struct graph_t));
    for (int i = 0; i < V; i++)
    {
        Node node = (Node)calloc(1, sizeof(struct node_t));
        node->color = WHITE;
        node->parent = NULL;
        node->value = i;
        node->d = -1;
        graph->point[i] = node;
    }
    for (int i = 0; i < V; i++)
    {
        Node node = graph->point[i];
        for (int j = 0; j < V; j++)
        {
            if (adj[i][j])
                node->next[j] = graph->point[j];
            else
                node->next[j] = NULL;
        }
    }
    return graph;
}

int search(Graph graph, Type key)
{
    for (int i = 0; i < V; i++)
    {
        Node ptr = graph->point[i];
        if (key == ptr->value)
            return i;
    }
    return -1;
}

int breadthSearch(Graph graph, Type key,Type value)
{
    Queue q = createQueue(V);
    int k = search(graph, key);
    Node ptr = graph->point[k];
    ptr->d = 0;
    ptr->parent = NULL;
    enqueue(q, ptr->value);
    ptr->color = GREY;
    while (!isEmptyQ(q))
    {
        peek(q, &k);
        k = search(graph, k);
        ptr = graph->point[k];
        Node u = ptr;
        
        for (int i = 0; i < V; i++)
        {
            if (u->next[i])
            {
                ptr = u->next[i];
                if (ptr->color == WHITE)
                {
                    enqueue(q, ptr->value);
                    ptr->color = GREY;
                    ptr->d = u->d + 1;
                    ptr->parent = u;
                    printf("(%d-->%d)%d  ", u->value, ptr->value, ptr->d);
                    if(value==ptr->value)
                        return ptr->d;
                }
            }
        }
        dequeue(q, &k);
        k = search(graph, k);
        graph->point[k]->color = BLACK;
    }
    free(q);
    if(value==graph->point[k]->value)
        return graph->point[k]->d;
    return -1;
}

int depthSearch(Graph graph, Type key,Type value)
{
    Stack s = createStack();
    int k = search(graph, key);
    Node ptr = graph->point[k];
    ptr->d = 0;
    ptr->parent = NULL;
    push(s, ptr->value);
    ptr->color = GREY;
    while (!isEmptyS(s))
    {
        peekStack(s, &k);
        k = search(graph, k);
        ptr = graph->point[k];
        Node u = ptr;
        
        for (int i = 0; i < V; i++)
        {
            if (u->next[i])
            {
                ptr = u->next[i];
                if (ptr->color == WHITE)
                {
                    push(s, ptr->value);
                    ptr->color = GREY;
                    ptr->d = u->d + 1;
                    ptr->parent = u;
                    printf("(%d-->%d)%d  ", u->value, ptr->value, ptr->d);
                    if(value==ptr->value)
                        return ptr->d;
                }
            }
        }
        pull(s, &k);
        k = search(graph, k);
        graph->point[k]->color = BLACK;
    }
    free(s);
    if(value==graph->point[k]->value)
        return graph->point[k]->d;
    return -1;
}

void printGraph(Graph graph)
{
    for (int i = 0; i < V; i++)
    {
        Node node = graph->point[i];
        printf("%d->\t", node->value);
        for (int j = 0; j < V; j++)
        {
            if (node->next[j])
                printf("(%d->%d)\t", node->value, node->next[j]->value);
        }
        printf("\n");
    }
}

void addEdge(Type arr[][V], int i, int j)
{
    arr[i][j] = 1;
    arr[j][i] = 1;
}

void printAdjMatrix(Type arr[][V])
{
    int i, j;

    for (i = 0; i < V; i++)
    {
        for (j = 0; j < V; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    
    Type adj[V][V] = {0};
    // Type source,destination;
    // int n,i;
    // printf("Enter number of edge you want to add: ");
    // scanf("%d",&n);

    // for(i=0;i<n;i++){
    //     printf("Enter the edge {source destination}; ");
    //     scanf("%d %d",&source,&destination);
    //     addEdge(adj,source,destination);
    // }
    addEdge(adj, 0, 1);
    addEdge(adj, 0, 3);
    addEdge(adj, 0, 8);
    addEdge(adj, 4, 8);
    addEdge(adj, 1, 7);
    addEdge(adj, 2, 5);
    addEdge(adj, 2, 3);
    addEdge(adj, 3, 4);
    addEdge(adj, 2, 7);
    addEdge(adj, 5, 6);
    Graph graph = createGraph(adj);
    
    // printf("\nPrint using Matrix-Sized 2D-array:\n");
    // printAdjMatrix(adj);
    // printf("\nPrint using linked-Sized 2D-array:\n");
    printGraph(graph);

    int ke,va;
    printf("Enter the value: ");
    scanf("%d", &ke);
    printf("Enter the end value: ");
    scanf("%d", &va);  
    printf("\nTotal Steps: %d",depthSearch(graph, ke,va));
    return 0;
}
