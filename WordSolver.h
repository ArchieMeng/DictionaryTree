//
// Created by archiemeng on 18-8-30.
//

#ifndef WORDSOLVER_H
#define WORDSOLVER_H

#include <vector>
#include <string>
#include "DictionaryTree.h"

using namespace std;

class WordSolver : public DictionaryTree {
public:
    vector<string> solve(vector<vector<char>>);
};


#endif //DICTIONARYTREE_WORDSOLVER_H
