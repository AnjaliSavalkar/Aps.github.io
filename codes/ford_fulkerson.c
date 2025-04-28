#include <stdio.h>
#include <string.h>
#include <limits.h>

#define V 6  // Number of vertices

// A DFS-based function to find if there is a path from source 's' to sink 't' in the residual graph
int dfs(int rGraph[V][V], int s, int t, int parent[]) {
    // Create a visited array and initialize all vertices as not visited
    int visited[V];
    memset(visited, 0, sizeof(visited));

    // Create a stack for DFS traversal
    int stack[V];
    int top = -1;
    stack[++top] = s;
    visited[s] = 1;
    parent[s] = -1;

    // Do DFS traversal and find a path from source to sink
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

// Ford-Fulkerson algorithm for finding the maximum flow in a flow network
int fordFulkerson(int graph[V][V], int source, int sink) {
    // Create a residual graph and initialize it as the original graph
    int rGraph[V][V];  // Residual graph
    for (int u = 0; u < V; u++) {
        for (int v = 0; v < V; v++) {
            rGraph[u][v] = graph[u][v];
        }
    }

    // Array to store the path
    int parent[V];
    int maxFlow = 0;

    // Augument the flow while there is a path from source to sink in the residual graph
    while (dfs(rGraph, source, sink, parent)) {
        // Find the maximum flow through the path found by DFS
        int pathFlow = INT_MAX;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = (pathFlow < rGraph[u][v]) ? pathFlow : rGraph[u][v];
        }

        // Update residual capacities of the edges and reverse edges along the path
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= pathFlow;
            rGraph[v][u] += pathFlow;
        }

        // Add the path flow to the total flow
        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main() {
    // Example graph (Network)
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
