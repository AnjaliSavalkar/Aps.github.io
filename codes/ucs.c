#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define INF 1000000

typedef struct {
    int node;
    int cost;
} Node;

typedef struct {
    Node data[MAX];
    int size;
} PriorityQueue;

void swap(Node* a, Node* b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void push(PriorityQueue* pq, int node, int cost) {
    pq->data[pq->size].node = node;
    pq->data[pq->size].cost = cost;
    int i = pq->size++;
    while (i > 0 && pq->data[i].cost < pq->data[(i - 1) / 2].cost) {
        swap(&pq->data[i], &pq->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

Node pop(PriorityQueue* pq) {
    Node top = pq->data[0];
    pq->data[0] = pq->data[--pq->size];
    int i = 0;
    while (2 * i + 1 < pq->size) {
        int minIndex = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < pq->size && pq->data[left].cost < pq->data[minIndex].cost)
            minIndex = left;
        if (right < pq->size && pq->data[right].cost < pq->data[minIndex].cost)
            minIndex = right;
        if (minIndex == i) break;
        swap(&pq->data[i], &pq->data[minIndex]);
        i = minIndex;
    }
    return top;
}

int visited[MAX];
int dist[MAX];
int parent[MAX];
int adj[MAX][MAX];

void uniform_cost_search(int start, int goal, int n) {
    PriorityQueue pq = { .size = 0 };
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }
    dist[start] = 0;
    push(&pq, start, 0);

    while (pq.size > 0) {
        Node current = pop(&pq);
        int u = current.node;
        if (visited[u]) continue;
        visited[u] = 1;
        if (u == goal) break;

        for (int v = 0; v < n; v++) {
            if (adj[u][v] > 0 && dist[v] > dist[u] + adj[u][v]) {
                dist[v] = dist[u] + adj[u][v];
                parent[v] = u;
                push(&pq, v, dist[v]);
            }
        }
    }

    if (dist[goal] == INF) {
        printf("No path found.\n");
        return;
    }

    printf("Minimum cost from %d to %d: %d\n", start, goal, dist[goal]);
    printf("Path: ");
    int path[MAX], len = 0;
    for (int v = goal; v != -1; v = parent[v])
        path[len++] = v;
    for (int i = len - 1; i >= 0; i--)
        printf("%d ", path[i]);
    printf("\n");
}

int main() {
    int n = 5;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;

    adj[0][1] = 2;
    adj[0][2] = 4;
    adj[1][2] = 1;
    adj[1][3] = 7;
    adj[2][4] = 3;
    adj[3][4] = 1;

    int start = 0, goal = 4;
    uniform_cost_search(start, goal, n);
    return 0;
}
