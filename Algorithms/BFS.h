#include <cstring>
#include <climits>

class BFS {
private:
    int size;       // Liczba miast w problemie TSP
    int minCost;    // Minimalny koszt rozwiązania

    // Funkcja pomocnicza do obliczania kosztu pełnej ścieżki
    int calculateCost(int* path, int** costMatrix, int pathSize);

    // Funkcja pomocnicza do obliczania dolnego ograniczenia
    int lowerBound(int* currentPath, int** distances, int currentPathSize);

public:
    // Konstruktor klasy
    BFS(int n) : size(n), minCost(INT_MAX) {}

    // Funkcja uruchamiająca algorytm Branch and Bound BFS
    int bnb_bfs_run(int** costMatrix);
};

