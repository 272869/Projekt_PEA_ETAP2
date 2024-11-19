#include "BranchAndBound.h"

using namespace std;

int BranchAndBound::lowerBound(int* currentPath, int** distances, int currentPathSize) {
    if (currentPathSize == size) return -1;	// Je�li �cie�ka jest pe�na, zwr�� -1
    int value = 0;	// zmienna przechowuj�ca warto�� dolnego ograniczenia

    // Sumowanie odleglosci mi�dzy miastami odwiedzonymi
    for (int i = 1; i < currentPathSize; i++) {
        value += distances[currentPath[i - 1]][currentPath[i]];
    }

    // Resetowanie tablicy miast, które zostały odwiedzone
    for (int i = 0; i < size; i++) {
        rest[i] = 0;
    }

    // Aktualizacja tablicy miast w obecnej trasie
    for (int i = 0; i < currentPathSize; i++) {
        rest[currentPath[i]] = 1;
    }

    // Szukanie minimalnych kosztów dla nieodwiedzonych miast
    for (int i = 0; i < size; i++) {
        if (rest[i] == 1 && currentPath[currentPathSize - 1] != i) continue; // Pomijanie odwiedzonych miast
        int min = 100000;
        for (int j = 0; j < size; j++) {
            if (rest[j] == 1 || i == j) continue;
            if (distances[i][j] < min) min = distances[i][j]; // Minimalny koszt przejścia jeśli znaleziony
        }

        // Dla nieodwiedzonych miast, sprawdza również koszt powrotu do punktu początkowego
        if (rest[i] != 1) {
            if (distances[i][0] < min) min = distances[i][0];
        }

        value += min; // Dodanie minimalnego kosztu dla miasta i
    }
    return value; // Zwrócenie dolnego ograniczenia
}

// Funkcja rekurencyjna B&B
void BranchAndBound::bnb(int* currentPath, int start, int& minCost, int* bestPath, int** costMatrix, int size) {
    if (start == size) { // Jeśli wszystkie miasta odwiedzone
        int currentCost = calculateCost(currentPath, costMatrix, size); // Obliczanie kosztu pełnej trasy
        if (currentCost < minCost) { // Aktualizacja minimalnego kosztu
            minCost = currentCost;
            for (int i = 0; i < size; ++i) {
                bestPath[i] = currentPath[i]; // Zapisanie nowej najlepszej trasy
            }
        }
        return;
    }

    // Przeszukiwanie wszystkich możliwych tras
    for (int i = start; i < size; ++i) {
        swap(currentPath[start], currentPath[i]); // Zamiana miast do permutacji

        int bound = lowerBound(currentPath, costMatrix, start + 1); // Obliczanie dolnego ograniczenia
        if (bound < minCost) {
            bnb(currentPath, start + 1, minCost, bestPath, costMatrix, size); // Rekurencyjne wywołanie funkcji
        }

        swap(currentPath[start], currentPath[i]); // Powrót do poprzedniego stanu po rekurencji
    }
}

// Uruchomienie algorytmu B&B
int BranchAndBound::bnb_run(int** routes, bool time_measure) {
    int currentCity = 0; // Miasto początkowe
    int currentCost = 0; // Koszt aktualnej trasy
    int result = 0; // Zmienna przechowująca koszt trasy
    int* path = new int[size]; // Tablica do przechowywania aktualnej trasy

    for (int i = 0; i < size; i++) {
        path[i] = i; // Inicjalizacja trasy
    }

    bestPath = new int[size];	// Tablica do przechowywania najlepszej trasy
    for (int i = 0; i < size; i++) {
        bestPath[i] = -1; // -1 oznacza brak wyniku
    }

    bnb(path, currentCity, this->minCost, bestPath, routes, size);

    result = calculateCost(bestPath, routes, size);

    return result;
}

// Wyświetlenie najkrótszej ścieżki i kosztu
void BranchAndBound::showTheShortestPath(int** costMatrix) {
    if (bestPath == nullptr) {
        return;
    }
    for (int i = 0; i < size; i++) {
        cout << bestPath[i] << " -> ";
    }
    cout << bestPath[0] << endl; // Powrót do początkowego miasta

    int cost = calculateCost(bestPath, costMatrix, size);
    cout << "Koszt: " << cost << endl;
}
