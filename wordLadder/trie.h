#ifndef TRIE_H
#define TRIE_H

#include <string>

class Trie {
private:

public:
        void insert(std::string s);
        void del(std::string s);
        bool contains(std::string s);
};

#endif
