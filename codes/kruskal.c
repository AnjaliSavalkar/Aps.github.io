#include <stdio.h>
#include <stdlib.h>

// Structure to represent a weighted edge
typedef struct {
    int u, v, weight;
} Edge;

// Disjoint-set (union-find) data structure
int parent[100], rank[100];

// Find function with path compression
int find(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i]);
}

// Union function to combine two sets
void unionSets(int u, int v) {
    int root_u = find(u);
    int root_v = find(v);
    if (root_u != root_v) {
        // Union by rank
        if (rank[root_u] > rank[root_v]) {
            parent[root_v] = root_u;
        } else if (rank[root_u] < rank[root_v]) {
            parent[root_u] = root_v;
        } else {
            parent[root_v] = root_u;
            rank[root_u]++;
        }
    }
}

// Function to compare two edges by their weight (for sorting)
int compareEdges(const void *a, const void *b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

// Kruskal's algorithm to find the MST
void kruskal(Edge edges[], int numEdges, int numVertices) {
    // Initialize disjoint-set
    for (int i = 0; i < numVertices; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    // Sort edges by weight
    qsort(edges, numEdges, sizeof(Edge), compareEdges);

    int mstWeight = 0;
    printf("Edges in the MST:\n");
    for (int i = 0; i < numEdges; i++) {
        int u = edges[i].u;
        int v = edges[i].v;

        // If u and v are in different sets, add the edge to the MST
        if (find(u) != find(v)) {
            printf("%d - %d : %d\n", u, v, edges[i].weight);
            mstWeight += edges[i].weight;
            unionSets(u, v);
        }
    }

    printf("Total weight of MST: %d\n", mstWeight);
}

int main() {
    // Number of vertices (warehouses) and edges (transportation routes)
    int numVertices = 5; // Example: 5 warehouses
    int numEdges = 7;    // Example: 7 transportation routes

    // List of edges (u, v, weight)
    Edge edges[] = {
        {0, 1, 2},
        {0, 3, 6},
        {1, 2, 3},
        {1, 3, 8},
        {1, 4, 5},
        {2, 4, 7},
        {3, 4, 9}
    };

    // Run Kruskal’s Algorithm
    kruskal(edges, numEdges, numVertices);

    return 0;
}
