#include <iostream>
#include <valarray>
#include "Algorithms/BranchAndBound.h"

int main() {
    FileReader dataReader;
    int size;
    int** matrix;
    matrix = dataReader.readFile("C:\\Users\\pitko\\Desktop\\Studia\\PEA\\Projekt_etap2\\cmake-build-debug\\matrix6.atsp",size);
//    matrix = dataReader.generateRandomAsymmetricalData(n);
//    dataReader.printMatrix(matrix,3);


    BranchAndBound bbLowestCost;
    Result result1= bbLowestCost.startFromEachVertex(matrix,size);
    Result result2 = bbLowestCost.branchAndBound(matrix,size,0);
    BranchAndBound::showPath(result2,size);
    BranchAndBound::showPath(result1,size);
    return 0;
}
