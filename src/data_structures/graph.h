#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

typedef struct Graph Graph;

Graph* graph_create(int vertices);
void graph_destroy(Graph* graph);
void graph_add_edge(Graph* graph, int src, int dest);
void graph_remove_edge(Graph* graph, int src, int dest);
bool graph_has_edge(Graph* graph, int src, int dest);
void graph_dfs(Graph* graph, int start, void (*visit)(int));
void graph_bfs(Graph* graph, int start, void (*visit)(int));

#endif // GRAPH_H