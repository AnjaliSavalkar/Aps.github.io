#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Define a structure to represent the graph
struct Edge {
    int vertex, weight;
    struct Edge* next;
};

// Define a structure to represent the priority queue
struct MinHeap {
    int* vertex;
    int* dist;
    int size;
};

// Function to create a new edge
struct Edge* newEdge(int vertex, int weight) {
    struct Edge* edge = (struct Edge*)malloc(sizeof(struct Edge));
    edge->vertex = vertex;
    edge->weight = weight;
    edge->next = NULL;
    return edge;
}

// Function to create a new min heap
struct MinHeap* createMinHeap(int size) {
    struct MinHeap* heap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    heap->vertex = (int*)malloc(size * sizeof(int));
    heap->dist = (int*)malloc(size * sizeof(int));
    heap->size = 0;
    return heap;
}

// Function to insert a vertex into the min heap
void insertMinHeap(struct MinHeap* heap, int vertex, int dist) {
    heap->vertex[heap->size] = vertex;
    heap->dist[heap->size] = dist;
    heap->size++;
}

// Function to extract the vertex with the minimum distance
int extractMin(struct MinHeap* heap) {
    int min = INT_MAX, minIndex = -1;
    for (int i = 0; i < heap->size; i++) {
        if (heap->dist[i] < min) {
            min = heap->dist[i];
            minIndex = i;
        }
    }
    int minVertex = heap->vertex[minIndex];
    heap->dist[minIndex] = INT_MAX;
    return minVertex;
}

// Function to update the distance of a vertex in the min heap
void updateMinHeap(struct MinHeap* heap, int vertex, int dist) {
    for (int i = 0; i < heap->size; i++) {
        if (heap->vertex[i] == vertex) {
            heap->dist[i] = dist;
        }
    }
}

// Function to perform UCS for finding the least-cost path
void uniformCostSearch(struct Edge* graph[], int V, int start, int end) {
    struct MinHeap* heap = createMinHeap(V);
    int dist[V];
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
    }
    dist[start] = 0;
    insertMinHeap(heap, start, 0);

    while (heap->size > 0) {
        int u = extractMin(heap);

        if (u == end) {
            printf("The minimum cost from %d to %d is: %d\n", start, end, dist[end]);
            return;
        }

        struct Edge* edge = graph[u];
        while (edge != NULL) {
            int v = edge->vertex;
            int weight = edge->weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                updateMinHeap(heap, v, dist[v]);
                insertMinHeap(heap, v, dist[v]);
            }
            edge = edge->next;
        }
    }
}

int main() {
    int V = 5;  // Number of vertices
    struct Edge* graph[V];
    for (int i = 0; i < V; i++) {
        graph[i] = NULL;
    }

    // Create the graph (adjacency list)
    graph[0] = newEdge(1, 10);
    graph[0]->next = newEdge(2, 5);
    graph[1] = newEdge(2, 2);
    graph[1]->next = newEdge(3, 1);
    graph[2] = newEdge(1, 3);
    graph[2]->next = newEdge(3, 9);
    graph[3] = newEdge(4, 4);
    graph[4] = newEdge(3, 6);

    // Call UCS from node 0 to node 4
    uniformCostSearch(graph, V, 0, 4);

    return 0;
}
