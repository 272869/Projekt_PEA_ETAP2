#include <cstring>
#include <climits>
#include "../Utils/Node.h"

class BFS {
private:
    int size;
    int minCost;
    int *bestPath;
    int allVertexMinCost;
    int *allVertexBestPath;
    int calculateCost(int* path, int** costMatrix, int pathSize);
    int lowerBound(int* currentPath, int** distances, int currentPathSize);


public:
    BFS(int n) : size(n), minCost(INT_MAX) {
        allVertexMinCost = INT_MAX;
        allVertexBestPath = nullptr;
    }
    ~BFS() {
        delete[] bestPath;
    }
    void showTheShortestPath();
    void showThePath(int** costMatrix);
    int startFromEachVertex(int** costMatrix);
    int bnb_bfs_run(int** costMatrix, int start);
};

