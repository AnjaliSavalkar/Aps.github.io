
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

// Grid size
#define ROW 10
#define COL 10

// Directional moves (left, right, up, down)
int rowMoves[] = {-1, 1, 0, 0};
int colMoves[] = {0, 0, -1, 1};

// Define the Node structure
typedef struct Node {
    int x, y;
    int g, h, f;
    struct Node* parent;
} Node;

// Min-heap for A* algorithm
typedef struct {
    Node** nodes;
    int size;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->nodes = (Node**)malloc(capacity * sizeof(Node*));
    minHeap->size = 0;
    return minHeap;
}

void swapNodes(Node** a, Node** b) {
    Node* temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->nodes[left]->f < heap->nodes[smallest]->f) {
        smallest = left;
    }

    if (right < heap->size && heap->nodes[right]->f < heap->nodes[smallest]->f) {
        smallest = right;
    }

    if (smallest != idx) {
        swapNodes(&heap->nodes[idx], &heap->nodes[smallest]);
        heapify(heap, smallest);
    }
}

Node* pop(MinHeap* heap) {
    if (heap->size == 0) return NULL;

    Node* node = heap->nodes[0];
    heap->nodes[0] = heap->nodes[heap->size - 1];
    heap->size--;
    heapify(heap, 0);

    return node;
}

void push(MinHeap* heap, Node* node) {
    heap->nodes[heap->size] = node;
    heap->size++;

    int idx = heap->size - 1;
    while (idx > 0 && heap->nodes[(idx - 1) / 2]->f > heap->nodes[idx]->f) {
        swapNodes(&heap->nodes[idx], &heap->nodes[(idx - 1) / 2]);
        idx = (idx - 1) / 2;
    }
}

// Heuristic: Manhattan distance
int heuristic(int x, int y, int goalX, int goalY) {
    return abs(x - goalX) + abs(y - goalY);
}

// Check if the position is valid and not blocked
bool isValid(int x, int y, int grid[ROW][COL]) {
    return x >= 0 && x < ROW && y >= 0 && y < COL && grid[x][y] == 0;
}

void reconstructPath(Node* node) {
    if (node == NULL) return;
    reconstructPath(node->parent);
    printf("(%d, %d) -> ", node->x, node->y);
}

void AStar(int grid[ROW][COL], int startX, int startY, int goalX, int goalY) {
    // Create the open list (min-heap)
    MinHeap* openList = createMinHeap(ROW * COL);
    
    // Initialize start node
    Node* startNode = (Node*)malloc(sizeof(Node));
    startNode->x = startX;
    startNode->y = startY;
    startNode->g = 0;
    startNode->h = heuristic(startX, startY, goalX, goalY);
    startNode->f = startNode->g + startNode->h;
    startNode->parent = NULL;
    
    push(openList, startNode);
    
    // Array to track visited nodes
    bool closedList[ROW][COL];
    memset(closedList, 0, sizeof(closedList));
    
    while (openList->size > 0) {
        Node* current = pop(openList);
        
        if (current->x == goalX && current->y == goalY) {
            printf("Path found: ");
            reconstructPath(current);
            printf("Goal reached!\n");
            return;
        }
        
        closedList[current->x][current->y] = 1;
        
        // Explore neighbors (left, right, up, down)
        for (int i = 0; i < 4; i++) {
            int newX = current->x + rowMoves[i];
            int newY = current->y + colMoves[i];
            
            if (isValid(newX, newY, grid) && !closedList[newX][newY]) {
                Node* neighbor = (Node*)malloc(sizeof(Node));
                neighbor->x = newX;
                neighbor->y = newY;
                neighbor->g = current->g + 1;
                neighbor->h = heuristic(newX, newY, goalX, goalY);
                neighbor->f = neighbor->g + neighbor->h;
                neighbor->parent = current;
                
                push(openList, neighbor);
            }
        }
    }
    
    printf("No path found!\n");
}

int main() {
    // Example grid where 0 is an open road, and 1 is a blocked road
    int grid[ROW][COL] = {
        {0, 1, 0, 0, 0, 1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 1, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 1, 1, 0, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    
    int startX = 0, startY = 0; // Starting point (top-left corner)
    int goalX = 9, goalY = 9;   // Goal point (bottom-right corner)
    
    AStar(grid, startX, startY, goalX, goalY);
    
    return 0;
}
