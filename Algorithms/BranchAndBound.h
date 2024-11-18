
#include <climits>
#include "../Utils/Node.h"
#include "../Utils/Matrix.h"
#include "../Utils/Result.h"
#include <queue>

class BranchAndBound {
public:
    Result branchAndBound(int** dist, int N, int start);   // Główna metoda branch and bound z argumentem start
    Result startFromEachVertex(int** dist, int N);          // Metoda wywołująca branch and bound dla każdego wierzchołka
    static int  calculateBound(Node* node, int** dist, int N);
    static void showPath(const Result& result, int size);

private:
    int bestCost;
    Node* bestNode;

};

