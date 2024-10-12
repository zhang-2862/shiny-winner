#include "Configuration.hh"

int main(int argc, char* argv[]) {
    Configuration::getConfigInstance()->printMap();
    Configuration::getConfigInstance()->printSet();

    return 0;
}

