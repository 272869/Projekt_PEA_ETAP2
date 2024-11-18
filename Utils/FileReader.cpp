#include "FileReader.h"
#include <iostream>

//załadowanie pliku grafu
bool FileReader::openFile(){
    std::string nameOfFile;

    std::cout << "Podaj nazwe pliku" << std::endl;
    std::cin >> nameOfFile;
    std::cout << "\n";
    file.open(nameOfFile);
    if(!file.is_open()) {
        std::cout << "Nie ma takiego pliku\n";
        return false;
    }
    else {
        std::cout << "Otworzono plik " << nameOfFile <<"\n";
        return true;
    }
}
//pobieranie liczb z plików
int FileReader::getDataFromFile() {
    int number;
    file >> number;
    return number;
}

int** FileReader::readFile(const std::string& path, int& size) {
    std::ifstream file(path);  // Otwiera plik do odczytu
    if (!file) {
        throw std::runtime_error("Nie można otworzyć pliku: " + path);
    }

    file >> size;  // Odczytuje rozmiar macierzy
    int** matrix = new int*[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            file >> matrix[i][j];  // Odczyt wartości do macierzy
        }
    }

    return matrix;
}