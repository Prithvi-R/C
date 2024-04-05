#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define INT_MAX 1000;
typedef enum{WHITE,GREY,BLACK} Color;
typedef int Type;
typedef struct node_t *Node;
typedef struct graph_t *Graph;
typedef struct queue_t *Queue;

struct queue_t {
    int *array;
    unsigned int capacity;
    int front, rear;
};

Queue newQueue(unsigned int capacity){
    Queue queue = (Queue) calloc (1, sizeof(struct queue_t));
    assert(queue);
    queue->array = (Type*) calloc (capacity, sizeof(Type));
    assert(queue->array);
    queue->capacity = capacity;
    queue->front = queue->rear = -1;
}

int isEmpty(Queue queue){
    return queue->front == -1 && queue->rear == -1;
}

int isFull(Queue queue){
    return queue->rear - queue->front == queue->capacity - 1;
}

int enqueue(Queue queue, Type data){
    if(isFull(queue)) return 0;
    if(isEmpty(queue)){
        queue->front = queue->rear = 0;
        queue->array[queue->front] = data;
    }
    else{
        ++queue->rear;
        queue->array[queue->rear%queue->capacity] = data;
    }
    return 1;
}

int dequeue(Queue queue, Type *data){
    if(isEmpty(queue)) return 0;
    *data = queue->array[queue->front];
    queue->array[(queue->front++)%queue->capacity] = 0;
    if(queue->front > queue->rear)
        queue->front = queue->rear = -1;
    return 1;
}

int peek(Queue queue, Type *data){
    if(isEmpty(queue)) return 0;
    *data = queue->array[queue->front%queue->capacity];
    return 1;
}

struct graph_t //declaring graph data structure
{
    Node point[10]; //An array of pointers to Node to represent an adjacency list
};
struct node_t{
    Color color;
    int d;
    Node parent;
    Type value;
    Node next;
};
struct link{
    Type source,destination;
};

// Node newNode(Node node,Type key,Node parent){
//     node=(Node)calloc(1,sizeof(struct node_t));
//     node->color=WHITE;
//     node->d=INT_MAX;
//     node->parent=NULL;
//     return node;
// }
// Node createNode(Node node,Type key,Node parent){
//     if(!node)
//         return newNode(node,key,NULL);
// }
Graph make_Graph(struct link edges[], int x) // function to create graph
{
    int i;
    Graph graph = (Graph )malloc(sizeof(struct graph_t)); // defining graph
    for (i = 0; i < 10; i++)
    {
        graph->point[i] = NULL;
    }

    for (i = 0; i < x; i++)

    {
        int source = edges[i].source;
        int destination = edges[i].destination;
        Node node = (Node)calloc(1,sizeof(struct node_t));
        node->value = destination;
        node->color=WHITE;
        node->d=INT_MAX;
        node->parent=NULL;
        node->next = graph->point[source];
        graph->point[source] = node;
    }
    return graph;
}

void displayGraph(Graph graph)// function to view garph
{
    int i;
    for (i = 0; i < 10; i++)
    {
        Node ptr = graph->point[i];
        printf("%d)\t",i);
        while (ptr)
        {
            printf("(%d -> %d) ", i, ptr->value);
            ptr = ptr->next;
        }
        printf("\n");
    }
}
int search(Graph graph,Type key){
    for(int i=0;i<10;i++){
        if(key==graph->point[i]->value)
            return i;
    }
    return -1;
}
int breadthSearch(Type key,Graph graph){
    Queue q=newQueue(100);
    int k=search(graph,key);
    Node ptr=graph->point[k];
    ptr->d=0;
    ptr->color=GREY;
    ptr->parent=NULL;
    int d;
    for(int i=0;i<10;i++){
        d=ptr->d;
        Node u=ptr;
        while (ptr->next && ptr->next->color==WHITE)
        {
            enqueue(q,ptr->value);
            ptr=ptr->next;
            ptr->color=GREY;
            ptr->d=d+1;
            ptr->parent=u;
            printf("(%d -> %d) ", graph->point[k]->value, ptr->value);
        }
        enqueue(q,ptr->value);
        dequeue(q,k);
        
        graph->point[k]->color=BLACK;
        peek(q,k);
        ptr=graph->point[k];
    }
    return d;
}

int main()
{
    struct link edges[] =
        {
            {0, 1}, {2,3},{1, 3}, {3, 0}, {3, 4}, {4, 5}, {5, 6},{8,8}

        };

    int n = sizeof(edges) / sizeof(edges[0]);
    Graph graph = make_Graph(edges, n);
    displayGraph(graph);
    printf("[(%d)]\n ", breadthSearch(3,graph));
    return 0;
}