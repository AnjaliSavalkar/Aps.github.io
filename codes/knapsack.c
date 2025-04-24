#include <stdio.h>
#include <stdlib.h>

// Function to find the maximum value we can obtain using 0/1 Knapsack
int knapsack(int capacity, int weights[], int values[], int n) {
    // Create a DP table to store the maximum value at each capacity
    int dp[capacity + 1];

    // Initialize all dp values to 0
    for (int i = 0; i <= capacity; i++) {
        dp[i] = 0;
    }

    // Iterate over each item
    for (int i = 0; i < n; i++) {
        // Traverse dp array backwards to prevent overwriting the results of this iteration
        for (int w = capacity; w >= weights[i]; w--) {
            dp[w] = (dp[w] > dp[w - weights[i]] + values[i]) ? dp[w] : dp[w - weights[i]] + values[i];
        }
    }

    // The maximum value is stored at dp[capacity]
    return dp[capacity];
}

int main() {
    // Example products with their weights (storage requirements) and values (profit)
    int weights[] = {2, 3, 4, 5};   // Storage requirement of each product
    int values[] = {3, 4, 5, 6};   // Profit or value of each product
    int n = sizeof(values) / sizeof(values[0]); // Number of products
    int capacity = 5;  // Available space in the warehouse (capacity)

    // Call the knapsack function to get the maximum value (optimal stock allocation)
    int maxProfit = knapsack(capacity, weights, values, n);

    // Print the result
    printf("Maximum profit (stock allocation): %d\n", maxProfit);

    return 0;
}
