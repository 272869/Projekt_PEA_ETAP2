#ifndef ZADANIE2_CONFIGFILEHANDLER_H
#define ZADANIE2_CONFIGFILEHANDLER_H

#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include <vector>
#include "FileReader.h"
#include "../Algorithms/BranchAndBound.h"
#include "Test.h"
#include "../Algorithms/DFS.h"
#include "../Algorithms/BFS.h"


class ConfigFile {
public:
    void parseConfig();

private:
    void handleGenerateMode();
    void handleTestMode(const std::string& dataType, const std::string& fileName, int size, const std::string& matrixType, const std::string& algorithm, const std::string& showOption);
    void executeAlgorithm(const std::string& matrixType, const std::string& algorithm);
    std::string filename;
    FileReader fileReader;
    Test test;
    BranchAndBound* bnb = nullptr;
    BFS* bfs = nullptr;
    DFS* dfs = nullptr;
};


#endif //ZADANIE2_CONFIGFILEHANDLER_H