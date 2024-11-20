#include <climits>
#include <iostream>
#include "BFS.h"
#include "../Utils/Queue.h"

using namespace std;


int BFS::calculateCost(int* path, int** costMatrix, int pathSize) {
    int cost = 0;
    for (int i = 1; i < pathSize; i++) {
        cost += costMatrix[path[i - 1]][path[i]];
    }
       cost += costMatrix[path[pathSize - 1]][path[0]]; // koszt powrotu do punktu początkowego
       return cost;
}
int BFS::lowerBound(int* currentPath, int** distances, int currentPathSize) {
    if (currentPathSize == size) return -1;
    int value = 0;
    for (int i = 1; i < currentPathSize; i++) {
        value += distances[currentPath[i - 1]][currentPath[i]];
    }
    int* visited = new int[size]{0};
    for (int i = 0; i < currentPathSize; i++) {
        visited[currentPath[i]] = 1;
    }
    for (int i = 0; i < size; i++) {
        if (visited[i]) continue;
        int minCost = INT_MAX;
        for (int j = 0; j < size; j++) {
            if (!visited[j] && i != j) {
                minCost = min(minCost, distances[i][j]);
            }
        }
        minCost = min(minCost, distances[i][0]);
        value += minCost;
    }
    delete[] visited;
    return value;
}

int BFS::bnb_bfs_run(int** costMatrix, int start) {
    Queue queue;
    queue.init(100);
    Node* root = new Node(size);
    root->path[0] = start;
    root->level = 1;
    root->bound = lowerBound(root->path, costMatrix, size);
    queue.enqueue(root);

    bestPath = new int[size]; // Zapisujemy najlepszą trasę jako pole klasy
    for (int i = 0; i < size; ++i) bestPath[i] = -1;

    while (!queue.isEmpty()) {
        Node* currentNode = queue.dequeue();
        if (currentNode->bound >= minCost) {
            delete currentNode;
            continue;
        }
        if (currentNode->level == size) {
            int currentCost = calculateCost(currentNode->path, costMatrix, size);
            if (currentCost < minCost) {
                minCost = currentCost;
                for (int i = 0; i < size; i++) {
                    bestPath[i] = currentNode->path[i];
                }
            }
            delete currentNode;
            continue;
        }

        for (int i = 0; i < size; ++i) {
            bool visited = false;
            for (int j = 0; j < currentNode->level; ++j) {
                if (currentNode->path[j] == i) {
                    visited = true;
                    break;
                }
            }
            if (visited) continue;
            Node* childNode = new Node(*currentNode, size);
            childNode->path[currentNode->level] = i;
            childNode->level = currentNode->level + 1;
            childNode->cost = currentNode->cost + costMatrix[currentNode->path[currentNode->level - 1]][i];
            childNode->bound = lowerBound(childNode->path, costMatrix, childNode->level);
            if (childNode->bound < minCost) {
                queue.enqueue(childNode);
            } else {
                delete childNode;
            }
        }
        delete currentNode;
    }

    return minCost; // Wynik algorytmu
}

int BFS::startFromEachVertex(int** costMatrix) {
    // Wywołanie branch and bound dla każdego wierzchołka początkowego
    for (int start = 0; start < size; start++) {
        minCost = INT_MAX; // Resetujemy minimalny koszt przed każdym wywołaniem
        bestPath = new int[size]; // Resetujemy najlepszą ścieżkę przed każdym wywołaniem
        bnb_bfs_run(costMatrix, start);  // Wywołanie z wierzchołkiem początkowym `start`
        if(minCost < allVertexMinCost)
        {
            allVertexMinCost = minCost;
            allVertexBestPath = bestPath;
        }
        // Wyświetlanie każdej ścieżki po wykonaniu DFS z danego wierzchołka
        //showThePath(start, costMatrix);
    }
    return minCost;
}

// Funkcja do wyświetlania każdej ścieżki w trakcie działania BFS
void BFS::showThePath(int start, int** costMatrix) {
    // Ścieżka aktualna
    std::cout << "Sciezka od wierzcholka " << start << ": ";
    for (int i = 0; i < size; i++) {
        std::cout << bestPath[i] << " -> ";
    }
    std::cout << bestPath[0] << std::endl; // Powrót do punktu początkowego

    // Obliczanie kosztu tej ścieżki
    int cost = calculateCost(bestPath, costMatrix, size);
    std::cout << "Koszt tej sciezki: " << cost << std::endl;
}

// Funkcja do wyświetlania najlepszej ścieżki (po zakończeniu wszystkich wywołań BFS)
void BFS::showTheShortestPath(int** costMatrix) {
    std::cout << "Najkrotsza sciezka: ";
    if(allVertexBestPath == nullptr) return;
    for (int i = 0; i < size; i++) {
        std::cout << allVertexBestPath[i] << " -> ";
    }
    std::cout << allVertexBestPath[0] << std::endl;
    std::cout << "Koszt najkrotszej sciezki: " << allVertexMinCost << std::endl;
}
