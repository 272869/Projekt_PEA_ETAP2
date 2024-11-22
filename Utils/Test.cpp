#include "Test.h"
#include <chrono>
#include <fstream>
#include "../Algorithms/BFS.h"
#include "../Algorithms/DFS.h"
#include "../Algorithms/BranchAndBound.h"

void Test::startTests() {
    int size[] = {4, 5, 6, 7, 8, 9, 10}; // Rozmiary macierzy
    std::string format = "size, time[us]"; // Format nagłówka pliku CSV

    // Zapis nagłówka do plików
    typeOfDataMessage(format);

    for (int s : size) {
        long long sumTimeLC = 0;
        long long sumTimeBFS = 0;
        long long sumTimeDFS = 0;

        for (int i = 0; i < 50; i++) {
            // Generowanie danych
            file_reader.loadRandomData(s, 99);
            int** matrix = file_reader.tab; // Wskaźnik na wygenerowaną macierz

            // Pomiar czasu i sumowanie wyników
            long long timeBF = calculateTime(1, matrix); // Algorytm brute force
            saveToCsvFile("LC.csv", timeBF, s);
            sumTimeLC += timeBF;

            long long timeNN = calculateTime(2, matrix); // Algorytm najbliższego sąsiada
            saveToCsvFile("BFS.csv", timeNN, s);
            sumTimeBFS += timeNN;

            long long timeRand = calculateTime(3, matrix); // Algorytm losowy
            saveToCsvFile("DFS.csv", timeRand, s);
            sumTimeDFS += timeRand;

            // Zwolnienie pamięci
            for (int row = 0; row < s; row++) delete[] matrix[row];
            delete[] matrix;
        }

        // Obliczanie średnich czasów
        double avgTimeLC = static_cast<double>(sumTimeLC) / 50.0;
        double avgTimeBFS = static_cast<double>(sumTimeBFS) / 50.0;
        double avgTimeDFS = static_cast<double>(sumTimeDFS) / 50.0;

        std::cout << "LC:   " << s << ", avg time: " << avgTimeLC << " [us]" << std::endl;
        std::cout << "BFS:   " << s << ", avg time: " << avgTimeBFS << " [us]" << std::endl;
        std::cout << "DFS: " << s << ", avg time: " << avgTimeDFS << " [us]" << std::endl;
    }
}


// Zapis danych do pliku CSV
void Test::saveToCsvFile(std::string fileName, long long time, int size) {
    std::ofstream file(fileName, std::ios::out | std::ios::app);  // Otwarcie pliku do zapisu

    if (!file.is_open()) {  // Sprawdzenie, czy plik został otwarty poprawnie
        std::cerr << "Nie można otworzyć pliku " << fileName << " do zapisu!" << std::endl;
        return;
    }

    file << size << ",    " << time<< std::endl;  // Zapis danych do pliku CSV
    file.close();  // Zamknięcie pliku
}

// Zapisanie komunikatu do pliku CSV
void Test::saveToCsvFile(std::string fileName, std::string message) {
    std::ofstream file(fileName, std::ios::out | std::ios::app);  // Otwarcie pliku do zapisu

    if (!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku " << fileName << " do zapisu!" << std::endl;
        return;
    }

    file << message << std::endl;  // Zapisanie komunikatu
    file.close();  // Zamknięcie pliku
}

// Zapis nagłówka do plików CSV
void Test::typeOfDataMessage(std::string message) {
    std::cout << "Utworzono plik" << std::endl;  // Komunikat o utworzeniu pliku
    saveToCsvFile("LC.csv", message);  // Zapisanie nagłówka do pliku BF.csv
    saveToCsvFile("BFS.csv", message);  // Zapisanie nagłówka do pliku NN.csv
    saveToCsvFile("DFS.csv", message);  // Zapisanie nagłówka do pliku Rand.csv
}

// Obliczanie czasu wykonania algorytmu
long long Test::calculateTime(int algorithm, int** matrix) {
    long long time;
    BranchAndBound* bnb = nullptr;
    BFS* bfs = nullptr;
    DFS* dfs = nullptr;
    switch (algorithm) {
        case 1: {  // Algorytm brute force
            bnb = new BranchAndBound(file_reader.size);
            auto timeStart = std::chrono::high_resolution_clock::now();  // Start pomiaru czasu
            //bnb->startFromEachVertex(matrix);
            bnb->bnb_run(matrix,0);
            auto timeEnd = std::chrono::high_resolution_clock::now();  // Koniec pomiaru czasu
            time = std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeStart).count();
            break;
        }
        case 2: {  // Algorytm najbliższego sąsiada (Nearest Neighbour)
            bfs = new BFS(file_reader.size);
            auto timeStart = std::chrono::high_resolution_clock::now();  // Start pomiaru czasu
            //bfs->startFromEachVertex(matrix);
            bfs->bnb_bfs_run(matrix,0);
            auto timeEnd = std::chrono::high_resolution_clock::now();  // Koniec pomiaru czasu
            time = std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeStart).count();
            break;
        }
        case 3: {
            dfs = new DFS(file_reader.size);
            auto timeStart = std::chrono::high_resolution_clock::now();  // Start pomiaru czasu
            //dfs->startFromEachVertex(matrix);
            dfs->bnb_dfs_run(matrix,0);
            auto timeEnd = std::chrono::high_resolution_clock::now();  // Koniec pomiaru czasu
            time = std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeStart).count();
            break;
        }
        default: {
            std::cerr << "Nieprawidłowy wybór algorytmu!" << std::endl;
            time=0;
            break;
        }
    }
    return time;
}