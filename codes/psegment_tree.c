#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000
#define MAXNODE 4000000

int A[MAXN];

typedef struct Node {
    int sum;
    struct Node *left, *right;
} Node;

Node nodePool[MAXNODE];
int nodeCount = 0;

Node* newNode(int sum, Node* left, Node* right) {
    Node* node = &nodePool[nodeCount++];
    node->sum = sum;
    node->left = left;
    node->right = right;
    return node;
}

Node* build(int start, int end) {
    if (start == end) {
        return newNode(A[start], NULL, NULL);
    }
    int mid = (start + end) / 2;
    Node* leftChild = build(start, mid);
    Node* rightChild = build(mid + 1, end);
    return newNode(leftChild->sum + rightChild->sum, leftChild, rightChild);
}

Node* update(Node* prev, int start, int end, int idx, int val) {
    if (start == end) {
        return newNode(val, NULL, NULL);
    }
    int mid = (start + end) / 2;
    Node *leftChild = prev->left, *rightChild = prev->right;
    if (idx <= mid) {
        leftChild = update(prev->left, start, mid, idx, val);
    } else {
        rightChild = update(prev->right, mid + 1, end, idx, val);
    }
    return newNode(leftChild->sum + rightChild->sum, leftChild, rightChild);
}

int query(Node* root, int start, int end, int l, int r) {
    if (r < start || end < l) return 0;
    if (l <= start && end <= r) return root->sum;
    int mid = (start + end) / 2;
    return query(root->left, start, mid, l, r) + query(root->right, mid + 1, end, l, r);
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }

    Node* versionRoots[q + 1];
    versionRoots[0] = build(0, n - 1);

    for (int i = 1; i <= q; i++) {
        int type;
        scanf("%d", &type);

        if (type == 1) {
            int version, idx, val;
            scanf("%d %d %d", &version, &idx, &val);
            versionRoots[i] = update(versionRoots[version], 0, n - 1, idx, val);
        } else if (type == 2) {
            int version, l, r;
            scanf("%d %d %d", &version, &l, &r);
            printf("%d\n", query(versionRoots[version], 0, n - 1, l, r));
            versionRoots[i] = versionRoots[i-1];
        }
    }

    return 0;
}
