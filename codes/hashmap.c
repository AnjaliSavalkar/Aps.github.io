#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000

typedef struct Node {
    int key;
    char value[100];
    struct Node* next;
} Node;

Node* hashTable[SIZE];

int hash(int key) {
    return key % SIZE;
}

void insert(int key, char* value) {
    int index = hash(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    strcpy(newNode->value, value);
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

char* search(int key) {
    int index = hash(key);
    Node* temp = hashTable[index];
    while (temp) {
        if (temp->key == key)
            return temp->value;
        temp = temp->next;
    }
    return NULL;
}

void update(int key, char* newValue) {
    int index = hash(key);
    Node* temp = hashTable[index];
    while (temp) {
        if (temp->key == key) {
            strcpy(temp->value, newValue);
            return;
        }
        temp = temp->next;
    }
}

void display() {
    for (int i = 0; i < SIZE; i++) {
        Node* temp = hashTable[i];
        while (temp) {
            printf("Key: %d, Value: %s\n", temp->key, temp->value);
            temp = temp->next;
        }
    }
}

int main() {
    insert(1, "Segment1");
    insert(2, "Segment2");
    insert(1001, "Segment3");
    printf("Search Key 2: %s\n", search(2));
    update(2, "Segment2_updated");
    printf("After Update Key 2: %s\n", search(2));
    display();
    return 0;
}
