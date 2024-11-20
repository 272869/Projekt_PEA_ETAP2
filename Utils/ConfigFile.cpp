//
// Created by grons on 13.11.2024.
//

#include "ConfigFile.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

ConfigFile::ConfigFile(const std::string &filename) : filename(filename) {}

void ConfigFile::parseConfig() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku konfiguracyjnego!" << std::endl;
        return;
    }

    std::string line, key, value;
    std::string mood, dataType, fileName, matrixType, algorithm, showOption;
    int size = 0;

    while (std::getline(file, line)) {
        // Usuń komentarz po znaku '#', jeśli istnieje
        size_t commentPos = line.find('#');
        if (commentPos != std::string::npos) {
            line = line.substr(0, commentPos);
        }

        // Usuń białe znaki na początku i końcu linii
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        // Pomiń puste linie
        if (line.empty()) {
            continue;
        }

        // Rozdzielenie klucza i wartości po dwukropku
        std::istringstream stream(line);
        if (std::getline(stream, key, ':') && std::getline(stream, value)) {
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);

            if (key == "mood") {
                mood = value;
            } else if (key == "data") {
                dataType = value;
            } else if (key == "fileName") {
                fileName = value;
            } else if (key == "matrixType") {
                matrixType = value;
            } else if (key == "size") {
                size = std::stoi(value);
            } else if (key == "show") {
                showOption = value;
            } else if (key == "algorithm") {
                algorithm = value;
            }
        }
    }

    // Obsługa trybu "generate" lub "test"
    if (mood == "generate") {
        std::cout << "Tryb generowania danych...\n";
        //test.startTests();
    } else if (mood == "test") {
        std::cout << "Tryb testowy...\n";

        if (dataType == "file") {
            std::cout << "Wczytuje macierz z pliku: " << fileName << std::endl;
            fileReader.loadFromFile(fileName);
        } else if (dataType == "random") {
            std::cout << "Generuje losowa macierz o rozmiarze: " << size << std::endl;
            if (matrixType == "s") {
                fileReader.loadRandomSymetricData(size, 0);
            } else if (matrixType == "a") {
                fileReader.loadRandomData(size, 0);
            }
        }

        if (showOption == "yes") {
            std::cout << "Macierz wejsciowa:\n";
            fileReader.showTab();
        }

        // Wybór algorytmu
        if (matrixType == "s") {
            if (algorithm == "BFS") {
                std::cout<<"algorytm: Branch and Bound BFS"<<std::endl;
                bfs = new BFS(fileReader.size);
                const auto startTime = std::chrono::high_resolution_clock::now();
                bfs->bnb_bfs_run(fileReader.tab,0);

                const auto endTime = std::chrono::high_resolution_clock::now();
                bfs->showThePath(0, fileReader.tab);
                const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
                std::cout << "Czas wykonania: " << duration << " [us]" << std::endl;
            } else if (algorithm == "DFS") {
                std::cout<<"algorytm: Branch and Bound DFS"<<std::endl;
                dfs = new DFS(fileReader.size);
                const auto startTime = std::chrono::high_resolution_clock::now();
                dfs->bnb_dfs_run(fileReader.tab,0);

                const auto endTime = std::chrono::high_resolution_clock::now();
                dfs->showThePath(0,fileReader.tab);
                const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
                std::cout << "Czas wykonania: " << duration << " [us]" << std::endl;
            } else if (algorithm == "LC") {
                std::cout<<"algorytm: Branch and Bound Lowest Cost"<<std::endl;
                bnb = new BranchAndBound(fileReader.size);
                const auto startTime = std::chrono::high_resolution_clock::now();
                bnb->bnb_run(fileReader.tab,0);

                const auto endTime = std::chrono::high_resolution_clock::now();
                bnb->showThePath(0,fileReader.tab);
                const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
                std::cout << "Czas wykonania: " << duration << " [us]" << std::endl;
            }
        } else if (matrixType == "a") {
            if (algorithm == "BFS") {
                std::cout<<"algorytm: Branch and Bound BFS"<<std::endl;
                bfs = new BFS(fileReader.size);
                const auto startTime = std::chrono::high_resolution_clock::now();
                bfs->startFromEachVertex(fileReader.tab);

                const auto endTime = std::chrono::high_resolution_clock::now();
                bfs->showTheShortestPath(fileReader.tab);
                const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
                std::cout << "Czas wykonania: " << duration << " [us]" << std::endl;
            } else if (algorithm == "DFS") {
                std::cout<<"algorytm: Branch and Bound DFS"<<std::endl;
                dfs = new DFS(fileReader.size);
                const auto startTime = std::chrono::high_resolution_clock::now();
                dfs->startFromEachVertex(fileReader.tab);

                const auto endTime = std::chrono::high_resolution_clock::now();
                dfs->showTheShortestPath(fileReader.tab);
                const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
                std::cout << "Czas wykonania: " << duration << " [us]" << std::endl;
            } else if (algorithm == "LC") {
                std::cout<<"algorytm: Branch and Bound lowest cost"<<std::endl;
                bnb = new BranchAndBound(fileReader.size);
                const auto startTime = std::chrono::high_resolution_clock::now();
                bnb->startFromEachVertex(fileReader.tab);

                const auto endTime = std::chrono::high_resolution_clock::now();
                bnb->showTheShortestPath(fileReader.tab);
                const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
                std::cout << "Czas wykonania: " << duration << " [us]" << std::endl;
            }
        }
        fileReader.dealocate();
    }
    file.close();
}

