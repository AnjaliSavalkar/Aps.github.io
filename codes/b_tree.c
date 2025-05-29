#include <stdio.h>
#include <stdlib.h>

#define MIN_DEGREE 3

typedef struct BTreeNode {
    int keys[2 * MIN_DEGREE - 1];
    struct BTreeNode* children[2 * MIN_DEGREE];
    int n;
    int leaf;
} BTreeNode;

BTreeNode* createNode(int leaf) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->leaf = leaf;
    node->n = 0;
    for (int i = 0; i < 2 * MIN_DEGREE; i++) node->children[i] = NULL;
    return node;
}

void splitChild(BTreeNode* parent, int i, BTreeNode* child) {
    BTreeNode* z = createNode(child->leaf);
    z->n = MIN_DEGREE - 1;
    for (int j = 0; j < MIN_DEGREE - 1; j++) z->keys[j] = child->keys[j + MIN_DEGREE];
    if (!child->leaf) {
        for (int j = 0; j < MIN_DEGREE; j++) z->children[j] = child->children[j + MIN_DEGREE];
    }
    child->n = MIN_DEGREE - 1;
    for (int j = parent->n; j >= i + 1; j--) parent->children[j + 1] = parent->children[j];
    parent->children[i + 1] = z;
    for (int j = parent->n - 1; j >= i; j--) parent->keys[j + 1] = parent->keys[j];
    parent->keys[i] = child->keys[MIN_DEGREE - 1];
    parent->n++;
}

void insertNonFull(BTreeNode* node, int k) {
    int i = node->n - 1;
    if (node->leaf) {
        while (i >= 0 && node->keys[i] > k) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = k;
        node->n++;
    } else {
        while (i >= 0 && node->keys[i] > k) i--;
        i++;
        if (node->children[i]->n == 2 * MIN_DEGREE - 1) {
            splitChild(node, i, node->children[i]);
            if (node->keys[i] < k) i++;
        }
        insertNonFull(node->children[i], k);
    }
}

BTreeNode* insert(BTreeNode* root, int k) {
    if (root == NULL) {
        root = createNode(1);
        root->keys[0] = k;
        root->n = 1;
        return root;
    }
    if (root->n == 2 * MIN_DEGREE - 1) {
        BTreeNode* s = createNode(0);
        s->children[0] = root;
        splitChild(s, 0, root);
        int i = 0;
        if (s->keys[0] < k) i++;
        insertNonFull(s->children[i], k);
        return s;
    } else {
        insertNonFull(root, k);
        return root;
    }
}

void traverse(BTreeNode* root) {
    if (root != NULL) {
        int i;
        for (i = 0; i < root->n; i++) {
            if (!root->leaf) traverse(root->children[i]);
            printf("%d ", root->keys[i]);
        }
        if (!root->leaf) traverse(root->children[i]);
    }
}

int main() {
    BTreeNode* root = NULL;
    int keys[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++) {
        root = insert(root, keys[i]);
    }

    traverse(root);
    printf("\n");

    return 0;
}
