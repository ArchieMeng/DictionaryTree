#include <iostream>
#include <string>
#include <fstream>
#include "DictionaryTree.h"
#include <ctime>
#include <vector>
#include "WordSolver.h"
using namespace std;

int main() {
    DictionaryTree fuck;
//    ifstream f("words.txt");
    ifstream f("words_alpha.txt");
    int cnt = 0, ansCnt = 0;
    clock_t dur1 = 0, dur2 = 0;
    clock_t t;
    for( std::string line; getline( f, line ); )
    {
        line.pop_back();
        t = clock();
        fuck.insert(line);
        cnt++;
        dur1 += clock() - t;
    }

    cout << fuck.find("ant") << endl;
    cout << fuck.find("asdad") << endl;
    f.clear();
    f.seekg(0, ios::beg);

    for ( std::string line; getline( f, line ); )
    {
        line.pop_back();
        t = clock();
        ansCnt += fuck.find(line);
        dur2 += clock() - t;
    }

//    while (f >> buf) {
//        cout << buf;
//    }
    cout << cnt << '\t' << ansCnt << endl;
    cout << (cnt == ansCnt) << endl;

    cout << "insert time:" << ((float) dur1 / CLOCKS_PER_SEC) << 's' <<  endl;
    cout << "insert time(per operation):" << ((float) dur1 / CLOCKS_PER_SEC / cnt) << 's' <<  endl;
    cout << "search time:" << ((float) dur2 / CLOCKS_PER_SEC) << 's' <<  endl;
    cout << "search time(per operation):" << ((float) dur2 / CLOCKS_PER_SEC / cnt) << 's' <<  endl;
    cout << "node count:" << fuck.getNodeCnt() << endl;

    // try Word Solver
    vector< vector<char> > m = {
        {'m', 'e', 'r'},
        {'a', 'p', 'i'},
        {'y', 'e', 'p'}
    };
    WordSolver solver;
    f.clear();
    f.seekg(0, ios::beg);

    for ( std::string line; getline( f, line ); )
    {
        line.pop_back();
        solver.insert(line);
    }

    t = clock();
    for (const auto &iter: solver.solve(m)) {
        cout << iter << endl;
    }
    cout << "solve time:" << (float) (clock() - t) / CLOCKS_PER_SEC << 's' << endl;

    getchar();

    return 0;
}
