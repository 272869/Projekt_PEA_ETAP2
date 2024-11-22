#include "BranchAndBound.h"

int BranchAndBound::calculateCost(int* path, int** costMatrix, int size) {
    int cost = 0;
    for (int i = 0; i < size - 1; i++) cost += costMatrix[path[i]][path[i + 1]];
    cost += costMatrix[path[size - 1]][path[0]];
    return cost;
}

int BranchAndBound::lowerBound(int* currentPath, int** distances, int currentPathSize) {
    if (currentPathSize == size) return -1;
    int value = 0;
    for (int i = 1; i < currentPathSize; i++) value += distances[currentPath[i - 1]][currentPath[i]];
    for (int i = 0; i < size; i++) rest[i] = 0;
    for (int i = 0; i < currentPathSize; i++) rest[currentPath[i]] = 1;
    for (int i = 0; i < size; i++) {
        if (rest[i] == 1 && currentPath[currentPathSize - 1] != i) continue;
        int min = INT_MAX;
        for (int j = 0; j < size; j++) {
            if (rest[j] == 1 || i == j) continue;
            if (distances[i][j] < min) min = distances[i][j];
        }
        if (rest[i] != 1) if (distances[i][0] < min) min = distances[i][0];
        value += min;
    }
    return value;
}

void BranchAndBound::bnb(int* currentPath, int start, int& minCost, int* bestPath, int** costMatrix, int size) {
    if (start == size) {
        int currentCost = calculateCost(currentPath, costMatrix, size);
        if (currentCost < minCost) {
            minCost = currentCost;
            for (int i = 0; i < size; ++i) bestPath[i] = currentPath[i];
        }
        return;
    }
    for (int i = start; i < size; ++i) {
        std::swap(currentPath[start], currentPath[i]);
        int bound = lowerBound(currentPath, costMatrix, start + 1);
        if (bound < minCost) bnb(currentPath, start + 1, minCost, bestPath, costMatrix, size);
        std::swap(currentPath[start], currentPath[i]);
    }
}

int BranchAndBound::bnb_run(int** routes, int start) {
    start = 0;
    int result = 0;
    int* path = new int[size];
    for (int i = 0; i < size; i++) path[i] = i;
    bestPath = new int[size];
    for (int i = 0; i < size; i++) bestPath[i] = -1;
    bnb(path, start, this->minCost, bestPath, routes, size);
    result = calculateCost(bestPath, routes, size);
    return result;
}

int BranchAndBound::startFromEachVertex(int** costMatrix) {
    for (int start = 0; start < size; start++) {
        minCost = INT_MAX;
        bestPath = new int[size];
        bnb_run(costMatrix, start);
        if(minCost < allVertexMinCost){
            allVertexMinCost = minCost;
            allVertexBestPath = bestPath;
        }
    }
    return minCost;
}

void BranchAndBound::showThePath(int start, int** costMatrix) {
    for (int i = 0; i < size; i++) std::cout << bestPath[i] << " -> ";
    std::cout << bestPath[0] << std::endl;
    int cost = calculateCost(bestPath, costMatrix, size);
    std::cout << "Koszt tej sciezki: " << cost << std::endl;
}

void BranchAndBound::showTheShortestPath(int** costMatrix) {
    std::cout << "Najkrotsza sciezka: ";
    if(allVertexBestPath == nullptr) return;
    for (int i = 0; i < size; i++) std::cout << allVertexBestPath[i] << " -> ";
    std::cout << allVertexBestPath[0] << std::endl;
    std::cout << "Koszt najkrotszej sciezki: " << allVertexMinCost << std::endl;
}