#include <climits>
#include <algorithm>
#include <iostream>
#include "DFS.h"

int DFS::calculateCost(int* path, int** costMatrix, int pathSize) {
    int cost = 0;
    for (int i = 1; i < pathSize; i++) cost += costMatrix[path[i - 1]][path[i]];
    cost += costMatrix[path[pathSize - 1]][path[0]];
    return cost;
}

int DFS::lowerBound(int* currentPath, int** distances, int currentPathSize) {
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

void DFS::dfs(Node* currentNode, int** costMatrix) {
    if (currentNode->bound >= minCost) {
        delete currentNode;
        return;
    }
    if (currentNode->depth == size) {
        int currentCost = calculateCost(currentNode->path, costMatrix, size);
        if (currentCost < minCost) {
            minCost = currentCost;
            for (int i = 0; i < size; ++i) bestPath[i] = currentNode->path[i];
        }
        delete currentNode;
        return;
    }
    for (int i = 0; i < size; ++i) {
        bool visited = false;
        for (int j = 0; j < currentNode->depth; ++j) {
            if (currentNode->path[j] == i) {
                visited = true;
                break;
            }
        }
        if (visited) continue;
        Node* childNode = new Node(size);
        for (int j = 0; j < currentNode->depth; ++j) childNode->path[j] = currentNode->path[j];
        childNode->path[currentNode->depth] = i;
        childNode->depth = currentNode->depth + 1;
        childNode->cost = currentNode->cost + costMatrix[currentNode->path[currentNode->depth - 1]][i];
        childNode->bound = lowerBound(childNode->path, costMatrix, childNode->depth);
        dfs(childNode, costMatrix);
    }
    delete currentNode;
}

int DFS::bnb_dfs_run(int** costMatrix, int start) {
    Node* root = new Node(size);
    root->path[0] = start;
    root->depth = 1;
    root->bound = lowerBound(root->path, costMatrix, root->depth);
    dfs(root, costMatrix);
    return minCost;
}

int DFS::startFromEachVertex(int** costMatrix) {
    for (int start = 0; start < size; start++) {
        minCost = INT_MAX;
        bestPath = new int[size];
        bnb_dfs_run(costMatrix, start);
        if(minCost < allVertexMinCost){
            allVertexMinCost = minCost;
            allVertexBestPath = bestPath;
        }
    }
    return minCost;
}

void DFS::showThePath(int start, int** costMatrix) {
    for (int i = 0; i < size; i++) std::cout << bestPath[i] << " -> ";
    std::cout << bestPath[0] << std::endl;
    int cost = calculateCost(bestPath, costMatrix, size);
    std::cout << "Koszt tej sciezki: " << cost << std::endl;
}

void DFS::showTheShortestPath(int** costMatrix) {
    std::cout << "Najkrotsza sciezka: ";
    if(allVertexBestPath == nullptr) return;
    for (int i = 0; i < size; i++) std::cout << allVertexBestPath[i] << " -> ";
    std::cout << allVertexBestPath[0] << std::endl;
    std::cout << "Koszt najkrotszej sciezki: " << allVertexMinCost << std::endl;
}
