/*
#ifndef  ALGORYTMYDOKLADNE_MATRIX_H
#define  ALGORYTMYDOKLADNE_MATRIX_H

#include "FileReader.h"

class Matrix {
public:
    Matrix() {
        loadData();
    }
    void generateRandomMatrix(int minValue, int maxValue);
    void generateSymetricRandomMatrix(int minValue, int maxValue);
    void showMatrixWages();

    int getSize() const;

    void createTables(int size);

    int **getMatrixWeights() const;

    void deleteMatrixTable(int **matrixW);

    int size;
    ~Matrix() {
        if (matrixWeights != nullptr) {
            for (int i = 0; i < size; i++) {
                delete[] matrixWeights[i];
            }
            delete[] matrixWeights;
            matrixWeights = nullptr;  // Ustawienie wskaźnika na nullptr po zwolnieniu pamięci
        }
    }

private:
    int optimum;
    int **matrixWeights = nullptr;
    void createMatrix(FileReader *fileReader);
    void loadData();
};


#endif //ALGORYTMYDOKLADNE_MATRIX_H
*/


#include "FileReader.h"

class Matrix {
public:
    Matrix() {
        loadData();
    }

    void showMatrixWages();
    void generateRandomMatrix(int minValue, int maxValue);
    void generateSymetricRandomMatrix(int minValue, int maxValue);
    int getSize() const;

    int **getMatrixWeights() const;

    void deleteMatrixTable(int **matrixW);

private:
    int size;
    int **matrixWeights = nullptr;
    void createTables();
    void createMatrix(FileReader *loadFromFile);
    void loadData();
};


