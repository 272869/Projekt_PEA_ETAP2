#include "Utils/ConfigFile.h"

int main(){
    ConfigFile configHandler("config.txt");
    configHandler.parseConfig();

    std::cout << std::endl << "Wcisnij ENTER aby zakonczyc program";
    std::cin.get();
    return 0;
}
