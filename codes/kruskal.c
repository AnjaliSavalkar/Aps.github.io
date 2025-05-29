#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u, v, weight;
} Edge;

int parent[100], rank[100];

int find(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i]);
}

void unionSets(int u, int v) {
    int root_u = find(u);
    int root_v = find(v);
    if (root_u != root_v) {
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

int compareEdges(const void *a, const void *b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

void kruskal(Edge edges[], int numEdges, int numVertices) {
    for (int i = 0; i < numVertices; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    qsort(edges, numEdges, sizeof(Edge), compareEdges);

    int mstWeight = 0;
    printf("Edges in the MST:\n");
    for (int i = 0; i < numEdges; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        if (find(u) != find(v)) {
            printf("%d - %d : %d\n", u, v, edges[i].weight);
            mstWeight += edges[i].weight;
            unionSets(u, v);
        }
    }
    printf("Total weight of MST: %d\n", mstWeight);
}

int main() {
    int numVertices = 5;
    int numEdges = 7;

    Edge edges[] = {
        {0, 1, 2},
        {0, 3, 6},
        {1, 2, 3},
        {1, 3, 8},
        {1, 4, 5},
        {2, 4, 7},
        {3, 4, 9}
    };

    kruskal(edges, numEdges, numVertices);

    return 0;
}
