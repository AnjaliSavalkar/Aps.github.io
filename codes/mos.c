#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100000

struct Query {
    int left, right, idx;
};

int compare(const void *a, const void *b) {
    struct Query *x = (struct Query *)a;
    struct Query *y = (struct Query *)b;
    int blockX = x->left / (int)sqrt(MAX);
    int blockY = y->left / (int)sqrt(MAX);
    if (blockX == blockY) {
        return x->right - y->right;
    }
    return blockX - blockY;
}

void add(int idx, int *current_cost, int *usage_data, int *cost) {
    *current_cost += usage_data[idx];
}

void remove(int idx, int *current_cost, int *usage_data, int *cost) {
    *current_cost -= usage_data[idx];
}

void mosAlgorithm(int *usage_data, int n, struct Query *queries, int q) {
    qsort(queries, q, sizeof(struct Query), compare);
    
    int current_cost = 0;
    int result[q];
    int l = 0, r = -1;

    for (int i = 0; i < q; i++) {
        int left = queries[i].left;
        int right = queries[i].right;
        
        while (r < right) {
            r++;
            add(r, &current_cost, usage_data, result);
        }
        while (r > right) {
            remove(r, &current_cost, usage_data, result);
            r--;
        }
        
        while (l < left) {
            remove(l, &current_cost, usage_data, result);
            l++;
        }
        while (l > left) {
            l--;
            add(l, &current_cost, usage_data, result);
        }
        
        result[queries[i].idx] = current_cost;
    }

    for (int i = 0; i < q; i++) {
        printf("Query %d: Total Cost = %d\n", i + 1, result[i]);
    }
}

int main() {
    int usage_data[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int n = sizeof(usage_data) / sizeof(usage_data[0]);
    
    struct Query queries[] = {{0, 4, 0}, {2, 6, 1}, {4, 9, 2}};
    int q = sizeof(queries) / sizeof(queries[0]);

    mosAlgorithm(usage_data, n, queries, q);
    
    return 0;
}
