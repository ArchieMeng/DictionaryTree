#ifndef DICTIONARYTREE
#define DICTIONARYTREE

#include<map>
#include <unordered_map>

using namespace std;

struct CharacterNode {
    char ch;
    bool isWord;
    unordered_map<char, CharacterNode*> children;
    CharacterNode(char ch, bool isWord) {
        this->ch = ch;
        this->isWord = isWord;
        this->children = unordered_map<char, CharacterNode*>();
    }

    bool find(char ch) {
        return this->children.find(ch) != this->children.end();
    }
};

class DictionaryTree {
public:
    bool find(string);
    void insert(string);
    int getNodeCnt() {return this->nodeCnt;}
    DictionaryTree();
    ~DictionaryTree();
private:
    CharacterNode* root;
    int nodeCnt = 0;
};

#endif