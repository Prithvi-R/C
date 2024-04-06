#include <stdio.h>
#include <stdlib.h>

#define V 8

typedef int Type;
typedef enum
{
    WHITE,
    GREY,
    BLACK
} Color;
typedef struct node_t *Node;
typedef struct graph_t *Graph;

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

void breadthSearch(Graph graph){
    
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
                printf("(%d->%d)\t",node->value, node->next[j]->value);
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
    addEdge(adj, 0, 1);
    addEdge(adj, 0, 3);
    addEdge(adj, 0, 8);
    addEdge(adj, 1, 7);
    addEdge(adj, 2, 5);
    addEdge(adj, 2, 3);
    addEdge(adj, 3, 4);
    addEdge(adj, 3, 4);
    addEdge(adj, 5, 6);
    printf("\nPrint using Matrix-Sized 2D-array:\n");
    printAdjMatrix(adj);
    printf("\nPrint using linked-Sized 2D-array:\n");
    Graph graph = createGraph(adj);
    printGraph(graph);

    return 0;
}
