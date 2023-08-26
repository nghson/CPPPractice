#include <string>
#include <vector>
#include "trie.h"
#include "Node.h"

using std::string;

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
