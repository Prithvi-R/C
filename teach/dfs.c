#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef enum { WHITE, GRAY, BLACK } Color;

typedef struct Vertex_t *Vertex;
struct Vertex_t {
    Color color;
    int pi;
    int d;
    int f;
};

Vertex newVertex() {
    Vertex v = (Vertex)calloc(1, sizeof(struct Vertex_t));
    v->color = WHITE;
    v->pi = INT_MAX;
    v->d = INT_MAX;
    v->f = INT_MAX;
    return v;
}

typedef struct Graph_t *Graph;
struct Graph_t {
    int numVertices;
    Vertex *vertices;
    int **adj;
};

Graph newGraph(int numVertices) {
    Graph g = (Graph)calloc(1, sizeof(struct Graph_t));
    g->numVertices = numVertices;
    g->vertices = (Vertex *)calloc(numVertices, sizeof(Vertex));
    g->adj = (int **)calloc(numVertices, sizeof(int *));

    for (int i = 0; i < numVertices; i++) {
        g->vertices[i] = newVertex();
        g->adj[i] = (int *)calloc(numVertices, sizeof(int));
        for (int j = 0; j < numVertices; j++) {
            g->adj[i][j] = 0;
        }
    }
    return g;
}

void deleteGraph(Graph g) {
    for (int i = 0; i < g->numVertices; i++) {
        free(g->adj[i]);
        free(g->vertices[i]);
    }
    free(g->adj);
    free(g->vertices);
    free(g);
}

void addEdge(Graph g, int u, int v) {
    g->adj[u][v] = 1;
}



int depthFirstSearchVisit(Graph g, int u, int time) {
    time++;
    g->vertices[u]->d = time;
    g->vertices[u]->color = GRAY;

    for (int v = 0; v < g->numVertices; v++) {
        if (g->adj[u][v] && g->vertices[v]->color == WHITE) {
            g->vertices[v]->pi = u;
            time = depthFirstSearchVisit(g, v, time);
        }
    }
    
    g->vertices[u]->color = BLACK;
    time++;
    g->vertices[u]->f = time;
    printf(
        "u = %d\t u.d = %d\t u.f = %d\t u.pi = %d\n",
        u, g->vertices[u]->d, g->vertices[u]->f,
        g->vertices[u]->pi != INT_MAX ? g->vertices[u]->pi : -1
    );

    return time;
}

void depthFirstSearch(Graph g) {
    for (int u = 0; u < g->numVertices; u++) {
        g->vertices[u]->color = WHITE;
        g->vertices[u]->pi = INT_MAX;
    }

    int time = 0;
    for (int u = 0; u < g->numVertices; u++)
        if (g->vertices[u]->color == WHITE)
            time = depthFirstSearchVisit(g, u, time);
}

void findPath(Graph g, int s, int v, char *path, int *index) {
    if (s == v) {
        sprintf(path, "%d", s);
    } else if (g->vertices[v]->pi == INT_MAX) {
        sprintf(path, "There is no path from %d to %d.", s, v);
    } else {
        findPath(g, s, g->vertices[v]->pi, path, index);
        sprintf(path + strlen(path), " -> %d", v);
    }
}

int main() {
    int n = 6;
    int s = 0; // node index starts with 0
    int v = 3;
    int adjacencyMatrix[6][6] = {
        {0, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 1, 1},
        {0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 1}
    };

    Graph g = newGraph(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adjacencyMatrix[i][j]) {
                addEdge(g, i, j);
            }
        }
    }

    depthFirstSearch(g);

    char path[100];
    int index = 0;
    findPath(g, s, v, path, &index);
    printf("%s\n", path);

    deleteGraph(g);

    return 0;
}