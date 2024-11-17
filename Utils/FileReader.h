
#include <fstream>

class FileReader{
public:
    bool openFile();

    int getDataFromFile();

    ~FileReader() {
        file.close();
    }
private:

    std::fstream file;
};

