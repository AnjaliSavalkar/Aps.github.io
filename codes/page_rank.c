#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 4
#define MAX_ITER 100
#define DAMPING 0.85

void pageRank(double graph[N][N], double rank[N]) {
    double newRank[N]; 
    int iter = 0;

    for (int i = 0; i < N; i++) {
        rank[i] = 1.0 / N;
    }

    while (iter < MAX_ITER) {
        for (int i = 0; i < N; i++) {
            newRank[i] = (1.0 - DAMPING) / N;
            
            for (int j = 0; j < N; j++) {
                if (graph[j][i] != 0) {
                    int outDegree = 0;
                    for (int k = 0; k < N; k++) {
                        if (graph[j][k] != 0) {
                            outDegree++;
                        }
                    }
                    newRank[i] += DAMPING * (rank[j] / outDegree);
                }
            }
        }

        for (int i = 0; i < N; i++) {
            rank[i] = newRank[i];
        }

        iter++;
    }
}

void printRanks(double rank[N]) {
    printf("Product Ranks:\n");
    for (int i = 0; i < N; i++) {
        printf("Product %d: Rank = %lf\n", i + 1, rank[i]);
    }
}

int main() {
    double graph[N][N] = {
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {1, 0, 0, 0}
    };

    double rank[N];

    pageRank(graph, rank);

    printRanks(rank);

    return 0;
}
