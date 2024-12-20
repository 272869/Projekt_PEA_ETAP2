#ifndef TEST_H
#define TEST_H
#include "FileReader.h"


class Test {
public:
    void startTests();

private:
    FileReader file_reader;
    FileReader file_readerSYM;
    long long calculateTime(int algorithm, int** tab);
    static void saveToCsvFile(std::string fileName, long long time , int size);
    static void saveToCsvFile(std::string fileName, std::string message);
    void typeOfDataMessage(std::string message);


};



#endif //TEST_H
