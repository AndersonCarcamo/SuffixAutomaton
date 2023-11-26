cmake_minimum_required(VERSION 3.26)
project(SuffixAutomaton)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(SuffixAutomaton
        generadorPalabras.h
        main.cpp
        patriciaTrie.h
        suffixAutomaton.h
        trie.h
        suffixAutomatonNO.h
        circularArrayMod.h
        nodeMod.h)
