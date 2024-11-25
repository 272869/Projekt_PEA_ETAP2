#include "ConfigFile.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

void ConfigFile::parseConfig() {
    // Otwiera plik konfiguracyjny do odczytu
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku konfiguracyjnego!" << std::endl;
        return; // Jeśli nie udało się otworzyć pliku, kończy działanie funkcji
    }

    std::unordered_map<std::string, std::string> config; // Słownik do przechowywania konfiguracji
    std::string line; // Do przechowywania kolejnych linii z pliku

    while (std::getline(file, line)) {
        // Usuwa komentarze i białe znaki na początku i końcu linii
        size_t commentPos = line.find('#');
        if (commentPos != std::string::npos) line = line.substr(0, commentPos); // Obcięcie komentarza
        line.erase(0, line.find_first_not_of(" \t")); // Usunięcie białych znaków z przodu
        line.erase(line.find_last_not_of(" \t") + 1); // Usunięcie białych znaków z tyłu
        if (line.empty()) continue; // Pominięcie pustych linii

        std::istringstream stream(line); // Strumień do podzielenia linii na klucz i wartość
        std::string key, value;
        if (std::getline(stream, key, ':') && std::getline(stream, value)) {
            // Usunięcie białych znaków wokół klucza i wartości
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            config[key] = value; // Dodanie pary klucz-wartość do mapy
        }
    }
    file.close(); // Zamknięcie pliku

    // Pobiera tryb działania z konfiguracji i wywołuje odpowiednią funkcję
    const auto& mode = config["mode"];
    if (mode == "generate")
        handleGenerateMode();
    else if (mode == "test")
        handleTestMode(config["data"], config["fileName"], std::stoi(config["size"]), config["matrixType"], config["algorithm"], config["show"]);
}

void ConfigFile::handleGenerateMode() {
    std::cout << "Tryb generowania danych...\n";
    test.startTests();
}

void ConfigFile::handleTestMode(const std::string& dataType, const std::string& fileName, int size, const std::string& matrixType, const std::string& algorithm, const std::string& showOption) {
    if (dataType == "file") {
        // Wczytanie macierzy z pliku
        std::cout << "Wczytuje macierz z pliku: " << fileName << std::endl;
        fileReader.loadFromFile(fileName);
    } else if (dataType == "random") {
        // Generowanie losowej macierzy
        std::cout << "Generuje losowa macierz o rozmiarze: " << size << std::endl;
        if (matrixType == "s")
            fileReader.loadRandomSymetricData(size, 0); // Symetryczna macierz
        else if (matrixType == "a")
            fileReader.loadRandomData(size, 0); // Ogólna macierz
    }

    if (showOption == "yes") {
        // Wyświetlenie macierzy, jeśli wybrano taką opcję
        std::cout << "Macierz wejsciowa:\n";
        fileReader.showTab();
    }

    executeAlgorithm(matrixType, algorithm); // Wywołanie algorytmu
}


void ConfigFile::executeAlgorithm(const std::string& matrixType, const std::string& algorithm) {
    auto startTimer = []() { return std::chrono::high_resolution_clock::now(); };
    auto endTimer = [](const auto& startTime) {
        return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - startTime).count();
    };

    if (matrixType == "s") {
        if (algorithm == "BFS") {
            bfs = new BFS(fileReader.size);
            std::cout << "BFS\n";
            auto startTime = startTimer();
            bfs->bnb_bfs_run(fileReader.tab, 0); // Wywołanie algorytmu
            auto duration = endTimer(startTime);
            //bfs->showThePath(fileReader.tab);
            std::cout << "Czas wykonania: " << duration << " [us]" << std::endl;
        } else if (algorithm == "DFS") {
            dfs = new DFS(fileReader.size);
            std::cout << "DFS\n";
            auto startTime = startTimer();
            dfs->bnb_dfs_run(fileReader.tab, 0); // Wywołanie algorytmu
            auto duration = endTimer(startTime);
            //dfs->showThePath(fileReader.tab);
            std::cout << "Czas wykonania: " << duration << " [us]" << std::endl;
        } else if (algorithm == "LC") {
            lc = new LowestCost(fileReader.size);
            std::cout << "Lowest Cost\n";
            auto startTime = startTimer();
            lc->bnb_lc_run(fileReader.tab, 0); // Wywołanie algorytmu
            auto duration = endTimer(startTime);
            //lc->showThePath(fileReader.tab);
            std::cout << "Czas wykonania: " << duration << " [us]" << std::endl;
        }
    } else if (matrixType == "a") {
        if (algorithm == "BFS") {
            bfs = new BFS(fileReader.size);
            std::cout << "BFS\n";
            auto startTime = startTimer();
            bfs->startFromEachVertex(fileReader.tab); // Wywołanie algorytmu
            auto duration = endTimer(startTime);
            //bfs->showTheShortestPath();
            std::cout << "Czas wykonania: " << duration << " [us]" << std::endl;
        } else if (algorithm == "DFS") {
            dfs = new DFS(fileReader.size);
            std::cout << "DFS\n";
            auto startTime = startTimer();
            dfs->startFromEachVertex(fileReader.tab); // Wywołanie algorytmu
            auto duration = endTimer(startTime);
            //dfs->showTheShortestPath();
            std::cout << "Czas wykonania: " << duration << " [us]" << std::endl;
        } else if (algorithm == "LC") {
            lc = new LowestCost(fileReader.size);
            std::cout << "Lowest Cost\n";
            auto startTime = startTimer();
            lc->startFromEachVertex(fileReader.tab); // Wywołanie algorytmu
            auto duration = endTimer(startTime);
            //lc->showTheShortestPath();
            std::cout << "Czas wykonania: " << duration << " [us]" << std::endl;
        }
    }
}
