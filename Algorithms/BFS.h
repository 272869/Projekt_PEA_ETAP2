#include <cstring>
#include <climits>

class BFS {
private:
    int size;       // Liczba miast w problemie TSP
    int minCost;    // Minimalny koszt rozwiązania
    int *bestPath;    // Minimalny koszt rozwiązania
    int allVertexMinCost;
    int *allVertexBestPath;

    // Funkcja pomocnicza do obliczania kosztu pełnej ścieżki
    int calculateCost(int* path, int** costMatrix, int pathSize);

    // Funkcja pomocnicza do obliczania dolnego ograniczenia
    int lowerBound(int* currentPath, int** distances, int currentPathSize);

public:
    // Konstruktor klasy
    BFS(int n) : size(n), minCost(INT_MAX) {
        allVertexMinCost = INT_MAX;
        allVertexBestPath = nullptr;
    }

    ~BFS() {
        delete[] bestPath;
    }
    void showTheShortestPath(int** costMatrix);
    void showThePath(int start, int** costMatrix);
    int startFromEachVertex(int** costMatrix);
    int bnb_bfs_run(int** costMatrix, int start);
};

