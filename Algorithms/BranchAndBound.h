#pragma once
#include <iostream>
#include "../Utils/Node.h"

class BranchAndBound {
public:
    int size = 0;
    int minCost = INT_MAX;
    int* bestPath = NULL;
    int* rest = NULL;
    int allVertexMinCost;
    int *allVertexBestPath;
    BranchAndBound(int n) {
        this->size = n;
        rest = new int[n];
        allVertexMinCost = INT_MAX;
        allVertexBestPath = nullptr;
    }
    ~BranchAndBound() {
        delete[] rest;
        delete[] bestPath;
    }
    int lowerBound(int* currentPath, int** distances, int currentPathSize);
    int bnb_run(int** routes, int start);
    void showTheShortestPath(int** costMatrix);
    void showThePath(int start, int** costMatrix);
    int startFromEachVertex(int** routes);
    void bnb(int* path, int start, int& minCost, int* bestPath, int** costMatrix, int size);
    int calculateCost(int* path, int** costMatrix, int size);
};