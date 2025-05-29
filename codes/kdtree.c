#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_DIMENSIONS 10

struct Point {
    int dimensions[MAX_DIMENSIONS];
};

struct KDTreeNode {
    struct Point point;
    struct KDTreeNode *left, *right;
};

double distance(struct Point a, struct Point b, int dim) {
    double dist = 0;
    for (int i = 0; i < dim; i++) {
        dist += pow(a.dimensions[i] - b.dimensions[i], 2);
    }
    return sqrt(dist);
}

int compareX(const void* a, const void* b) {
    return ((struct Point*)a)->dimensions[0] - ((struct Point*)b)->dimensions[0];
}

int compareY(const void* a, const void* b) {
    return ((struct Point*)a)->dimensions[1] - ((struct Point*)b)->dimensions[1];
}

struct KDTreeNode* buildKDTree(struct Point points[], int start, int end, int depth, int dim) {
    if (start > end) return NULL;
    int axis = depth % dim;
    qsort(points + start, end - start + 1, sizeof(struct Point), 
        (int (*)(const void *, const void *))(
            (axis == 0) ? compareX : compareY));
    int median = (start + end) / 2;
    struct KDTreeNode *node = (struct KDTreeNode*)malloc(sizeof(struct KDTreeNode));
    node->point = points[median];
    node->left = buildKDTree(points, start, median - 1, depth + 1, dim);
    node->right = buildKDTree(points, median + 1, end, depth + 1, dim);
    return node;
}

struct KDTreeNode* nearestNeighbor(struct KDTreeNode* root, struct Point target, int depth, int dim, struct KDTreeNode* best) {
    if (root == NULL) return best;
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
    currentBest = nearestNeighbor(nextBranch, target, depth + 1, dim, currentBest);
    if (fabs(target.dimensions[axis] - root->point.dimensions[axis]) < distance(currentBest->point, target, dim)) {
        currentBest = nearestNeighbor(oppositeBranch, target, depth + 1, dim, currentBest);
    }
    return currentBest;
}

int main() {
    struct Point points[] = {{.dimensions = {1, 2}}, {.dimensions = {3, 4}}, {.dimensions = {5, 6}}};
    int n = sizeof(points) / sizeof(points[0]);
    int dim = 2;
    struct KDTreeNode* root = buildKDTree(points, 0, n - 1, 0, dim);
    struct Point target = {.dimensions = {3, 3}};
    struct KDTreeNode* nearest = nearestNeighbor(root, target, 0, dim, NULL);
    printf("Nearest neighbor point: ");
    for (int i = 0; i < dim; i++) {
        printf("%d ", nearest->point.dimensions[i]);
    }
    printf("\n");
    return 0;
}
