//Matthew Cardona
//Lab Assignment 10
//4-19-24
//COP3502C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie node structure
struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    int count; // Number of occurrences
};

// Initialize a TrieNode
struct TrieNode* createNode() {
    struct TrieNode* newNode = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    if (newNode) {
        newNode->count = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++)
            newNode->children[i] = NULL;
    }
    return newNode;
}

// Inserts a word into the trie
void insert(struct TrieNode* root, char* word) {
    struct TrieNode* current = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (current->children[index] == NULL)
            current->children[index] = createNode();
        current = current->children[index];
    }
    current->count++;
}

// Counts occurrences of a word in the trie
int numberOfOccurrences(struct TrieNode* root, char* word) {
    struct TrieNode* current = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (current->children[index] == NULL)
            return 0; // Word not found
        current = current->children[index];
    }
    return current->count;
}

// Deallocates memory for the trie
void deallocateTrie(struct TrieNode* root) {
    if (root == NULL)
        return;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        deallocateTrie(root->children[i]);
    free(root);
}

// Reads words from dictionary file
int readDictionary(char* filename, char** pInWords) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        exit(1);
    }

    int numWords = 0;
    char word[100]; // Assuming maximum word length is 99 characters

    while (fscanf(file, "%s", word) != EOF) {
        pInWords[numWords] = strdup(word); // Copy the word into pInWords
        numWords++;
    }

    fclose(file);
    return numWords;
}

int main(void) {
    char* inWords[256];

    // Read the number of words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i) {
        printf("%s\n", inWords[i]);
    }

    // Create and populate the trie
    struct TrieNode* root = createNode();
    for (int i = 0; i < numWords; i++) {
        insert(root, inWords[i]);
    }

    // Test some words
    char* pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(root, pWords[i]));
    }

    // Deallocate the trie
    deallocateTrie(root);

    return 0;
}
