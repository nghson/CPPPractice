#ifndef TRIE_H
#define TRIE_H

#include <string>
#include "Node.h"

class Trie {
public:
        Trie();
        Trie(const std::string& filename);

        void insert(const std::string& s);
        void remove(const std::string& s);
        bool contains(const std::string& s);

private:
        struct Node {
        private:
                Node* children[26];
        };

        Node* root;

};

#endif
