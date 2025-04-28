#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100000

// Define a structure to represent queries
struct Query {
    int left, right, idx;
};

// Compare function for sorting queries based on Mo's algorithm logic
int compare(struct Query a, struct Query b) {
    return a.left / (int)sqrt(MAX) == b.left / (int)sqrt(MAX) ? a.right - b.right : a.left - b.left;
}

// Function to add an element to the current range
void add(int idx, int *current_cost, int *usage_data, int *cost) {
    *current_cost += usage_data[idx];
}

// Function to remove an element from the current range
void remove(int idx, int *current_cost, int *usage_data, int *cost) {
    *current_cost -= usage_data[idx];
}

// Function to process the queries using Mo's Algorithm
void mosAlgorithm(int *usage_data, int n, struct Query *queries, int q) {
    // Sort the queries based on Mo's algorithm
    qsort(queries, q, sizeof(struct Query), compare);
    
    int current_cost = 0;
    int result[q];
    int l = 0, r = -1;

    // Process each query
    for (int i = 0; i < q; i++) {
        int left = queries[i].left;
        int right = queries[i].right;
        
        // Move the right pointer to the right position
        while (r < right) {
            r++;
            add(r, &current_cost, usage_data, result);
        }
        while (r > right) {
            remove(r, &current_cost, usage_data, result);
            r--;
        }
        
        // Move the left pointer to the right position
        while (l < left) {
            remove(l, &current_cost, usage_data, result);
            l++;
        }
        while (l > left) {
            l--;
            add(l, &current_cost, usage_data, result);
        }
        
        // Store the result for the current query
        result[queries[i].idx] = current_cost;
    }

    // Print the results for each query
    for (int i = 0; i < q; i++) {
        printf("Query %d: Total Cost = %d\n", i + 1, result[i]);
    }
}

int main() {
    int usage_data[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100}; // Example data (cost per unit for different time periods)
    int n = sizeof(usage_data) / sizeof(usage_data[0]);
    
    // Define the queries
    struct Query queries[] = {{0, 4, 0}, {2, 6, 1}, {4, 9, 2}};
    int q = sizeof(queries) / sizeof(queries[0]);

    // Call the function to process queries
    mosAlgorithm(usage_data, n, queries, q);
    
    return 0;
}
