#include "Utils/ConfigFile.h"

int main(){
    ConfigFile configHandler("C:\\Users\\pitko\\Desktop\\Studia\\PEA\\Projekt_etap2\\cmake-build-debug\\config.txt");
    configHandler.parseConfig();
}
