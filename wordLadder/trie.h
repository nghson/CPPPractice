#ifndef TRIE_H
#define TRIE_H

#include <string>
#include "Node.h"

class Trie {
public:
        Trie();
        Trie(const std::string& filename);
        ~Trie();

        bool insert(const std::string& s);
        void remove(const std::string& s);
        bool contains(const std::string& s);

private:
        class Node {
        public:
                Node()
                {
                        for (int i = 0; i < 26; ++i) {
                                children[i] = nullptr;
                        }
                }

                bool isLeaf()
                {
                        return childCount() == 0;
                }

                int childCount()
                {
                        int count = 0;
                        for (int i = 0; i < 26; i++) {
                                if (children[i] != nullptr) {
                                        count++;
                                }
                        }
                        return count;
                }
        private:
                Node* children[26];
        };

        Node* root;


        bool _insert(Node*& node, const std::string& word);
        void deleteTree();
};

#endif
