#include <stdio.h>
#include <limits.h>

int maxKadane(int* arr, int n) {
    int maxSum = INT_MIN, currentSum = 0;
    for (int i = 0; i < n; i++) {
        currentSum = currentSum + arr[i];
        if (maxSum < currentSum)
            maxSum = currentSum;
        if (currentSum < 0)
            currentSum = 0;
    }
    return maxSum;
}

int maxSumRectangle(int mat[][100], int row, int col) {
    int maxSum = INT_MIN;
    int temp[100];

    for (int left = 0; left < col; left++) {
        for (int i = 0; i < row; i++)
            temp[i] = 0;

        for (int right = left; right < col; right++) {
            for (int i = 0; i < row; i++)
                temp[i] += mat[i][right];

            int sum = maxKadane(temp, row);
            if (sum > maxSum)
                maxSum = sum;
        }
    }

    return maxSum;
}

int main() {
    int mat[4][100] = {
        {1, 2, -1, -4},
        {-8, -3, 4, 2},
        {3, 8, 10, 1},
        {-4, -1, 1, 7}
    };
    int row = 4, col = 4;
    int maxSum = maxSumRectangle(mat, row, col);
    printf("Maximum sum submatrix = %d\n", maxSum);
    return 0;
}
