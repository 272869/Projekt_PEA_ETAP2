#include <climits>
#include <iostream>
#include "BFS.h"
#include "../Utils/PriorityQueue.h"

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

int BFS::bnb_bfs_run(int** costMatrix) {
    Queue queue;
    queue.init(100);
    Node* root = new Node(size);
    root->path[0] = 0;
    root->level = 1;
    root->bound = lowerBound(root->path, costMatrix, 1);
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

void BFS::showTheShortestPath(int** costMatrix) {
    if (bestPath == nullptr) {
        return;
    }
    for (int i = 0; i < size; i++) {
        cout << bestPath[i] << " -> ";
    }
    cout << bestPath[0] << endl; // Powrót do punktu początkowego

    int cost = calculateCost(bestPath, costMatrix, size);
    cout << "Koszt: " << cost << endl;
}
