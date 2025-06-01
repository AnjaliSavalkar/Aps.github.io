#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CACHE_CAPACITY 4

typedef struct Node {
    int key;
    int value;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct {
    int key;
    Node* node;
} Entry;

#define HASH_SIZE 100

Entry* hashMap[HASH_SIZE];

typedef struct {
    int capacity;
    int size;
    Node* head;
    Node* tail;
} LRUCache;

int hash(int key) {
    return key % HASH_SIZE;
}

Node* createNode(int key, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

void addNodeAtHead(LRUCache* cache, Node* node) {
    node->next = cache->head;
    node->prev = NULL;
    if (cache->head != NULL)
        cache->head->prev = node;
    cache->head = node;
    if (cache->tail == NULL)
        cache->tail = node;
}

void removeNode(LRUCache* cache, Node* node) {
    if (node->prev)
        node->prev->next = node->next;
    else
        cache->head = node->next;
    if (node->next)
        node->next->prev = node->prev;
    else
        cache->tail = node->prev;
}

void moveToHead(LRUCache* cache, Node* node) {
    removeNode(cache, node);
    addNodeAtHead(cache, node);
}

Node* removeTail(LRUCache* cache) {
    Node* removed = cache->tail;
    if (removed) {
        if (removed->prev)
            removed->prev->next = NULL;
        else
            cache->head = NULL;
        cache->tail = removed->prev;
    }
    return removed;
}

LRUCache* createLRUCache(int capacity) {
    LRUCache* cache = (LRUCache*)malloc(sizeof(LRUCache));
    cache->capacity = capacity;
    cache->size = 0;
    cache->head = cache->tail = NULL;
    memset(hashMap, 0, sizeof(hashMap));
    return cache;
}

int get(LRUCache* cache, int key) {
    int idx = hash(key);
    Entry* entry = hashMap[idx];
    while (entry && entry->key != key)
        entry = (Entry*)(entry->node);
    if (!entry)
        return -1;
    moveToHead(cache, entry->node);
    return entry->node->value;
}

void put(LRUCache* cache, int key, int value) {
    int idx = hash(key);
    Entry* entry = hashMap[idx];
    while (entry && entry->key != key)
        entry = (Entry*)(entry->node);
    if (entry) {
        entry->node->value = value;
        moveToHead(cache, entry->node);
    } else {
        Node* newNode = createNode(key, value);
        addNodeAtHead(cache, newNode);
        Entry* newEntry = (Entry*)malloc(sizeof(Entry));
        newEntry->key = key;
        newEntry->node = newNode;
        newNode->next = (Node*)hashMap[idx];
        hashMap[idx] = newEntry;
        cache->size++;
        if (cache->size > cache->capacity) {
            Node* removed = removeTail(cache);
            int removedIdx = hash(removed->key);
            Entry* e = hashMap[removedIdx];
            Entry* prev = NULL;
            while (e && e->key != removed->key) {
                prev = e;
                e = (Entry*)(e->node);
            }
            if (prev)
                prev->node = (Node*)(e->node);
            else
                hashMap[removedIdx] = (Entry*)(e->node);
            free(e);
            free(removed);
            cache->size--;
        }
    }
}

void printCache(LRUCache* cache) {
    Node* curr = cache->head;
    printf("Cache: ");
    while (curr) {
        printf("[%d:%d] ", curr->key, curr->value);
        curr = curr->next;
    }
    printf("\n");
}

int main() {
    LRUCache* cache = createLRUCache(CACHE_CAPACITY);

    put(cache, 1, 100);
    put(cache, 2, 200);
    put(cache, 3, 300);
    put(cache, 4, 400);
    printCache(cache);

    printf("Get 2: %d\n", get(cache, 2));
    printCache(cache);

    put(cache, 5, 500);
    printCache(cache);

    printf("Get 1 (should be -1, evicted): %d\n", get(cache, 1));
    printf("Get 3: %d\n", get(cache, 3));
    printCache(cache);

    return 0;
}
