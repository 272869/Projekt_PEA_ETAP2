
#include <fstream>

class FileReader{
public:
    bool openFile();
    static int** readFile(const std::string& path, int& size);
    int getDataFromFile();

    ~FileReader() {
        file.close();
    }
private:

    std::fstream file;
};

