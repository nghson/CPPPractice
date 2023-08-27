#include <string>
#include <vector>
#include <cctype>
#include "trie.h"
#include "Node.h"

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

}

void Trie::remove(const string& s)
{

}

bool Trie::contains(const string& s)
{

}

bool _insert(Node*& node, const string& word)
{

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
