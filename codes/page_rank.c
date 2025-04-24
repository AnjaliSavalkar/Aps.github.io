#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 4 // Number of products (nodes)
#define MAX_ITER 100
#define DAMPING 0.85 // Damping factor for PageRank

// Function to perform PageRank on the product graph
void pageRank(double graph[N][N], double rank[N]) {
    double newRank[N]; 
    int iter = 0;

    // Initialize ranks to 1/N
    for (int i = 0; i < N; i++) {
        rank[i] = 1.0 / N;
    }

    // Iterate to update ranks
    while (iter < MAX_ITER) {
        for (int i = 0; i < N; i++) {
            newRank[i] = (1.0 - DAMPING) / N; // Basic rank formula (damping factor)
            
            // Sum the contribution from other nodes
            for (int j = 0; j < N; j++) {
                if (graph[j][i] != 0) { // There's a link from product j to product i
                    int outDegree = 0;
                    // Calculate out-degree of node j
                    for (int k = 0; k < N; k++) {
                        if (graph[j][k] != 0) {
                            outDegree++;
                        }
                    }
                    newRank[i] += DAMPING * (rank[j] / outDegree);
                }
            }
        }

        // Update ranks
        for (int i = 0; i < N; i++) {
            rank[i] = newRank[i];
        }

        iter++;
    }
}

// Function to print the product ranks
void printRanks(double rank[N]) {
    printf("Product Ranks:\n");
    for (int i = 0; i < N; i++) {
        printf("Product %d: Rank = %lf\n", i + 1, rank[i]);
    }
}

int main() {
    // Graph representing product co-purchases
    // graph[i][j] = 1 means there is a link from product i to product j (i.e., co-purchased)
    double graph[N][N] = {
        {0, 1, 0, 0}, // Product 1 -> Product 2
        {0, 0, 1, 0}, // Product 2 -> Product 3
        {0, 0, 0, 1}, // Product 3 -> Product 4
        {1, 0, 0, 0}  // Product 4 -> Product 1
    };

    // Array to store the ranks of products
    double rank[N];

    // Calculate PageRank
    pageRank(graph, rank);

    // Print the ranks of products
    printRanks(rank);

    return 0;
}
