#ifndef PROJEKT_ETAP2_DFS_H
#define PROJEKT_ETAP2_DFS_H
#include "../Utils/Node.h"

class DFS {
private:
    int size;
    int minCost;
    int* bestPath;
    int allVertexMinCost;
    int *allVertexBestPath;
    int calculateCost(int* path, int** costMatrix, int pathSize);
    int lowerBound(int* currentPath, int** distances, int currentPathSize);
    void dfs(Node* currentNode, int** costMatrix);

public:
    DFS(int n) : size(n), minCost(INT_MAX) {
        bestPath = new int[size];
        for (int i = 0; i < size; ++i) bestPath[i] = -1;
        allVertexMinCost = INT_MAX;
        allVertexBestPath = nullptr;
    }
    ~DFS() {
        delete[] bestPath;
    }
    void showTheShortestPath(int** costMatrix);
    void showThePath(int start, int** costMatrix);
    int bnb_dfs_run(int** costMatrix, int start);
    int startFromEachVertex(int** costMatrix);
};


#endif //PROJEKT_ETAP2_DFS_H
