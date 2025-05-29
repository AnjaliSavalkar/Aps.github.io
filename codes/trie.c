#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

typedef struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    int isEndOfWord;
} TrieNode;

TrieNode* createNode() {
    TrieNode* newNode = (TrieNode*)malloc(sizeof(TrieNode));
    newNode->isEndOfWord = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

void insert(TrieNode* root, const char* word) {
    TrieNode* currentNode = root;
    int index;

    for (int i = 0; i < strlen(word); i++) {
        index = word[i] - 'a';
        if (currentNode->children[index] == NULL) {
            currentNode->children[index] = createNode();
        }
        currentNode = currentNode->children[index];
    }
    currentNode->isEndOfWord = 1;
}

void searchPrefix(TrieNode* root, char* currentPrefix, int level) {
    if (root->isEndOfWord) {
        currentPrefix[level] = '\0';
        printf("%s\n", currentPrefix);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i] != NULL) {
            currentPrefix[level] = 'a' + i;
            searchPrefix(root->children[i], currentPrefix, level + 1);
        }
    }
}

void getSuggestions(TrieNode* root, const char* prefix) {
    TrieNode* currentNode = root;
    int index;
    int length = strlen(prefix);
    char currentPrefix[length + 100]; // extra buffer for suggestions

    for (int i = 0; i < length; i++) {
        index = prefix[i] - 'a';
        if (currentNode->children[index] == NULL) {
            printf("No suggestions found.\n");
            return;
        }
        currentNode = currentNode->children[index];
    }

    strcpy(currentPrefix, prefix);
    searchPrefix(currentNode, currentPrefix, length);
}

int main() {
    TrieNode* root = createNode();
    insert(root, "apple");
    insert(root, "app");
    insert(root, "bat");
    insert(root, "ball");
    insert(root, "batman");
    insert(root, "banana");

    printf("Autocomplete Suggestions for 'ba':\n");
    getSuggestions(root, "ba");

    printf("\nAutocomplete Suggestions for 'app':\n");
    getSuggestions(root, "app");

    return 0;
}
