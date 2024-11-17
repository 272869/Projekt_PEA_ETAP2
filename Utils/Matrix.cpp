#include <iostream>
#include "Matrix.h"


void Matrix::createTables() {
    matrixWeights = new int *[size];
    for (int i = 0; i < size; i++) {
        matrixWeights[i] = new int[size];
    }
}

void Matrix::loadData() {
    auto *loadFromFile = new FileReader();
    if (loadFromFile->openFile()) {
        size = loadFromFile->getDataFromFile();
        createTables();
        createMatrix(loadFromFile);
        std::cout << "Wczytano dane\n";
    }
    delete loadFromFile;
}

void Matrix::createMatrix(FileReader *loadFromFile) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrixWeights[i][j] = loadFromFile->getDataFromFile();
            if (i == j)
                matrixWeights[i][j] = INT_MAX;
        }
    }
}


void Matrix::deleteMatrixTable(int **matrixW) {
    for (int i = 0; i < size; i++) {
        delete[] matrixW[i];
    }
    delete[] matrixW;
}

int Matrix::getSize() const {
    return size;
}

int **Matrix::getMatrixWeights() const {
    return matrixWeights;
}
// Losowe generowanie macierzy wag
void Matrix::generateRandomMatrix(int minValue, int maxValue) {
    srand(time(nullptr));  // Inicjalizacja generatora liczb losowych za pomocą aktualnego czasu

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) {
                // Ustawienie -1 na przekątnej
                matrixWeights[i][j] = -1;
            } else {
                // Losowa wartość pomiędzy minValue a maxValue
                matrixWeights[i][j] = minValue + rand() % (maxValue - minValue + 1);
            }
        }
    }
}

// Losowe generowanie symetrycznej macierzy wag
void Matrix::generateSymetricRandomMatrix(int minValue, int maxValue) {
    srand(time(nullptr));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j <= i; j++) {  // Zmieniamy zakres pętli
            if (i == j) {
                matrixWeights[i][j] = -1;
            } else {
                int randomValue = minValue + rand() % (maxValue - minValue + 1);
                matrixWeights[i][j] = randomValue;
                matrixWeights[j][i] = randomValue;  // Symetryczne przypisanie
            }
        }
    }
}
void Matrix::showMatrixWages() {
    std::cout << "  ";
    for (int i = 0; i < size + 1; i++) {
        for (int j = 0; j < size; j++) {
            if (i == 0)
                std::cout << j << " ";
            else {
                if (matrixWeights[i - 1][j] != INT_MAX)
                    std::cout << matrixWeights[i - 1][j];
                else
                    std::cout << "-";
                std::cout << " ";
            }
        }
        if (i != size)
            std::cout << std::endl << i << " ";
    }
    std::cout << std::endl << std::endl;
}
