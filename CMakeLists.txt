cmake_minimum_required(VERSION 3.10)
project(DictionaryTree)

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-O3)

add_executable(DictionaryTree main.cpp DictionaryTree.cpp WordSolver.cpp)
add_library(dictionary_tree.cpython-36m-x86_64-linux-gnu.so DictionaryTree.cpp WordSolver.cpp bind.cpp)
target_link_libraries(dictionary_tree.cpython-36m-x86_64-linux-gnu.so ${PYTHON_LIBRARIES})