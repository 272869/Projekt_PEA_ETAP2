#pragma once
#include <iostream>
class BranchAndBound {
public:
    int size = 0; // Liczba miast (rozmiar problemu)
    int minCost = 1000000000; // Koszt minimalny
    int* bestPath = NULL; // Najlepsza �cie�ka
    int* rest = NULL; // Tablica miast, kt�re nie zosta�y odwiedzone
    int allVertexMinCost;
    int *allVertexBestPath;

    // Konstruktor
    BranchAndBound(int n) {
        this->size = n;
        rest = new int[n];
        allVertexMinCost = INT_MAX;
        allVertexBestPath = nullptr;
    }
    // Destruktor
    ~BranchAndBound() {

        delete[] rest;
        delete[] bestPath;
    }


    // Funkcja zwracaj�ca dolne ograniczenie
    int lowerBound(int* currentPath, int** distances, int currentPathSize);

    // Wywo�uje algorytm B&B
    int bnb_run(int** routes, int start);
    void showTheShortestPath(int** costMatrix);
    void showThePath(int start, int** costMatrix);
    int startFromEachVertex(int** routes);
    // Funkcja rekurencyjna B&B
    void bnb(int* path, int start, int& minCost, int* bestPath, int** costMatrix, int size);

    // Funkcja oblicza ca�kowity koszt trasy
    int calculateCost(int* path, int** costMatrix, int size);
};