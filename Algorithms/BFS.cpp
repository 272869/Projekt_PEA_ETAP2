#include <climits>
#include <iostream>
#include "BFS.h"
#include "../Utils/Queue.h"

int BFS::calculateCost(int* path, int** costMatrix, int pathSize) {
    int cost = 0;
    for (int i = 1; i < pathSize; i++) cost += costMatrix[path[i - 1]][path[i]];
       cost += costMatrix[path[pathSize - 1]][path[0]];
       return cost;
}
int BFS::lowerBound(int* currentPath, int** distances, int currentPathSize) {
    if (currentPathSize == size) return -1;
    int value = 0;
    for (int i = 1; i < currentPathSize; i++) value += distances[currentPath[i - 1]][currentPath[i]];
    int* visited = new int[size]{0};
    for (int i = 0; i < currentPathSize; i++) visited[currentPath[i]] = 1;
    for (int i = 0; i < size; i++) {
        if (visited[i]) continue;
        int minCost = INT_MAX;
        for (int j = 0; j < size; j++) if (!visited[j] && i != j) minCost = std::min(minCost, distances[i][j]);
        minCost = std::min(minCost, distances[i][0]);
        value += minCost;
    }
    delete[] visited;
    return value;
}

int BFS::bnb_bfs_run(int** costMatrix, int start) {

    // Inicjalizacja kolejki do przetwarzania wierzchołków
    Queue queue;
    queue.initialize(100);

    // Tworzymy korzeń drzewa z bieżącego punktu startowego
    Node* root = new Node(size);
    root->path[0] = start;
    root->depth = 1; // Odwiedzono jedno miasto
    root->bound = lowerBound(root->path, costMatrix, size);
    queue.enqueue(root); //Dodajemy korzeń do kolejki.

    // Zmienna do przechowywania najlepszej znalezionej ścieżki
    bestPath = new int[size];
    for (int i = 0; i < size; ++i) bestPath[i] = -1; //Wypełniamy ją wartościami -1 jako wartość początkowa.
    while (!queue.isQueueEmpty()) {
        Node* currentNode = queue.dequeue();

        // Jeśli bieżąca granica jest większa lub równa najlepszej znalezionej ścieżce, ignorujemy ten węzeł
        if (currentNode->bound >= minCost) {
            delete currentNode;
            continue;
        }

        // Jeśli wszystkie wierzchołki zostały odwiedzone, obliczamy koszt ścieżki
        if (currentNode->depth == size) {
            int currentCost = calculateCost(currentNode->path, costMatrix, size);

            // Jeśli koszt tej ścieżki jest mniejszy niż dotychczasowy, zapisujemy nową najlepszą ścieżkę
            if (currentCost < minCost) {
                minCost = currentCost;
                for (int i = 0; i < size; i++) bestPath[i] = currentNode->path[i];
            }
            delete currentNode;
            continue;
        }

        // Rozważamy wszystkie możliwe kolejne wierzchołki do odwiedzenia
        for (int i = 0; i < size; ++i) {
            bool visited = false;

            // Sprawdzamy, czy wierzchołek już został odwiedzony
            for (int j = 0; j < currentNode->depth; ++j) {
                if (currentNode->path[j] == i) {
                    visited = true;
                    break;
                }
            }
            if (visited) continue;

            // Tworzymy nowy węzeł potomny
            Node* childNode = new Node(*currentNode, size);
            childNode->path[currentNode->depth] = i; //Dodajemy miasto i do ścieżki.
            childNode->depth = currentNode->depth + 1;
            childNode->cost = currentNode->cost + costMatrix[currentNode->path[currentNode->depth - 1]][i];
            childNode->bound = lowerBound(childNode->path, costMatrix, childNode->depth);
            if (childNode->bound < minCost) queue.enqueue(childNode); // bierzemy kolejny z kolejki jesli obiecujacu
            else delete childNode; // jesli nie usuwamy
        }
        delete currentNode;
    }
    return minCost;
}

int BFS::startFromEachVertex(int** costMatrix) {
    for (int start = 0; start < size; start++) {
        minCost = INT_MAX;
        bestPath = new int[size];
        bnb_bfs_run(costMatrix, start);
        if(minCost < allVertexMinCost){
            allVertexMinCost = minCost;
            allVertexBestPath = bestPath;
        }
    }
    return minCost;
}

void BFS::showThePath(int** costMatrix) {
    for (int i = 0; i < size; i++) std::cout << bestPath[i] << " -> ";
    std::cout << bestPath[0] << std::endl;
    int cost = calculateCost(bestPath, costMatrix, size);
    std::cout << "Koszt tej sciezki: " << cost << std::endl;
}

void BFS::showTheShortestPath() {
    std::cout << "Najkrotsza sciezka: ";
    if(allVertexBestPath == nullptr) return;
    for (int i = 0; i < size; i++) std::cout << allVertexBestPath[i] << " -> ";
    std::cout << allVertexBestPath[0] << std::endl;
    std::cout << "Koszt najkrotszej sciezki: " << allVertexMinCost << std::endl;
}
