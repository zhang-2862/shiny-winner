#include "PageLibPreprocessor.hh"
#include "SplitToolCppJieba.hh"

int main(void) {
    SplitToolCppJieba jieba;
    PageLibPreprocessor preprocessor(&jieba);

    /* preprocessor.printTF_map(); */
    /* preprocessor.printDF_map(); */
    preprocessor.buildInvetIndexTable();
    preprocessor.StoreOnDisk();
}
