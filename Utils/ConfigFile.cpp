////
//// Created by pitko on 19.11.2024.
////
//
//#include "ConfigFile.h"
////
//// Created by grons on 13.11.2024.
////
//
//#include <fstream>
//#include <iostream>
//#include <sstream>
//#include <vector>
//#include <string>
//#include "ConfigFile.h"
//
//ConfigFile::ConfigFile(const std::string &filename) : filename(filename) {}
//
//void ConfigFile::parseConfig() {
//    std::ifstream file(filename);
//    if (!file.is_open()) {
//        std::cerr << "Nie można otworzyć pliku konfiguracyjnego!" << std::endl;
//        return;
//    }
//
//    std::string line, key, value;
//    std::string mood, dataType, fileName, matrixType, algorithm, showOption;
//    int iterations = 0, size = 0;
//    std::vector<int> sizeVertex;
//
//    while (std::getline(file, line)) {
//        // Usuń komentarz po znaku '#', jeśli istnieje
//        size_t commentPos = line.find('#');
//        if (commentPos != std::string::npos) {
//            line = line.substr(0, commentPos);
//        }
//
//        // Usuń białe znaki na początku i końcu linii
//        line.erase(0, line.find_first_not_of(" \t"));
//        line.erase(line.find_last_not_of(" \t") + 1);
//
//        // Pomiń puste linie
//        if (line.empty()) {
//            continue;
//        }
//
//        // Rozdzielenie klucza i wartości po dwukropku
//        std::istringstream stream(line);
//        if (std::getline(stream, key, ':') && std::getline(stream, value)) {
//            value.erase(0, value.find_first_not_of(" \t"));
//            value.erase(value.find_last_not_of(" \t") + 1);
//
//            if (key == "mood") {
//                mood = value;
//            } else if (key == "data") {
//                dataType = value;
//            } else if (key == "fileName") {
//                fileName = value;
//            } else if (key == "matrixType") {
//                matrixType = value;
//            } else if (key == "size") {
//                size = std::stoi(value);
//            } else if (key == "show") {
//                showOption = value;
//            } else if (key == "algorithm") {
//                algorithm = value;
//            } else if (key == "iterations") {
//                iterations = std::stoi(value);
//            } else if (key == "sizeVertex") {
//                std::istringstream verticesStream(value);
//                std::string vertex;
//                while (std::getline(verticesStream, vertex, ',')) {
//                    sizeVertex.push_back(std::stoi(vertex));
//                }
//            }
//        }
//    }
//
//
//    // Obsługa trybu "generate" lub "test"
//    if (mood == "generate") {
//        std::cout << "Tryb generowania danych...\n";
//        generator.generate(iterations, sizeVertex);
//    } else if (mood == "test") {
//        std::cout << "Tryb testowy...\n";
//
//        int** matrix = nullptr;
//        if (dataType == "file") {
//            std::cout << "Wczytuje macierz z pliku: " << fileName << std::endl;
//            matrix = dataReader.readFile(fileName, size);
//        } else if (dataType == "random") {
//            std::cout << "Generuje losowa macierz o rozmiarze: " << size << std::endl;
//            if (matrixType == "s") {
//                matrix = dataReader.generateRandomSymmetricalData(size);
//            } else if (matrixType == "a") {
//                matrix = dataReader.generateRandomAsymmetricalData(size);
//            }
//        }
//
//        if (showOption == "yes" && matrix != nullptr) {
//            std::cout << "Macierz wejsciowa:\n";
//            for (int i = 0; i < size; i++) {
//                for (int j = 0; j < size; j++) {
//                    std::cout << matrix[i][j] << " ";
//                }
//                std::cout << std::endl;
//            }
//        }
//
//        // Wybór algorytmu
//        Result result;
//        if (matrixType == "s") {
//            if (algorithm == "BAndBBFS") {
//                std::cout<<"algorytm: Branch and Bound BFS"<<std::endl;
//                const auto startTime = std::chrono::high_resolution_clock::now();
//                result = bbfs.branchAndBound(matrix, size, 0);
//                const auto endTime = std::chrono::high_resolution_clock::now();
//                const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
//                std::cout << "Czas wykonania: " << duration << " [us]" << std::endl;
//            } else if (algorithm == "BAndBDFS") {
//                std::cout<<"algorytm: Branch and Bound DFS"<<std::endl;
//                const auto startTime = std::chrono::high_resolution_clock::now();
//                result = bdfs.branchAndBound(matrix, size, 0);
//                const auto endTime = std::chrono::high_resolution_clock::now();
//                const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
//                std::cout << "Czas wykonania: " << duration << " [us]" << std::endl;
//            } else if (algorithm == "BAndBLowestCost") {
//                std::cout<<"algorytm: Branch and Bound lowest cost"<<std::endl;
//                const auto startTime = std::chrono::high_resolution_clock::now();
//                result = bLowestCost.branchAndBound(matrix, size, 0);
//                const auto endTime = std::chrono::high_resolution_clock::now();
//                const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
//                std::cout << "Czas wykonania: " << duration << " [us]" << std::endl;
//            }
//        } else if (matrixType == "a") {
//            if (algorithm == "BAndBBFS") {
//                std::cout<<"algorytm: Branch and Bound BFS"<<std::endl;
//                const auto startTime = std::chrono::high_resolution_clock::now();
//                result = bbfs.startFromEachVertex(matrix, size);
//                const auto endTime = std::chrono::high_resolution_clock::now();
//                const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
//                std::cout << "Czas wykonania: " << duration << " [us]" << std::endl;
//            } else if (algorithm == "BAndBDFS") {
//                std::cout<<"algorytm: Branch and Bound DFS"<<std::endl;
//                const auto startTime = std::chrono::high_resolution_clock::now();
//                result = bdfs.startFromEachVertex(matrix, size);const auto endTime = std::chrono::high_resolution_clock::now();
//                const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
//                std::cout << "Czas wykonania: " << duration << " [us]" << std::endl;
//            } else if (algorithm == "BAndBLowestCost") {
//                result = bLowestCost.startFromEachVertex(matrix, size);
//                const auto startTime = std::chrono::high_resolution_clock::now();
//                std::cout<<"algorytm: Branch and Bound lowest cost"<<std::endl;
//                const auto endTime = std::chrono::high_resolution_clock::now();
//                const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
//                std::cout << "Czas wykonania: " << duration << " [us]" << std::endl;
//            }
//        }
//        printSolution(result, size);
//
//        // Zwalnianie pamięci
//        for (int i = 0; i < size; i++) {
//            delete[] matrix[i];
//        }
//        delete[] matrix;
//    }
//
//    file.close();
//}
//
//void ConfigFileHandler::printSolution(const Result& result, int size) {
//    if (result.path != nullptr) {
//        std::cout << "Najlepsza trasa: ";
//
//        //size do iterowania po ścieżce
//        for (int i = 0; i < size; i++) {
//            std::cout << result.path[i] << " -> ";
//        }
//
//        std::cout << result.path[0] << std::endl; // Powrót do miasta startowego
//        std::cout << "Minimalny koszt: " << result.cost << std::endl;
//    } else {
//        std::cout << "Brak znalezionego rozwiązania." << std::endl;
//    }
//}