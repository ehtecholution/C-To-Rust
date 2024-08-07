#include <stdio.h>
#include <assert.h>
#include "../src/data_structures/graph.h"

void test_graph_creation_and_edges() {
    Graph* graph = graph_create(5);
    
    graph_add_edge(graph, 0, 1);
    graph_add_edge(graph, 0, 4);
    graph_add_edge(graph, 1, 2);
    graph_add_edge(graph, 1, 3);
    graph_add_edge(graph, 1, 4);
    graph_add_edge(graph, 2, 3);
    graph_add_edge(graph, 3, 4);
    
    assert(graph_has_edge(graph, 0, 1));
    assert(graph_has_edge(graph, 0, 4));
    assert(!graph_has_edge(graph, 0, 2));
    
    graph_remove_edge(graph, 1, 4);
    assert(!graph_has_edge(graph, 1, 4));
    
    graph_destroy(graph);
    printf("Graph creation and edge operations test passed.\n");
}

void visit(int vertex) {
    printf("%d ", vertex);
}

void test_graph_traversal() {
    Graph* graph = graph_create(5);
    
    graph_add_edge(graph, 0, 1);
    graph_add_edge(graph, 0, 4);
    graph_add_edge(graph, 1, 2);
    graph_add_edge(graph, 1, 3);
    graph_add_edge(graph, 1, 4);
    graph_add_edge(graph, 2, 3);
    graph_add_edge(graph, 3, 4);
    
    printf("DFS traversal: ");
    graph_dfs(graph, 0, visit);
    printf("\n");
    
    printf("BFS traversal: ");
    graph_bfs(graph, 0, visit);
    printf("\n");
    
    graph_destroy(graph);
    printf("Graph traversal test passed.\n");
}

int main() {
    test_graph_creation_and_edges();
    test_graph_traversal();
    printf("All graph tests passed.\n");
    return 0;
}