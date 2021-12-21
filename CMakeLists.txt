cmake_minimum_required(VERSION 3.10)
project(DictionaryTree)

find_package(PythonLibs REQUIRED)

find_package(SWIG REQUIRED COMPONENTS python)
if(SWIG_FOUND)
    message("SWIG found: ${SWIG_EXECUTABLE}")
    INCLUDE(${SWIG_USE_FILE})
    if(NOT SWIG_python_FOUND)
        message(WARNING "SWIG python bindings cannot be generated")
    endif()
endif()

include_directories(${PYTHON_INCLUDE_DIRS})
include_directories(.)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-O3)

set_property(SOURCE dictionary_tree.i PROPERTY CPLUSPLUS ON)
swig_add_library(dictionary_tree LANGUAGE python SOURCES dictionary_tree.i DictionaryTree.cpp WordSolver.cpp)
swig_link_libraries(dictionary_tree ${PYTHON_LIBRARIES})