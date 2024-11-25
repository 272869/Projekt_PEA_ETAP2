#pragma once
#include <iostream>
#include "../Utils/Node.h"

class LowestCost {
public:
    int size = 0;
    int minCost = INT_MAX;
    int* bestPath = NULL;
    int* rest = NULL;
    int allVertexMinCost;
    int *allVertexBestPath;

    LowestCost(int n) {
        this->size = n;
        rest = new int[n];
        allVertexMinCost = INT_MAX;
        allVertexBestPath = nullptr;
    }
    ~LowestCost() {
        delete[] rest;
        delete[] bestPath;
    }

    int lowerBound(int* currentPath, int** distances, int currentPathSize);
    int bnb_lc_run(int** routes, int start);
    void showTheShortestPath();
    void showThePath(int** costMatrix);
    int startFromEachVertex(int** routes);
    void bnb_lc(Node* currentNode, int** costMatrix);
    int calculateCost(int* path, int** costMatrix, int size);
};