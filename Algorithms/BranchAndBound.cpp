#include "BranchAndBound.h"

using namespace std;

int BranchAndBound::lowerBound(int* currentPath, int** distances, int currentPathSize) {
    if (currentPathSize == size) return -1;	// Je�li �cie�ka jest pe�na, zwr�� -1
    int value = 0;	// zmienna przechowuj�ca warto�� dolnego ograniczenia

    //Sumowanie odleglosci mi�dzy miastami odwiedzonymi
    for (int i = 1; i < currentPathSize; i++) {
        value += distances[currentPath[i - 1]][currentPath[i]];
    }

    //Resetowanoe tablicy miast, kt�re zosta�y odwiedzone
    for (int i = 0; i < size; i++) {
        rest[i] = 0;
    }

    // Aktualizacja tablicy miast w obecnej trasie
    for (int i = 0; i < currentPathSize; i++) {
        rest[currentPath[i]] = 1;
    }

    // Szukanie minimalnych koszt�w dla nieodwiedzonych miast
    for (int i = 0; i < size; i++) {
        if (rest[i] == 1 && currentPath[currentPathSize - 1] != i) continue; // Pomijanie odwiedzonych miast
        int min = 100000;
        for (int j = 0; j < size; j++) {
            if (rest[j] == 1 || i == j) continue;
            if (distances[i][j] < min)min = distances[i][j]; // Minnimalny koszt przejscia jesli znaleziony
        }

        // Dla nieodwiedzonych miast, sprawdza r�wnie� koszt powrotu do punktu pocz�tkowego

        if (rest[i] != 1) {
            if (distances[i][0] < min)min = distances[i][0];
        }

        value += min; // Dodanie minimalnego kosztu dla miasta i
    }
    return value; // Zwr�cenie dolnego ograniczenia
}

// Funkcja rekurencyjna B&B
void BranchAndBound::bnb(int* currentPath, int start, int& minCost, int* bestPath, int** costMatrix, int size) {
    if (start == size) { // jesli wszystkie miasta odwiedzone
        int currentCost = calculateCost(currentPath, costMatrix, size); // obliczanie kosztu pelnej trasy
        if (currentCost < minCost) { // aktualizacja minimalnego kosztu
            minCost = currentCost;
            for (int i = 0; i < size; ++i) {
                bestPath[i] = currentPath[i]; // zapisanie nowej najlepszej trasy
            }
        }
        return;
    }

    // Przeszukiwanie wszystkich mo�liwych tras
    for (int i = start; i < size; ++i) {
        swap(currentPath[start], currentPath[i]); // zamiana miast do permutacji

        int bound = lowerBound(currentPath, costMatrix, start + 1); // obliczanie dolnego ograniczenia
        if (bound < minCost) {
            bnb(currentPath, start + 1, minCost, bestPath, costMatrix, size); // rekurencyjne wywolanie funkcji
        }

        //swap(path[start], path[i]); // powrot do poprzedniego stanu po rekurencji
    }
}


// uruchomienie algorytmu B&B
int BranchAndBound::bnb_run(int** routes, bool time_measure) {
    int currentCity = 0; // miasto poczatkowe
    int currentCost = 0; // koszt aktualnej trasy
    int result = 0; // zmienna przechowujaca koszt trasy
    int* path = new int[size]; // tablica do przechowywania aktualnej trasy

    for (int i = 0; i < size; i++) {
        path[i] = i; // inicjalizacja trasy
    }

    int* bestPath = new int[size];	// tablica do przechowywania najlepszej trasy
    for (int i = 0; i < size; i++) {
        bestPath[i] = -1; // -1 oznacza brak wyniku
    }

    bnb(path, currentCity, this->minCost, bestPath, routes, size);
    for (int i = 0; i < size; i++) {
        std::cout << bestPath[i] << "->";
    }
    std::cout << 0 << "\n";

    result = calculateCost(bestPath, routes, size);

    return result;
}

