
#include <climits>
#include <algorithm>
#include <iostream>
#include "DFS.h"

int DFS::calculateCost(int* path, int** costMatrix, int pathSize) {
    int cost = 0;
    for (int i = 1; i < pathSize; i++) {
        cost += costMatrix[path[i - 1]][path[i]];
    }
    cost += costMatrix[path[pathSize - 1]][path[0]]; // Koszt powrotu do punktu początkowego
    return cost;
}

int DFS::lowerBound(int* currentPath, int** distances, int currentPathSize) {
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
                minCost = std::min(minCost, distances[i][j]);
            }
        }
        minCost = std::min(minCost, distances[i][0]);
        value += minCost;
    }
    delete[] visited;
    return value;
}

void DFS::dfs(Node* currentNode, int** costMatrix) {
    if (currentNode->bound >= minCost) {
        delete currentNode;
        return;
    }
    if (currentNode->level == size) {
        int currentCost = calculateCost(currentNode->path, costMatrix, size);
        if (currentCost < minCost) {
            minCost = currentCost;
            for (int i = 0; i < size; ++i) {
                bestPath[i] = currentNode->path[i];
            }
        }
        delete currentNode;
        return;
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
        Node* childNode = new Node(size);
        for (int j = 0; j < currentNode->level; ++j) {
            childNode->path[j] = currentNode->path[j];
        }
        childNode->path[currentNode->level] = i;
        childNode->level = currentNode->level + 1;
        childNode->cost = currentNode->cost +
                          costMatrix[currentNode->path[currentNode->level - 1]][i];

        childNode->bound = lowerBound(childNode->path, costMatrix, childNode->level);

        dfs(childNode, costMatrix); // Rekurencyjne wywołanie dla dziecka
    }
    delete currentNode;
}

int DFS::bnb_dfs_run(int** costMatrix) {
    Node* root = new Node(size);
    root->path[0] = 1;
    root->level = 1;
    root->bound = lowerBound(root->path, costMatrix, 1);
    dfs(root, costMatrix);
    return minCost;
}

// Wyświetlenie najkrótszej ścieżki i kosztu
void DFS::showTheShortestPath(int** costMatrix) {
    if (bestPath == nullptr) {
        return;
    }
    for (int i = 0; i < size; i++) {
        std::cout << bestPath[i] << " -> ";
    }
    std::cout << bestPath[0] << std::endl; // Powrót do punktu początkowego
    int cost = calculateCost(bestPath, costMatrix, size);
    std::cout << "Koszt: " << cost << std::endl;
}
