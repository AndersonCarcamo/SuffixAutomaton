#ifndef PROYECTOAED_TRIE_H
#define PROYECTOAED_TRIE_H

#include <string>
#include <unordered_map>

using namespace std;

// Node structure for Patricia Trie
struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

// Patricia Trie class
class Trie {
private:
    TrieNode* root;

    // Utility function to insert a word into the trie
    void insertUtil(TrieNode* node, const string& word) {
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->isEndOfWord = true;
    }

    // Utility function to search for a word in the trie
    bool searchUtil(TrieNode* node, const string& word) {
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                return false;
            }
            node = node->children[c];
        }
        return node->isEndOfWord;
    }

public:
    // Constructor
    Trie() {
        root = new TrieNode();
    }

    // Public method to insert a word into the trie
    void insert(const string& word) {
        insertUtil(root, word);
    }

    // Public method to search for a word in the trie
    bool search(const string& word) {
        return searchUtil(root, word);
    }
};

#endif //PROYECTOAED_TRIE_H
