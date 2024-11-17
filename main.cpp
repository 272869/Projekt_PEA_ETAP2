#include <iostream>
#include "Algorithms/BranchAndBound.h"

int main() {
    BranchAndBound *branchAndBound;
    //std::cout << "elo1" << std::endl;
    branchAndBound = new BranchAndBound();
    //std::cout << "elo2" << std::endl;
    if (branchAndBound->getMatrix() != nullptr)
        std::cout << "elo3" << std::endl;
        branchAndBound->printMatrixWages();
        branchAndBound->branchAndBoundAlgorithm();
    std::cout << "elo4" << std::endl;
    //delete branchAndBound;
    //std::cout << "elo5" << std::endl;
    return 0;
}
