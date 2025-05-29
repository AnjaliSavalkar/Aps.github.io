#include <stdio.h>
#include <stdlib.h>

int knapsack(int capacity, int weights[], int values[], int n) {
    int dp[capacity + 1];
    for (int i = 0; i <= capacity; i++) {
        dp[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        for (int w = capacity; w >= weights[i]; w--) {
            if (dp[w] < dp[w - weights[i]] + values[i]) {
                dp[w] = dp[w - weights[i]] + values[i];
            }
        }
    }
    return dp[capacity];
}

int main() {
    int weights[] = {2, 3, 4, 5};
    int values[] = {3, 4, 5, 6};
    int n = sizeof(values) / sizeof(values[0]);
    int capacity = 5;

    int maxProfit = knapsack(capacity, weights, values, n);
    printf("Maximum profit (stock allocation): %d\n", maxProfit);

    return 0;
}
