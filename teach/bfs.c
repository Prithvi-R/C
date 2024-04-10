#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef enum { WHITE, GRAY, BLACK } Color;


/* Queue implementation starts here. */
typedef struct Queue_t *Queue;
struct Queue_t {
    int size;
    int *array;
    int front;
    int rear;
};

Queue newQueue(int capacity) {
	Queue q = (Queue) calloc(1, sizeof (struct Queue_t));
	q->size = capacity;
    q->array = (int *) calloc(capacity, sizeof(int));
    q->front = 0;
    q->rear = 0;
	return q;
}

void enqueue(Queue q, int value) {
    q->array[q->rear] = value;
    q->rear = (q->rear + 1) % q->size;
}

int dequeue(Queue q) {
    int value = q->array[q->front];
    q->front = (q->front + 1) % q->size;
    return value;
}

bool isEmpty(Queue q) {
    return q->front == q->rear;
}

void deleteQueue(Queue q) {
	free(q->array);
	free(q);
}
/* Queue implementation ends here. */


/* Vertex implementation starts here. */
typedef struct Vertex_t *Vertex;
struct Vertex_t {
    Color color;
    int pi;
    int d;
};

Vertex newVertex() {
	Vertex v = (Vertex) calloc(1, sizeof (struct Vertex_t));
	v->color = WHITE;
    v->pi = INT_MAX;
    v->d = INT_MAX;
	return v;
}
/* Vertex Implementation ends here. */


/* Graph implementation starts here. */
typedef struct Graph_t *Graph;
struct Graph_t {
    int numVertices;
    Vertex *vertices;
    int **adj;
};

Graph newGraph(int numVertices) {
    Graph g = (Graph) calloc(1, sizeof(struct Graph_t));
    g->numVertices = numVertices;
    g->vertices = (Vertex *) calloc(numVertices, sizeof(Vertex));
    g->adj = (int **) calloc(numVertices, sizeof(int *));

    for (int i = 0; i < numVertices; i++) {
        g->vertices[i] = newVertex();
        g->adj[i] = (int *) calloc(numVertices, sizeof(int));
        for (int j = 0; j < numVertices; j++) {
            g->adj[i][j] = 0;
        }
    }
	return g;
}

void deleteGraph(Graph g) {
	for (int i = 0; i < g->numVertices; i++) {
        free(g->adj[i]);
    }
    free(g->adj);
    free(g->vertices);
    free(g);
}


void addEdge(Graph g, int u, int v) {
    g->adj[u][v] = 1;
}
/* Graph implementaion ends here. */


void breadthFirstSearch(Graph g, int s) {
    for (int i = 0; i < g->numVertices; i++) {
        g->vertices[i]->color = WHITE;
        g->vertices[i]->pi = INT_MAX;
        g->vertices[i]->d = INT_MAX;
    }

    g->vertices[s]->color = GRAY;
    g->vertices[s]->d = 0;

    Queue q = newQueue(g->numVertices);
    
    enqueue(q, s);

    while (!isEmpty(q)) {
        int u = dequeue(q);

        for (int v = 0; v < g->numVertices; v++) {
            if (g->adj[u][v] && g->vertices[v]->color == WHITE) {
                g->vertices[v]->color = GRAY;
                g->vertices[v]->d = g->vertices[u]->d + 1;
                g->vertices[v]->pi = u;
                enqueue(q, v);
            }
        }

        g->vertices[u]->color = BLACK;
        printf(
			"u = %d\t u.d = %d\t u.pi = %d\n",
			u, g->vertices[u]->d,
			g->vertices[u]->pi != INT_MAX ? g->vertices[u]->pi : -1
		);
    }

    deleteQueue(q);
}

void findPath(Graph g, int s, int v, char *path) {
    if (s == v) {
        sprintf(path, "%d", s);
    } else if (g->vertices[v]->pi == INT_MAX) {
        sprintf(path, "There is no path from %d to %d.", s, v);
    } else {
        findPath(g, s, g->vertices[v]->pi, path);
        sprintf(path + strlen(path), " -> %d", v);
    }
}

int main() {
    int n = 8;
    int s = 1; // node index starts with 0
    int v = 7;
    int adjacencyMatrix[8][8] = {
        {0, 1, 0, 0, 1, 0, 0, 0},
        {1, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0, 1, 1, 0},
        {0, 0, 1, 0, 0, 0, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0, 0, 1, 0},
        {0, 0, 1, 1, 0, 1, 0, 1},
        {0, 0, 0, 1, 0, 0, 1, 0}
    };

    Graph g = newGraph(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adjacencyMatrix[i][j]) {
                addEdge(g, i, j);
            }
        }
    }

    breadthFirstSearch(g, s);

    char path[100];
    findPath(g, s, v, path);
    printf("%s\n", path);

    deleteGraph(g);

    return 0;
}