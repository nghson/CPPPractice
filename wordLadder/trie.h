#ifndef TRIE_H
#define TRIE_H

#include <string>

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
                        _isWord = false;
                        for (int i = 0; i < 26; ++i) {
                                children[i] = nullptr;
                        }
                }

                Node*& child(char c)
                {
                        return children[c - 'a'];
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

                bool isWord()
                {
                        return _isWord;
                }

                void setWord(bool v)
                {
                        _isWord = v;
                }

        private:
                Node* children[26];
                bool _isWord;
        };

        Node* root;


        bool _insert(Node*& node, const std::string& word);
        void deleteTree();
};

#endif
