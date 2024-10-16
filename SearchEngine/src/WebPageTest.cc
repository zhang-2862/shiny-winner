#include "WebPage.hh"  // 包含 WebPage 类
#include <iostream>
#include <cassert>  // 用于断言测试
#include <string>

using std::cout;
using std::cerr;
using std::endl;
using std::string;

void testValidXml() {
    cout << "Running testValidXml..." << endl;
    
    // 准备一个有效的 XML 文档
    string validXml = R"(
    <doc>
        <docid>123</docid>
        <title>Test Title</title>
        <link>http://example.com</link>
        <content>This is the content of the document.</content>
    </doc>
    )";

    // 创建 WebPage 对象
    WebPage webpage;
    webpage.setDoc(validXml);
    webpage.parseXml();

    // 断言解析后的内容是否正确
    assert(webpage.docId() == 123);
    assert(webpage.docTitle() == "Test Title");
    assert(webpage.docUrl() == "http://example.com");
    assert(webpage.docContent() == "This is the content of the document.");

    cout << "testValidXml passed!" << endl;
}


int main() {
    // 运行所有测试
    testValidXml();

    cout << "All tests passed!" << endl;
    return 0;
}

