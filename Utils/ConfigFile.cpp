#include "ConfigFile.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

void ConfigFile::parseConfig() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku konfiguracyjnego!" << std::endl;
        return;
    }
    std::unordered_map<std::string, std::string> config;
    std::string line;

    while (std::getline(file, line)) {
        size_t commentPos = line.find('#');
        if (commentPos != std::string::npos) line = line.substr(0, commentPos);
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);
        if (line.empty()) continue;
        std::istringstream stream(line);
        std::string key, value;
        if (std::getline(stream, key, ':') && std::getline(stream, value)) {
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            config[key] = value;
        }
    }
    file.close();
    const auto& mode = config["mode"];
    if (mode == "generate") handleGenerateMode();
    else if (mode == "test") handleTestMode(config["data"], config["fileName"], std::stoi(config["size"]), config["matrixType"], config["algorithm"], config["show"]);
}

void ConfigFile::handleGenerateMode() {
    std::cout << "Tryb generowania danych...\n";
    test.startTests();
}

void ConfigFile::handleTestMode(const std::string& dataType, const std::string& fileName, int size, const std::string& matrixType, const std::string& algorithm, const std::string& showOption) {
    if (dataType == "file") {
        std::cout << "Wczytuje macierz z pliku: " << fileName << std::endl;
        fileReader.loadFromFile(fileName);
    } else if (dataType == "random") {
        std::cout << "Generuje losowa macierz o rozmiarze: " << size << std::endl;
        if (matrixType == "s") fileReader.loadRandomSymetricData(size, 0);
        else if (matrixType == "a") fileReader.loadRandomData(size, 0);
    }
    if (showOption == "yes") {
        std::cout << "Macierz wejsciowa:\n";
        fileReader.showTab();
    }
    executeAlgorithm(matrixType, algorithm);
}

void ConfigFile::executeAlgorithm(const std::string& matrixType, const std::string& algorithm) {
    auto startTimer = []() { return std::chrono::high_resolution_clock::now(); };
    auto endTimer = [](const auto& startTime) {
        return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - startTime).count();
    };

    if (matrixType == "s") {
        if (algorithm == "BFS") {
            bfs = new BFS(fileReader.size);
            std::cout << "Algorytm: Branch and Bound BFS\n";
            auto startTime = startTimer();
            bfs->bnb_bfs_run(fileReader.tab, 0); // Wywołanie algorytmu
            auto duration = endTimer(startTime);
            bfs->showThePath(0, fileReader.tab);
            std::cout << "Czas wykonania: " << duration << " [us]" << std::endl;
        } else if (algorithm == "DFS") {
            dfs = new DFS(fileReader.size);
            std::cout << "Algorytm: Branch and Bound DFS\n";
            auto startTime = startTimer();
            dfs->bnb_dfs_run(fileReader.tab, 0); // Wywołanie algorytmu
            auto duration = endTimer(startTime);
            dfs->showThePath(0, fileReader.tab);
            std::cout << "Czas wykonania: " << duration << " [us]" << std::endl;
        } else if (algorithm == "LC") {
            bnb = new BranchAndBound(fileReader.size);
            std::cout << "Algorytm: Branch and Bound Lowest Cost\n";
            auto startTime = startTimer();
            bnb->bnb_run(fileReader.tab, 0); // Wywołanie algorytmu
            auto duration = endTimer(startTime);
            bnb->showThePath(0, fileReader.tab);
            std::cout << "Czas wykonania: " << duration << " [us]" << std::endl;
        }
    } else if (matrixType == "a") {
        if (algorithm == "BFS") {
            bfs = new BFS(fileReader.size);
            std::cout << "Algorytm: Branch and Bound BFS\n";
            auto startTime = startTimer();
            bfs->startFromEachVertex(fileReader.tab); // Wywołanie algorytmu
            auto duration = endTimer(startTime);
            bfs->showTheShortestPath(fileReader.tab);
            std::cout << "Czas wykonania: " << duration << " [us]" << std::endl;
        } else if (algorithm == "DFS") {
            dfs = new DFS(fileReader.size);
            std::cout << "Algorytm: Branch and Bound DFS\n";
            auto startTime = startTimer();
            dfs->startFromEachVertex(fileReader.tab); // Wywołanie algorytmu
            auto duration = endTimer(startTime);
            dfs->showTheShortestPath(fileReader.tab);
            std::cout << "Czas wykonania: " << duration << " [us]" << std::endl;
        } else if (algorithm == "LC") {
            bnb = new BranchAndBound(fileReader.size);
            std::cout << "Algorytm: Branch and Bound Lowest Cost\n";
            auto startTime = startTimer();
            bnb->startFromEachVertex(fileReader.tab); // Wywołanie algorytmu
            auto duration = endTimer(startTime);
            bnb->showTheShortestPath(fileReader.tab);
            std::cout << "Czas wykonania: " << duration << " [us]" << std::endl;
        }
    }
}
