//
// Created by grons on 13.11.2024.
//

#ifndef ZADANIE2_CONFIGFILEHANDLER_H
#define ZADANIE2_CONFIGFILEHANDLER_H

#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include "FileReader.h"
#include "../Algorithms/BranchAndBound.h"
#include "Test.h"
#include "../Algorithms/DFS.h"
#include "../Algorithms/BFS.h"

class ConfigFile {
public:
    // Konstruktor klasy, przyjmuje nazwę pliku konfiguracyjnego
    ConfigFile(const std::string &filename);

    // Funkcja odpowiedzialna za parsowanie pliku konfiguracyjnego
    void parseConfig();


private:
    std::string filename;
    FileReader fileReader;
    Test test;
    BranchAndBound* bnb;
    BFS* bfs;
    DFS* dfs;

};


#endif //ZADANIE2_CONFIGFILEHANDLER_H