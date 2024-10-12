#include "DictProducer.hh"

int main(int argc, char* argv[]) {
    DictProducer dictProducer("data/eng_copus");
    dictProducer.storeDict("data/dict.dat");
    dictProducer.storeIndex("data/dictIndex.dat");
    /* dictProducer.printDict(); */
    dictProducer.printIndex();
    return 0;
}

