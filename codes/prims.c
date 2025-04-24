#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

// Structure to represent an edge
typedef struct {
    int u, v, weight;
} Edge;

int graph[MAX][MAX];
int parent[MAX];
int key[MAX];
int mstSet[MAX];

// Function to find the vertex with minimum key value
int minKey(int numVertices) {
    int min = INT_MAX, minIndex;
    for (int v = 0; v < numVertices; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}

// Prim's Algorithm to find MST
void prim(int numVertices) {
    // Initialize all keys as INFINITE and mstSet[] as false
    for (int i = 0; i < numVertices; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    // Start with vertex 0
    key[0] = 0;
    parent[0] = -1; // No parent for the starting node

    for (int count = 0; count < numVertices - 1; count++) {
        // Pick the minimum key vertex from the set of vertices not yet processed
        int u = minKey(numVertices);
        mstSet[u] = 1;

        // Update key value and parent index of the adjacent vertices of the picked vertex
        for (int v = 0; v < numVertices; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Print the constructed MST
    printf("Edges in the MST:\n");
    int totalWeight = 0;
    for (int i = 1; i < numVertices; i++) {
        printf("%d - %d : %d\n", parent[i], i, graph[i][parent[i]]);
        totalWeight += graph[i][parent[i]];
    }
    printf("Total weight of MST: %d\n", totalWeight);
}

int main() {
    // Example number of warehouses (vertices)
    int numVertices = 5;

    // Example graph (adjacency matrix)
    int graph[5][5] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    // Run Prim’s Algorithm
    prim(numVertices);

    return 0;
}
