//
// Created by archiemeng on 18-8-30.
//

#include "WordSolver.h"

vector <string> WordSolver::solve(vector < vector<char> > matrix) {
    vector<string> words;
    for (unsigned int i = 0; i < matrix.size(); ++i) {
        for (unsigned int j = 0; j < matrix[i].size(); ++j) {
            // i-dimensional iteration
            string tmp;
            CharacterNode *cur = this->root;
            for (unsigned int k = i;k < matrix.size();++k) {
                tmp.push_back(matrix[k][j]);
                if((cur->children.find(matrix[k][j])) != cur->children.end()) {
                    cur = cur->children[matrix[k][j]];
                    if (cur->isWord) {
                        words.push_back(tmp);
                    }
                } else {
                    break;
                }
            }
            if (!tmp.empty() && cur->isWord) {
                words.push_back(tmp);
            }

            // j-dimensional iteration
            tmp = "";
            cur = this->root;
            for (unsigned int k = j;k < matrix[i].size();++k) {
                tmp.push_back(matrix[i][k]);
                if((cur->children.find(matrix[i][k])) != cur->children.end()) {
                    cur = cur->children[matrix[i][k]];
                    if (cur->isWord) {
                        words.push_back(tmp);
                    }
                } else {
                    break;
                }
            }
            if (!tmp.empty() && cur->isWord) {
                words.push_back(tmp);
            }
        }
    }
    return words;
}
