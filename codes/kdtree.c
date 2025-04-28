#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_DIMENSIONS 10

// Define a structure to represent a point in high-dimensional space
struct Point {
    int dimensions[MAX_DIMENSIONS];
};

// Define a structure to represent a KD-Tree node
struct KDTreeNode {
    struct Point point;
    struct KDTreeNode *left, *right;
};

// Function to calculate the distance between two points
double distance(struct Point a, struct Point b, int dim) {
    double dist = 0;
    for (int i = 0; i < dim; i++) {
        dist += pow(a.dimensions[i] - b.dimensions[i], 2);
    }
    return sqrt(dist);
}

// Function to build the KD Tree
struct KDTreeNode* buildKDTree(struct Point points[], int start, int end, int depth, int dim) {
    if (start > end) return NULL;

    // Find the dimension to split on (based on the current depth)
    int axis = depth % dim;

    // Sort points according to the axis
    qsort(points + start, end - start + 1, sizeof(struct Point), 
        (int (*)(const void *, const void *))(
            (axis == 0) ? compareX : compareY));

    // Find the median point and create a node
    int median = (start + end) / 2;
    struct KDTreeNode *node = (struct KDTreeNode*)malloc(sizeof(struct KDTreeNode));
    node->point = points[median];
    node->left = buildKDTree(points, start, median - 1, depth + 1, dim);
    node->right = buildKDTree(points, median + 1, end, depth + 1, dim);
    
    return node;
}

// Function to perform nearest neighbor search in KD-Tree
struct KDTreeNode* nearestNeighbor(struct KDTreeNode* root, struct Point target, int depth, int dim, struct KDTreeNode* best) {
    if (root == NULL) return best;
    
    // Calculate the distance between the current node and target point
    struct KDTreeNode* currentBest = best;
    double currentDist = distance(root->point, target, dim);
    double bestDist = (currentBest == NULL) ? INFINITY : distance(currentBest->point, target, dim);
    if (currentDist < bestDist) {
        currentBest = root;
    }
    
    int axis = depth % dim;
    struct KDTreeNode* nextBranch = NULL;
    struct KDTreeNode* oppositeBranch = NULL;

    if (target.dimensions[axis] < root->point.dimensions[axis]) {
        nextBranch = root->left;
        oppositeBranch = root->right;
    } else {
        nextBranch = root->right;
        oppositeBranch = root->left;
    }
    
    // Search the next branch
    currentBest = nearestNeighbor(nextBranch, target, depth + 1, dim, currentBest);

    // Check if we need to search the opposite branch
    if (fabs(target.dimensions[axis] - root->point.dimensions[axis]) < distance(currentBest->point, target, dim)) {
        currentBest = nearestNeighbor(oppositeBranch, target, depth + 1, dim, currentBest);
    }

    return currentBest;
}

// Helper function to compare points based on x-axis (for sorting)
int compareX(const void* a, const void* b) {
    return ((struct Point*)a)->dimensions[0] - ((struct Point*)b)->dimensions[0];
}

// Helper function to compare points based on y-axis (for sorting)
int compareY(const void* a, const void* b) {
    return ((struct Point*)a)->dimensions[1] - ((struct Point*)b)->dimensions[1];
}

int main() {
    struct Point points[] = {{.dimensions = {1, 2}}, {.dimensions = {3, 4}}, {.dimensions = {5, 6}}};
    int n = sizeof(points) / sizeof(points[0]);

    int dim = 2; // Number of dimensions (e.g., genre, ratings)
    struct KDTreeNode* root = buildKDTree(points, 0, n - 1, 0, dim);

    struct Point target = {.dimensions = {3, 3}}; // Example query point (user preferences)

    struct KDTreeNode* nearest = nearestNeighbor(root, target, 0, dim, NULL);
    
    printf("Nearest neighbor point: ");
    for (int i = 0; i < dim; i++) {
        printf("%d ", nearest->point.dimensions[i]);
    }
    printf("\n");

    return 0;
}
