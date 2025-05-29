#include <stdio.h>
#include <string.h>
#include <limits.h>

#define V 6

int dfs(int rGraph[V][V], int s, int t, int parent[]) {
    int visited[V];
    memset(visited, 0, sizeof(visited));
    int stack[V];
    int top = -1;
    stack[++top] = s;
    visited[s] = 1;
    parent[s] = -1;
    while (top >= 0) {
        int u = stack[top--];
        for (int v = 0; v < V; v++) {
            if (visited[v] == 0 && rGraph[u][v] > 0) {
                stack[++top] = v;
                parent[v] = u;
                visited[v] = 1;
                if (v == t)
                    return 1;
            }
        }
    }
    return 0;
}

int fordFulkerson(int graph[V][V], int source, int sink) {
    int rGraph[V][V];
    for (int u = 0; u < V; u++) {
        for (int v = 0; v < V; v++) {
            rGraph[u][v] = graph[u][v];
        }
    }
    int parent[V];
    int maxFlow = 0;
    while (dfs(rGraph, source, sink, parent)) {
        int pathFlow = INT_MAX;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = (pathFlow < rGraph[u][v]) ? pathFlow : rGraph[u][v];
        }
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= pathFlow;
            rGraph[v][u] += pathFlow;
        }
        maxFlow += pathFlow;
    }
    return maxFlow;
}

int main() {
    int graph[V][V] = {
        {0, 16, 13, 0, 0, 0},
        {0, 0, 10, 12, 0, 0},
        {0, 4, 0, 0, 14, 0},
        {0, 0, 9, 0, 0, 20},
        {0, 0, 0, 7, 0, 4},
        {0, 0, 0, 0, 0, 0}
    };
    printf("The maximum possible flow is %d\n", fordFulkerson(graph, 0, 5));
    return 0;
}
