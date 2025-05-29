#include <stdio.h>

int parent[100000], size[100000];

void make_set(int v) {
    parent[v] = v;
    size[v] = 1;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (size[a] < size[b]) {
            int temp = a; a = b; b = temp;
        }
        parent[b] = a;
        size[a] += size[b];
    }
}

int main() {
    int n = 5;
    for (int i = 1; i <= n; i++)
        make_set(i);

    union_sets(1, 2);
    union_sets(3, 4);
    union_sets(2, 3);

    for (int i = 1; i <= n; i++)
        printf("Parent of %d is %d\n", i, find_set(i));

    return 0;
}
