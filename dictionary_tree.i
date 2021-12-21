%module dictionary_tree
// to use std::string
%include "std_string.i"
// to use std::map
%include "std_map.i"
// to use std::vector
%include "std_vector.i"
namespace std{
    %template(VecChar) vector<char>;
    %template(VecVecChar) vector<vector<char>>;
    %template(VecString) vector<string>;
};
%{
    #include "DictionaryTree.h"
    #include "WordSolver.h"
%}

%include "DictionaryTree.h"
%include "WordSolver.h"