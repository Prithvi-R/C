#include <stdio.h>
#include <stdlib.h>

#define V 6 //Define the maximum number of vertices in the graph

struct graph //declaring graph data structure
{
    struct Node *point[V]; //An array of pointers to Node to represent an adjacency list
};

struct Node //declaring node
{
    int destination;
    struct Node *next;
};

struct link // declaring edge
{
    int source, destination;
};

struct graph *make_Graph(struct link edges[], int x) // function to create graph
{
    int i;
    struct graph *graph = (struct graph *)malloc(sizeof(struct graph)); // defining graph
    for (i = 0; i < V; i++)
    {
        graph->point[i] = NULL;
    }

    for (i = 0; i < x; i++)

    {
        int source = edges[i].source;
        int destination = edges[i].destination;
        struct Node *Node1 = (struct Node *)malloc(sizeof(struct Node));
        Node1->destination = destination;
        Node1->next = graph->point[source];
        graph->point[source] = Node1;
    }
    return graph;
}

void displayGraph(struct graph *graph) // function to view garph
{
    int i;
    for (i = 0; i < V; i++)
    {
        struct Node *ptr = graph->point[i];
        printf("%d)\t",i);
        while (ptr)
        {
            printf("(%d -> %d) ", i, ptr->destination);
            ptr = ptr->next;
        }
        printf("\n");
    }
}

int main()
{
    struct link edges[] =
            {
            {0, 1}, {2,3},{1, 3}, {3, 0}, {3, 4}, {4, 5}, {5, 6}

        };

    int n = sizeof(edges) / sizeof(edges[0]);
    struct graph *graph = make_Graph(edges, n);
    displayGraph(graph);
    return 0;
}