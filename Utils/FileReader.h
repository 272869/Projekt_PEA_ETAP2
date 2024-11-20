#ifndef FILEREADER_H
#define FILEREADER_H
#include <string>
using namespace std;

class FileReader{
public:
    int** tab;
    int size;
    FileReader() {
        this->size = 0;
        tab = NULL;
    }
    int** loadFromFile(std::string path);
    int** loadRandomData(int N, int sand);
    void alocate(int N);
    void dealocate();
    void showTab();
    void ordertable(int randtab[], int number);
    void randomshuttle(int randtab[], int number, int testnumber, int lpoj);
};

#endif // !FILEREADER_H