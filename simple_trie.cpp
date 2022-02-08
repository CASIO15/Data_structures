#include <iostream>
#include <cassert>

using namespace std;

constexpr int ascii_range = 26;

class Trie {
private:
    struct node {
        struct node* children[ascii_range];
        bool isEndOfWord;

        node()
        {
            for (auto& i : children)
                i = nullptr;
            isEndOfWord = false;
        }
    };

    node* t_node;

    static void dispatchInsert(node** node, string& data);
    static bool searchWord(node* node, string& key);
    static void dispatchRemove(node* node, string& key);
    static inline int letterOffset(char ch);
    static void dispatchDisplayTrie(node* node, string res = "", int offset = 0);
    static void deleteAll(node* node, int offset = 0);

public:

    Trie()
    {
        t_node = nullptr;
    }

    void insert(string& data);
    bool search(string& key);
    void dump();
    void remove(string& key);
    ~Trie();
};

int Trie::letterOffset(char ch)
{
    return static_cast<int>(ch) - static_cast<int>('a');
}

void Trie::dispatchInsert(node** node, string& data)
{
    if (*node == nullptr)
        *node = new Trie::node();

    Trie::node* crawler = *node;

    for (auto& ch : data) {
        int offset = Trie::letterOffset(ch);

        if (!crawler->children[offset])
            crawler->children[offset] = new Trie::node;
        crawler = crawler->children[offset];
    }

    crawler->isEndOfWord = true;
}

void Trie::insert(string& data)
{
    this->dispatchInsert(&this->t_node, data);
}

bool Trie::searchWord(node* node, string& key)
{
    assert(node != nullptr);

    Trie::node* crawler = node;

    for (auto& ch : key) {
        int offset = Trie::letterOffset(ch);

        if (crawler->children[offset] != nullptr)
            crawler = crawler->children[offset];
        else
            return false;
    }

    if (crawler->isEndOfWord)
        return true;
    return false;
}

bool Trie::search(string& key)
{
    return this->searchWord(this->t_node, key);
}

void Trie::dispatchDisplayTrie(node* node, string res, int offset)
{
    if (node->isEndOfWord) {
        res.resize(offset);
        cout << res << '\n';
    }

    for (int i = 0; i < ascii_range; i++) {
        if (node->children[i]) {
            res.insert(res.begin() + offset, static_cast<char>(i + 'a'));
            Trie::dispatchDisplayTrie(node->children[i], res, offset + 1);
        }
    }
}

void Trie::dump()
{
    this->dispatchDisplayTrie(this->t_node);
}

void Trie::dispatchRemove(node* node, string& key)
{
    if (!searchWord(node, key)) {
        cout << "Error: key is not present\n";
        return;
    }

    Trie::node* crawler = node;
    int offset;

    for (auto& ch : key) {
        offset = Trie::letterOffset(ch);

        if (crawler->children[offset] != nullptr) {
            crawler = crawler->children[offset];
            delete crawler->children[offset];
        }
    }

    crawler->isEndOfWord = false;
}

void Trie::remove(string& key)
{
    this->dispatchRemove(this->t_node, key);
}

void Trie::deleteAll(node* node, int offset)
{
    if (node->isEndOfWord) {
        return;
    }

    for (int i = 0; i < ascii_range; i++) {
        if (node->children[i]) {
            Trie::deleteAll(node->children[i], offset + 1);
            delete node->children[i];
            node->children[i] = nullptr;
        }
    }
}

Trie::~Trie()
{
    this->deleteAll(t_node);
    this->t_node = nullptr;
}


int main()
{

    string CppLangKeywords[] = { "int", "char", "void", "main", "return", "struct", "class", "using", "namespace", "namespaces" };
    Trie trie;

    for (auto& word : CppLangKeywords)
        trie.insert(word);

    trie.dump();

    cout << "\n\n";

    cout << "Removing \'" << CppLangKeywords[7] << "\' from trie\n";
    trie.remove(CppLangKeywords[7]);
    cout << trie.search(CppLangKeywords[7]) << endl;

    trie.dump();

    return 0;
}
