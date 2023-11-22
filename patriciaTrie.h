#ifndef PROYECTOAED_PATRICIATRIE_H
#define PROYECTOAED_PATRICIATRIE_H

#include <string>
#include <unordered_map>

using namespace std;

// Node structure for Patricia Trie
struct PatriciaTrieNode {
    unordered_map<string, PatriciaTrieNode*> children;
    bool isEndOfWord;
    string key;  // Key associated with the edge leading to this node

    PatriciaTrieNode() : isEndOfWord(false) {}
};

// Patricia Trie class
class PatriciaTrie {
private:
    PatriciaTrieNode* root;

    // Utility function to insert a word into the trie
    void insertUtil(PatriciaTrieNode* node, const string& word) {
        for (auto it = node->children.begin(); it != node->children.end(); ++it) {
            const string& edgeKey = it->first;
            int i = 0;
            while (i < edgeKey.size() && i < word.size() && edgeKey[i] == word[i]) {
                ++i;
            }

            if (i > 0) {
                // Split the edge
                string commonPrefix = edgeKey.substr(0, i);
                string remainingEdgeKey = edgeKey.substr(i);
                string remainingWord = word.substr(i);

                // Remove the old edge
                PatriciaTrieNode* child = it->second;
                node->children.erase(it);

                // Add the common prefix as a new edge
                node->children[commonPrefix] = new PatriciaTrieNode();
                node->children[commonPrefix]->key = commonPrefix;

                // Add the remaining parts as children of the new node
                node->children[commonPrefix]->children[remainingEdgeKey] = child;
                node->children[commonPrefix]->children[remainingWord] = new PatriciaTrieNode();
                node->children[commonPrefix]->children[remainingWord]->key = remainingWord;

                return;
            }
        }

        // If no common prefix was found, simply add a new edge
        node->children[word] = new PatriciaTrieNode();
        node->children[word]->key = word;
        node->children[word]->isEndOfWord = true;
    }

    // Utility function to search for a word in the trie
    bool searchUtil(PatriciaTrieNode* node, const string& word) {
        for (auto it = node->children.begin(); it != node->children.end(); ++it) {
            const string& edgeKey = it->first;
            if (word.find(edgeKey) == 0) {
                // Prefix match, follow the edge
                int edgeLength = edgeKey.size();
                string remainingWord = word.substr(edgeLength);

                if (remainingWord.empty()) {
                    // If the edge consumes the entire remaining word, check if it's the end of a word
                    return it->second->isEndOfWord;
                } else {
                    // Recursively search the next node
                    return searchUtil(it->second, remainingWord);
                }
            }
        }

        return false;
    }

public:
    // Constructor
    PatriciaTrie() {
        root = new PatriciaTrieNode();
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

#endif //PROYECTOAED_PATRICIATRIE_H
