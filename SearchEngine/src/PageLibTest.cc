#include "PageLib.hh"

int main(void) {
    DirScanner dirScanner;
    PageLib pagelib(dirScanner);
    
    pagelib.create();
    pagelib.store();

    return 0;
}
