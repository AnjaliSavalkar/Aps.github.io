#include <stdio.h>
#include <math.h>

#define MAXN 100000

int arr[MAXN];
int block[MAXN];
int blk_sz;

void preprocess(int n) {
    blk_sz = sqrt(n);
    for (int i = 0; i < n; i++)
        block[i / blk_sz] += arr[i];
}

int query(int l, int r) {
    int sum = 0;
    while (l < r && l % blk_sz != 0 && l != 0) {
        sum += arr[l];
        l++;
    }
    while (l + blk_sz <= r) {
        sum += block[l / blk_sz];
        l += blk_sz;
    }
    while (l <= r) {
        sum += arr[l];
        l++;
    }
    return sum;
}

int main() {
    int n = 9;
    arr[0] = 1; arr[1] = 1; arr[2] = 2; arr[3] = 1; arr[4] = 3;
    arr[5] = 4; arr[6] = 5; arr[7] = 2; arr[8] = 8;

    preprocess(n);

    printf("Sum of [0, 4] is %d\n", query(0, 4));
    printf("Sum of [1, 3] is %d\n", query(1, 3));
    printf("Sum of [2, 4] is %d\n", query(2, 4));

    return 0;
}
