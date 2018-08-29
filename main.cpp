#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include "DictionaryTree.h"
#include <ctime>
using namespace std;

int main() {
    DictionaryTree fuck;
//    ifstream f("words.txt");
    ifstream f("words_alpha.txt");
    int cnt = 0, ansCnt = 0;

    clock_t t1 = clock();
    for( std::string line; getline( f, line ); )
    {
        line.pop_back();
        fuck.insert(line);
        cnt++;
    }
    clock_t t2 = clock();

    cout << fuck.find("ant") << endl;
    cout << fuck.find("asdad") << endl;
    f.clear();
    f.seekg(0, ios::beg);

    clock_t t3 = clock();
    for ( std::string line; getline( f, line ); )
    {
        line.pop_back();
        ansCnt += fuck.find(line);
    }
    clock_t t4 = clock();

//    while (f >> buf) {
//        cout << buf;
//    }
    cout << cnt << '\t' << ansCnt << endl;
    cout << (cnt == ansCnt) << endl;

    clock_t dur1 = t2 - t1, dur2 = t4 - t3;
    cout << "insert time:" << ((float) dur1 / CLOCKS_PER_SEC) << 's' <<  endl;
    cout << "insert time(per operation):" << ((float) dur1 / CLOCKS_PER_SEC / cnt) << 's' <<  endl;
    cout << "search time:" << ((float) dur2 / CLOCKS_PER_SEC) << 's' <<  endl;
    cout << "search time(per operation):" << ((float) dur2 / CLOCKS_PER_SEC / cnt) << 's' <<  endl;
    cout << "node count:" << fuck.getNodeCnt() << endl;
    return 0;
}