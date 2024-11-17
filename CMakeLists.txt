cmake_minimum_required(VERSION 3.28)
project(Projekt_etap2)

set(CMAKE_CXX_STANDARD 17)

add_executable(Projekt_etap2 main.cpp
        Algorithms/BranchAndBound.h
        Algorithms/BranchAndBound.cpp
        Utils/Matrix.h
        Utils/Matrix.cpp
        Utils/FileReader.h
        Utils/FileReader.cpp
        Utils/PriorityQueue.h
        Utils/FIFOQueue.h
        Algorithms/BFS.h
        Algorithms/BFS.cpp
)
