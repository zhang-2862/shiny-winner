all: ConfigTest.exe DirScannerTest.exe DictProducerTest.exe test_jieba.exe PageLibTest.exe

# 生成 DictProducerTest.exe
DictProducerTest.exe: bin/DictProducer.o bin/DictProducerTest.o bin/DirScanner.o bin/Configuration.o bin/SplitTool.o bin/SplitToolCppJieba.o 
	g++ bin/DictProducer.o bin/DictProducerTest.o bin/DirScanner.o bin/Configuration.o bin/SplitTool.o bin/SplitToolCppJieba.o -o DictProducerTest.exe

# 生成 ConfigTest.exe
ConfigTest.exe: bin/Configuration.o bin/ConfigTest.o
	g++ bin/Configuration.o bin/ConfigTest.o -o configTest.exe

# 生成 DirScannerTest.exe
DirScannerTest.exe: bin/DirScanner.o bin/DirScannerTest.o
	g++ bin/DirScanner.o bin/DirScannerTest.o -o DirScannerTest.exe

# 生成test_jieba.exe
test_jieba.exe: bin/test_jieba.o 
	g++ bin/test_jieba.o -o test_jieba.exe

# 生成PageLibTest.exe
PageLibTest.exe: bin/PageLib.o bin/PageLibTest.o bin/tinyxml2.o bin/Configuration.o bin/DirScanner.o
	g++ bin/PageLib.o bin/PageLibTest.o bin/tinyxml2.o bin/Configuration.o bin/DirScanner.o -o PageLibTest.exe

# 编译 DictProducer.o
bin/DictProducer.o: src/DictProducer.cc include/DictProducer.hh
	g++ -c src/DictProducer.cc -o bin/DictProducer.o -g -I include

# 编译 DirScanner.o (删除重复定义)
bin/DirScanner.o: src/DirScanner.cc include/DirScanner.hh
	g++ -c src/DirScanner.cc -o bin/DirScanner.o -g -I include

# 编译 Configuration.o
bin/Configuration.o: src/Configuration.cc include/Configuration.hh
	g++ -c src/Configuration.cc -o bin/Configuration.o -g -I include

# 编译 DictProducerTest.o
bin/DictProducerTest.o: src/DictProducerTest.cc
	g++ -c src/DictProducerTest.cc -o bin/DictProducerTest.o -g -I include

# 编译 DirScannerTest.o
bin/DirScannerTest.o: src/DirScannerTest.cc
	g++ -c src/DirScannerTest.cc -o bin/DirScannerTest.o -g -I include

# 编译 ConfigTest.o
bin/ConfigTest.o: src/ConfigTest.cc
	g++ -c src/ConfigTest.cc -o bin/ConfigTest.o -g -I include

# 编译 test_jieba.o
bin/test_jieba.o: src/test_jieba.cc include/cppjieba/Jieba.hpp
	g++ -c src/test_jieba.cc -o bin/test_jieba.o -g -I include

# 编译 SplitTool.o
bin/SplitTool.o: src/SplitTool.cc include/SplitTool.hh
	g++ -c src/SplitTool.cc -o bin/SplitTool.o -g -I include

# 编译 SplitToolCppJieba.o
bin/SplitToolCppJieba.o: src/SplitToolCppJieba.cc include/SplitToolCppJieba.hh
	g++ -c src/SplitToolCppJieba.cc -o bin/SplitToolCppJieba.o -g -I include

# 编译 PageLibTest.o
bin/PageLibTest.o: src/PageLibTest.cc
	g++ -c src/PageLibTest.cc -o bin/PageLibTest.o -g -I include

# 编译 PageLib.o
bin/PageLib.o: src/PageLib.cc include/PageLib.hh
	g++ -c src/PageLib.cc -o bin/PageLib.o -g -I include

# 编译 tinyxml2.o
bin/tinyxml2.o: src/tinyxml2.cc include/tinyxml2.h
	g++ -c src/tinyxml2.cc -o bin/tinyxml2.o -g -I include

# 编译 WebPage.o
bin/WebPage.o: src/WebPage.cc include/WebPage.hh
	g++ -c src/WebPage.cc -o bin/WebPage.o -g -I include

# 编译 PageLibPreprocessor.o
bin/PageLibPreprocessor.o: src/PageLibPreprocessor.cc bin/PageLibPreprocessor.hh
	g++ -c src/PageLibPreprocessor.cc -o bin/PageLibPreprocessor.o -g -I include
	

	

# 清理目标文件
clean:
	rm -f bin/*.o ConfigTest.exe dirScanner.exe DictProducerTest.exe PageLibTest.exe

