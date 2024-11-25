cmake_minimum_required(VERSION 3.28)
project(Projekt_etap2)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")

add_executable(Projekt_etap2 main.cpp
        Algorithms/LowestCost.h
        Algorithms/LowestCost.cpp
        Utils/FileReader.h
        Utils/FileReader.cpp
        Algorithms/BFS.h
        Algorithms/BFS.cpp
        Algorithms/DFS.h
        Algorithms/DFS.cpp
        Utils/ConfigFile.h
        Utils/ConfigFile.cpp
        Utils/Queue.h
        Utils/Test.cpp
        Utils/Test.h
)
