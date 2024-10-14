#include "DictProducer.hh"
#include "SplitToolCppJieba.hh"

int main(int argc, char* argv[]) {
    SplitToolCppJieba cppjieba;
    DictProducer dictProducer("data/eng_copus",
                              "data/cn_copus",
                              &cppjieba);
    dictProducer.storeDict("data/dict.dat");
    dictProducer.storeIndex("data/dictIndex.dat");
    /* dictProducer.printDict(); */
    /* dictProducer.printIndex(); */
    return 0;
}

