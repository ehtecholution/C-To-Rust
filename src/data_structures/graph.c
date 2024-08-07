#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX_VERTICES 100

struct Graph {
    bool adjacency_matrix[MAX_VERTICES][MAX_VERTICES];
    int num_vertices;
};

Graph* graph_create(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->num_vertices = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adjacency_matrix[i][j] = false;
        }
    }
    return graph;
}

void graph_destroy(Graph* graph) {
    free(graph);
}

void graph_add_edge(Graph* graph, int src, int dest) {
    if (src >= 0 && src < graph->num_vertices && dest >= 0 && dest < graph->num_vertices) {
        graph->adjacency_matrix[src][dest] = true;
        graph->adjacency_matrix[dest][src] = true;
    }
}

void graph_remove_edge(Graph* graph, int src, int dest) {
    if (src >= 0 && src < graph->num_vertices && dest >= 0 && dest < graph->num_vertices) {
        graph->adjacency_matrix[src][dest] = false;
        graph->adjacency_matrix[dest][src] = false;
    }
}

bool graph_has_edge(Graph* graph, int src, int dest) {
    if (src >= 0 && src < graph->num_vertices && dest >= 0 && dest < graph->num_vertices) {
        return graph->adjacency_matrix[src][dest];
    }
    return false;
}

static void dfs_recursive(Graph* graph, int v, bool visited[], void (*visit)(int)) {
    visited[v] = true;
    visit(v);

    for (int i = 0; i < graph->num_vertices; i++) {
        if (graph->adjacency_matrix[v][i] && !visited[i]) {
            dfs_recursive(graph, i, visited, visit);
        }
    }
}

void graph_dfs(Graph* graph, int start, void (*visit)(int)) {
    bool visited[MAX_VERTICES] = {false};
    dfs_recursive(graph, start, visited, visit);
}

void graph_bfs(Graph* graph, int start, void (*visit)(int)) {
    bool visited[MAX_VERTICES] = {false};
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    visited[start] = true;
    queue[rear++] = start;

    while (front < rear) {
        int v = queue[front++];
        visit(v);

        for (int i = 0; i < graph->num_vertices; i++) {
            if (graph->adjacency_matrix[v][i] && !visited[i]) {
                visited[i] = true;
                queue[rear++] = i;
            }
        }
    }
}