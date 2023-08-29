#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include "trie.h"

using std::cout;
using std::string;

bool clean(string& s);

Trie::Trie()
{
        root = nullptr;
}

Trie::Trie(const string& filename)
{

}

Trie::~Trie()
{
        root = nullptr;
        deleteTree();
}

void Trie::deleteTree()
{

}

bool Trie::insert(const string& s)
{
        if (s.empty()) {
                return false;
        }

        string w = s;
        if (!clean(w)) {
                return false;
        }

        return _insert(root, w, w);
}

void Trie::remove(const string& s)
{

}

bool Trie::contains(const string& s)
{

}

bool Trie::_insert(Node*& node, const string& word, const string& original)
{
        if (!node) {
                node = new Node();
        }

        if (word.empty()) {
                node->isWord();
                if (node->isWord()) {
                        return false;
                }
                node->setWord(true);
                _allWords.insert(original);
                return true;
        }

        return _insert(node->child(word[0]), word.substr(1), original);
}

bool clean(string& s)
{
        const size_t l = s.size();
        size_t ind = 0;
        for (size_t i = 0; i < l; ++i) {
                auto c = std::tolower(s[i]);
                if (c < 'a' || c > 'z') {
                        return false;
                }
                s[ind++] = c;
        }
        if (ind != l) {
                s.erase(ind, l - ind);
        }
        return true;
}

void Trie::printAll()
{
        for (auto i = _allWords.begin(); i != _allWords.end(); ++i) {
                cout << *i << '\n';
        }
}