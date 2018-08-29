#include "DictionaryTree.h"
#include <vector>
using namespace std;

bool DictionaryTree::find(string word) {
    CharacterNode* cur = this->root;
    for(auto iter: word) {
        if (cur->find(iter)) {
            cur = cur->children[iter];
        } else {
            return false;
        }
    }
    return cur->isWord;
}

void DictionaryTree::insert(string word) {
    CharacterNode* cur = this->root;
    for(auto iter: word) {
        if (cur->find(iter )) {
            cur = cur->children[iter];
        } else {
            this->nodeCnt++;
            cur = cur->children[iter] = new CharacterNode(iter, false);
        }
    }
    cur->isWord = true;
}

DictionaryTree::DictionaryTree() {
    this->root = new CharacterNode('\0', false);
}

DictionaryTree::~DictionaryTree() {
    vector<CharacterNode*> nodes;
    CharacterNode* cur;
    if (this->root)
    {
        nodes.push_back(this->root);
        while (!nodes.empty()) {
            cur = nodes.back();
            nodes.pop_back();
            for(auto iter: cur->children) {
                nodes.push_back(iter.second);
            }
            delete cur;
        }
    }
}
