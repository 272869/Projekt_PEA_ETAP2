#pragma once
#include <iostream>
class BranchAndBound {
public:
    int size = 0; // Liczba miast (rozmiar problemu)
    int minCost = 1000000000; // Koszt minimalny
    int* bestPath = NULL; // Najlepsza �cie�ka
    int* rest = NULL; // Tablica miast, kt�re nie zosta�y odwiedzone

    // Konstruktor
    BranchAndBound(int n) {
        this->size = n;
        rest = new int[n];
    }
    // Destruktor
    ~BranchAndBound() {

        delete[] rest;
        delete[] bestPath;
    }
    // Resetuje tablice z najlepsz� tras�
    void restoreTables() {
        int minCost = 1000000000;
        int temp_size = 1;
        for (int i = 0; i < size + 1; i++) {
            bestPath[i] = -1;
        }
    }

    // Funkcja zwracaj�ca dolne ograniczenie
    int lowerBound(int* currentPath, int** distances, int currentPathSize);

    // Wywo�uje algorytm B&B
    int bnb_run(int** routes, bool time_measure);
    void showTheShortestPath(int** costMatrix);
    // Funkcja rekurencyjna B&B
    void bnb(int* path, int start, int& minCost, int* bestPath, int** costMatrix, int size);

    // Funkcja oblicza ca�kowity koszt trasy
    int calculateCost(int* path, int** costMatrix, int size) {
        int cost = 0;
        for (int i = 0; i < size - 1; i++) {
            cost += costMatrix[path[i]][path[i + 1]];
        }
        cost += costMatrix[path[size - 1]][path[0]];
        return cost;
    }

};