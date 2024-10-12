#include "Configuration.hh"

int main(int argc, char* argv[]) {
    Configuration::getInstance()->printMap();
    Configuration::getInstance()->printSet();

    return 0;
}

