#include "Test.h"
#include <chrono>
#include <fstream>
#include "../Algorithms/BFS.h"
#include "../Algorithms/DFS.h"
#include "../Algorithms/LowestCost.h"

void Test::startTests() {
    int size[] = {4, 5, 6, 7, 8, 9, 10}; // Rozmiary macierzy
    int repetitions = 50; // Rozmiary macierzy
    std::string format = "size, time[us]"; // Format nagłówka pliku CSV

    // Zapis nagłówka do plików
    typeOfDataMessage(format);

    for (int s : size) {
        long long sumTimeLC = 0;
        long long sumTimeLCSYM = 0;
        long long sumTimeBFS = 0;
        long long sumTimeBFSSYM = 0;
        long long sumTimeDFS = 0;
        long long sumTimeDFSSYM = 0;

        for (int i = 0; i < repetitions; i++) {
            // Generowanie danych
            file_reader.loadRandomData(s, 99);
            int** matrix = file_reader.tab; // Wskaźnik na wygenerowaną macierz
            file_readerSYM.loadRandomSymetricData(s, 99);
            int** matrixSYM = file_readerSYM.tab; // Wskaźnik na wygenerowaną macierz

            // Pomiar czasu i sumowanie wyników
            long long timeLC = calculateTime(1, matrix); // Algorytm brute force
            saveToCsvFile("LC.csv", timeLC, s);
            sumTimeLC += timeLC;

            long long timeBFS = calculateTime(2, matrix); // Algorytm najbliższego sąsiada
            saveToCsvFile("BFS.csv", timeBFS, s);
            sumTimeBFS += timeBFS;

            long long timeDFS = calculateTime(3, matrix); // Algorytm losowy
            saveToCsvFile("DFS.csv", timeDFS, s);
            sumTimeDFS += timeDFS;

            // Pomiar czasu i sumowanie wyników
            long long timeLCSYM = calculateTime(4, matrixSYM); // Algorytm brute force
            saveToCsvFile("LCSYM.csv", timeLCSYM, s);
            sumTimeLCSYM += timeLCSYM;

            long long timeBFSSYM = calculateTime(5, matrixSYM); // Algorytm najbliższego sąsiada
            saveToCsvFile("BFSSYM.csv", timeBFSSYM, s);
            sumTimeBFSSYM += timeBFSSYM;

            long long timeDFSSYM = calculateTime(6, matrixSYM); // Algorytm losowy
            saveToCsvFile("DFSSYM.csv", timeDFSSYM, s);
            sumTimeDFSSYM += timeDFSSYM;

            // Zwolnienie pamięci
            for (int row = 0; row < s; row++) delete[] matrix[row];
            delete[] matrix;

            for (int row = 0; row < s; row++) delete[] matrixSYM[row];
            delete[] matrixSYM;
        }

        // Obliczanie średnich czasów
        double avgTimeLC = static_cast<double>(sumTimeLC) / repetitions;
        double avgTimeBFS = static_cast<double>(sumTimeBFS) / repetitions;
        double avgTimeDFS = static_cast<double>(sumTimeDFS) / repetitions;
        double avgTimeLCSYM = static_cast<double>(sumTimeLCSYM) / repetitions;
        double avgTimeBFSSYM = static_cast<double>(sumTimeBFSSYM) / repetitions;
        double avgTimeDFSSYM = static_cast<double>(sumTimeDFSSYM) / repetitions;

        std::cout << "LC:   " << s << ", avg time: " << avgTimeLC << " [us]" << std::endl;
        std::cout << "BFS:   " << s << ", avg time: " << avgTimeBFS << " [us]" << std::endl;
        std::cout << "DFS: " << s << ", avg time: " << avgTimeDFS << " [us]" << std::endl;
        std::cout << "LC SYM:   " << s << ", avg time: " << avgTimeLCSYM << " [us]" << std::endl;
        std::cout << "BFS SYM:   " << s << ", avg time: " << avgTimeBFSSYM << " [us]" << std::endl;
        std::cout << "DFS SYM: " << s << ", avg time: " << avgTimeDFSSYM << " [us]" << std::endl;
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
    saveToCsvFile("LCSYM.csv", message);  // Zapisanie nagłówka do pliku BF.csv
    saveToCsvFile("BFSSYM.csv", message);  // Zapisanie nagłówka do pliku NN.csv
    saveToCsvFile("DFSSYM.csv", message);  // Zapisanie nagłówka do pliku Rand.csv
}

// Obliczanie czasu wykonania algorytmu
long long Test::calculateTime(int algorithm, int** matrix) {
    long long time;
    LowestCost* lc = nullptr;
    BFS* bfs = nullptr;
    DFS* dfs = nullptr;
    switch (algorithm) {
        case 1: {  // Algorytm brute force
            lc = new LowestCost(file_reader.size);
            auto timeStart = std::chrono::high_resolution_clock::now();  // Start pomiaru czasu
            lc->startFromEachVertex(matrix); //asym
            auto timeEnd = std::chrono::high_resolution_clock::now();  // Koniec pomiaru czasu
            time = std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeStart).count();
            break;
        }
        case 2: {  // Algorytm najbliższego sąsiada (Nearest Neighbour)
            bfs = new BFS(file_reader.size);
            auto timeStart = std::chrono::high_resolution_clock::now();  // Start pomiaru czasu
            bfs->startFromEachVertex(matrix); //asym
            auto timeEnd = std::chrono::high_resolution_clock::now();  // Koniec pomiaru czasu
            time = std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeStart).count();
            break;
        }
        case 3: {
            dfs = new DFS(file_reader.size);
            auto timeStart = std::chrono::high_resolution_clock::now();  // Start pomiaru czasu
            dfs->startFromEachVertex(matrix); //asym
            auto timeEnd = std::chrono::high_resolution_clock::now();  // Koniec pomiaru czasu
            time = std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeStart).count();
            break;
        }
        case 4: {  // Algorytm brute force
            lc = new LowestCost(file_readerSYM.size);
            auto timeStart = std::chrono::high_resolution_clock::now();  // Start pomiaru czasu
            lc->bnb_lc_run(matrix,0); //sym
            auto timeEnd = std::chrono::high_resolution_clock::now();  // Koniec pomiaru czasu
            time = std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeStart).count();
            break;
        }
        case 5: {  // Algorytm najbliższego sąsiada (Nearest Neighbour)
            bfs = new BFS(file_readerSYM.size);
            auto timeStart = std::chrono::high_resolution_clock::now();  // Start pomiaru czasu
            bfs->bnb_bfs_run(matrix,0); //sym
            auto timeEnd = std::chrono::high_resolution_clock::now();  // Koniec pomiaru czasu
            time = std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeStart).count();
            break;
        }
        case 6: {
            dfs = new DFS(file_readerSYM.size);
            auto timeStart = std::chrono::high_resolution_clock::now();  // Start pomiaru czasu
            dfs->bnb_dfs_run(matrix,0); //sym
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