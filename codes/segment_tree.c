#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000

int A[MAXN];
int tree[4 * MAXN];

void build(int node, int start, int end) {
    if (start == end) {
        tree[node] = A[start];
    } else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
}

void update(int node, int start, int end, int idx, int val) {
    if (start == end) {
        A[idx] += val;
        tree[node] += val;
    } else {
        int mid = (start + end) / 2;
        if (start <= idx && idx <= mid) {
            update(2 * node, start, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, end, idx, val);
        }
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
}

int query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
        return 0;
    }
    if (l <= start && end <= r) {
        return tree[node];
    }
    int mid = (start + end) / 2;
    int p1 = query(2 * node, start, mid, l, r);
    int p2 = query(2 * node + 1, mid + 1, end, l, r);
    return p1 + p2;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }
    build(1, 0, n - 1);
    printf("Sum of values in range [1, 3]: %d\n", query(1, 0, n - 1, 1, 3));
    update(1, 0, n - 1, 1, 10);
    printf("After update, sum of values in range [1, 3]: %d\n", query(1, 0, n - 1, 1, 3));
    return 0;
}
