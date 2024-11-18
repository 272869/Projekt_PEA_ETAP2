

#ifndef PROJEKT_ETAP2_DFS_H
#define PROJEKT_ETAP2_DFS_H


#include "../Utils/Node.h"

class DFS {
private:
    int size;       // Liczba miast
    int minCost;    // Minimalny koszt rozwiązania
    int* bestPath;  // Najlepsza znaleziona trasa

    // Funkcja pomocnicza do obliczania kosztu pełnej ścieżki
    int calculateCost(int* path, int** costMatrix, int pathSize);

    // Funkcja pomocnicza do obliczania dolnego ograniczenia
    int lowerBound(int* currentPath, int** distances, int currentPathSize);

    // Główna funkcja DFS (rekurencyjna)
    void dfs(Node* currentNode, int** costMatrix);

public:
    // Konstruktor klasy
    DFS(int n) : size(n), minCost(INT_MAX) {
        bestPath = new int[size];
        for (int i = 0; i < size; ++i) {
            bestPath[i] = -1;
        }
    }

    // Destruktor klasy
    ~DFS() {
        delete[] bestPath;
    }

    // Funkcja uruchamiająca algorytm DFS
    int bnb_dfs_run(int** costMatrix);
};


#endif //PROJEKT_ETAP2_DFS_H
