#include "LowestCost.h"

// Oblicza koszt pełnej ścieżki
int LowestCost::calculateCost(int* path, int** costMatrix, int size) {
    int cost = 0;
    for (int i = 0; i < size - 1; i++) cost += costMatrix[path[i]][path[i + 1]]; // Sumujemy koszty wszystkich odcinków w ścieżce.
    cost += costMatrix[path[size - 1]][path[0]]; // Dodajemy koszt powrotu do punktu startowego.
    return cost;
}

// Oblicza dolne oszacowanie kosztu dla częściowej ścieżki
int LowestCost::lowerBound(int* currentPath, int** distances, int currentPathSize) {

    // Jeśli ścieżka jest już pełna, zwracamy -1 jako informację o braku dalszego podziału.
    if (currentPathSize == size) return -1;
    int value = 0;

    // Obliczamy koszt już odwiedzonych węzłów w obecnej ścieżce.
    for (int i = 1; i < currentPathSize; i++) value += distances[currentPath[i - 1]][currentPath[i]];

    // Tworzymy tablicę `rest`, aby śledzić, które wierzchołki zostały odwiedzone.
    for (int i = 0; i < size; i++) rest[i] = 0; //nieodwiedzone
    for (int i = 0; i < currentPathSize; i++) rest[currentPath[i]] = 1; // odwiedzone

    // Dla każdego nieodwiedzonego wierzchołka szukamy najkrótszej krawędzi.
    for (int i = 0; i < size; i++) {
        if (rest[i] == 1 && currentPath[currentPathSize - 1] != i) continue; // jeżeli odwiedzone to pomijamy
        int min = INT_MAX; // Inicjalizujemy wartość minimalną.
        for (int j = 0; j < size; j++) {
            if (rest[j] == 1 || i == j) continue; //Pomijamy wierzchołki już odwiedzone i do samego siebie.
            if (distances[i][j] < min) min = distances[i][j]; // aktualizujemy min
        }

        // Uwzględniamy także koszt powrotu do punktu początkowego.
        if (rest[i] != 1) if (distances[i][0] < min) min = distances[i][0];
        value += min;
    }
    return value;
}


void LowestCost::bnb_lc(Node* currentNode, int** costMatrix) {
    // Jeśli osiągnięto pełną ścieżkę, obliczamy jej koszt
    if (currentNode->depth == size) {
        int currentCost = calculateCost(currentNode->path, costMatrix, size);
        if (currentCost < minCost) {
            minCost = currentCost;
            for (int i = 0; i < size; ++i) bestPath[i] = currentNode->path[i];
        }
        delete currentNode; // Usuwamy węzeł po przetworzeniu
        return;
    }

    // Tworzymy nowe gałęzie dla każdego nieodwiedzonego miasta
    for (int i = 0; i < size; ++i) {
        bool visited = false;

        // Sprawdzamy, czy miasto `i` zostało już odwiedzone
        for (int j = 0; j < currentNode->depth; ++j) {
            if (currentNode->path[j] == i) {
                visited = true;
                break;
            }
        }
        if (visited) continue;

        // Tworzymy nowy węzeł (dziecko)
        Node* childNode = new Node(size);
        for (int j = 0; j < currentNode->depth; ++j) {
            childNode->path[j] = currentNode->path[j];
        }
        childNode->path[currentNode->depth] = i;
        childNode->depth = currentNode->depth + 1;

        // Obliczamy koszt i dolne oszacowanie
        childNode->cost = currentNode->cost + costMatrix[currentNode->path[currentNode->depth - 1]][i];
        childNode->bound = lowerBound(childNode->path, costMatrix, childNode->depth);

        // Przetwarzamy gałąź, jeśli jej oszacowanie jest mniejsze niż minCost
        if (childNode->bound < minCost) {
            bnb_lc(childNode, costMatrix);
        } else {
            delete childNode; // Odrzucamy gałąź, jeśli oszacowanie jest nieopłacalne
        }
    }
    delete currentNode; // Usuwamy bieżący węzeł po zakończeniu przetwarzania
}


int LowestCost::bnb_lc_run(int** costMatrix, int start) {
    // Tworzymy korzeń drzewa
    Node* root = new Node(size);
    root->path[0] = start;
    root->depth = 1;
    root->cost = 0;
    root->bound = lowerBound(root->path, costMatrix, root->depth);

    // Uruchamiamy algorytm
    bnb_lc(root, costMatrix);

    return minCost;
}

// Uruchamia algorytm dla każdego możliwego punktu początkowego.
int LowestCost::startFromEachVertex(int** costMatrix) {
    for (int start = 0; start < size; start++) {
        minCost = INT_MAX;
        bestPath = new int[size];
        bnb_lc_run(costMatrix, start);
        if(minCost < allVertexMinCost){
            allVertexMinCost = minCost;
            allVertexBestPath = bestPath;
        }
    }
    return minCost;
}

// Wyświetla ścieżkę z danego punktu startowego.
void LowestCost::showThePath(int** costMatrix) {
    for (int i = 0; i < size; i++) std::cout << bestPath[i] << " -> ";
    std::cout << bestPath[0] << std::endl;
    int cost = calculateCost(bestPath, costMatrix, size);
    std::cout << "Koszt tej sciezki: " << cost << std::endl;
}

// Wyświetla najlepszą znalezioną ścieżkę z wszystkich wierzchołków
void LowestCost::showTheShortestPath() {
    std::cout << "Najkrotsza sciezka: ";
    if(allVertexBestPath == nullptr) return;
    for (int i = 0; i < size; i++) std::cout << allVertexBestPath[i] << " -> ";
    std::cout << allVertexBestPath[0] << std::endl;
    std::cout << "Koszt najkrotszej sciezki: " << allVertexMinCost << std::endl;
}