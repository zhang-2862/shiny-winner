all: ConfigTest.exe DirScannerTest.exe DictProducerTest.exe test_jieba.exe PageLibTest.exe WebPageTest.exe PageLibPreprocessorTest.exe SearchEngineServer.exe

# # 生成 SearchEngineServer.exe
# SearchEngineServer.exe: bin/*.o
# 	g++ bin/*.o -o SearchEngineServer.exe

# 生成 SearchEngineServer.exe，排除所有 Test.o 文件
SearchEngineServer.exe: bin/Configuration.o bin/SplitTool.o bin/SplitToolCppJieba.o \
                        bin/Acceptor.o bin/Dictionary.o bin/EventLoop.o bin/InetAddress.o \
                        bin/KeyRecommender.o bin/Socket.o bin/SocketIO.o bin/TaskQueue.o \
                        bin/TcpConnection.o bin/TcpServer.o bin/WebPage.o  \
                        bin/WebPageQuery.o bin/WebPageSearcher.o bin/TestEchoserver.o bin/tinyxml2.o bin/Tlv.o bin/Echoserver.o \
						bin/ThreadPool.o
	g++ -o SearchEngineServer.exe $^

# 生成 DictProducerTest.exe
DictProducerTest.exe: bin/DictProducer.o bin/DictProducerTest.o bin/DirScanner.o bin/Configuration.o bin/SplitTool.o bin/SplitToolCppJieba.o 
	g++ bin/DictProducer.o bin/DictProducerTest.o bin/DirScanner.o bin/Configuration.o bin/SplitTool.o bin/SplitToolCppJieba.o -o DictProducerTest.exe

# 生成 ConfigTest.exe
ConfigTest.exe: bin/Configuration.o bin/ConfigTest.o
	g++ bin/Configuration.o bin/ConfigTest.o -o ConfigTest.exe

# 生成 DirScannerTest.exe
DirScannerTest.exe: bin/DirScanner.o bin/DirScannerTest.o
	g++ bin/DirScanner.o bin/DirScannerTest.o -o DirScannerTest.exe

# 生成test_jieba.exe
test_jieba.exe: bin/test_jieba.o 
	g++ bin/test_jieba.o -o test_jieba.exe

# 生成PageLibTest.exe
PageLibTest.exe: bin/PageLib.o bin/PageLibTest.o bin/tinyxml2.o bin/Configuration.o bin/DirScanner.o
	g++ bin/PageLib.o bin/PageLibTest.o bin/tinyxml2.o bin/Configuration.o bin/DirScanner.o -o PageLibTest.exe

# 生成WebPageTest.exe
WebPageTest.exe: bin/WebPage.o bin/tinyxml2.o bin/WebPageTest.o
	g++ bin/WebPage.o bin/tinyxml2.o bin/WebPageTest.o -o WebPageTest.exe

# 生成PageLibPreprocessorTest.exe
PageLibPreprocessorTest.exe: bin/PageLibPreprocessor.o bin/Configuration.o bin/WebPage.o bin/SplitTool.o bin/SplitToolCppJieba.o bin/tinyxml2.o bin/PageLibPreprocessorTest.o
	g++ bin/PageLibPreprocessor.o bin/Configuration.o bin/WebPage.o bin/SplitTool.o bin/SplitToolCppJieba.o bin/tinyxml2.o bin/PageLibPreprocessorTest.o -o PageLibPreprocessorTest.exe

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
bin/SplitToolCppJieba.o: src/SplitToolCppJieba.cc include/SplitToolCppJieba.hh include/cppjieba/Jieba.hpp
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
bin/WebPage.o: src/WebPage.cc include/WebPage.hh  include/tinyxml2.h
	g++ -c src/WebPage.cc -o bin/WebPage.o -g -I include

# 编译 PageLibPreprocessor.o
bin/PageLibPreprocessor.o: src/PageLibPreprocessor.cc include/PageLibPreprocessor.hh include/simhash/Simhasher.hpp
	g++ -c src/PageLibPreprocessor.cc -o bin/PageLibPreprocessor.o -g -I include
	
# 编译 WebPageTest.o: src/WebPageTest.cc 
bin/WebPageTest.o: src/WebPageTest.cc
	g++ -c src/WebPageTest.cc -o bin/WebPageTest.o -g -I include

# 编译 PageLibPreprocessorTest.o
bin/PageLibPreprocessorTest.o: src/PageLibPreprocessorTest.cc
	g++ -c src/PageLibPreprocessorTest.cc -o bin/PageLibPreprocessorTest.o -g -I include

# 编译 Acceptor.o
bin/Acceptor.o: src/Acceptor.cc include/Acceptor.h
	g++ -c src/Acceptor.cc -o bin/Acceptor.o -g -I include

# 编译 Dictionary.o
bin/Dictionary.o: src/Dictionary.cc include/Dictionary.hh
	g++ -c src/Dictionary.cc -o bin/Dictionary.o -g -I include

# 编译 EchoServer.o
bin/EchoServer.o: src/EchoServer.cc include/Echoserver.h
	g++ -c src/EchoServer.cc -o bin/EchoServer.o -g -I include

# 编译 EventLoop.o
bin/EventLoop.o: src/EventLoop.cc include/EventLoop.h
	g++ -c src/EventLoop.cc -o bin/EventLoop.o -g -I include

# 编译 InetAddress.o
bin/InetAddress.o: src/InetAddress.cc include/InetAddress.h
	g++ -c src/InetAddress.cc -o bin/InetAddress.o -g -I include

# 编译 KeyRecommender.o
bin/KeyRecommender.o: src/KeyRecommender.cc include/KeyRecommender.hh include/Tlv.hh
	g++ -c src/KeyRecommender.cc -o bin/KeyRecommender.o -g -I include

# 编译 Socket.o
bin/Socket.o: src/Socket.cc include/Socket.h
	g++ -c src/Socket.cc -o bin/Socket.o -g -I include

# 编译 SocketIO.o
bin/SocketIO.o: src/SocketIO.cc include/SocketIO.h
	g++ -c src/SocketIO.cc -o bin/SocketIO.o -g -I include

# 编译 TaskQueue.o
bin/TaskQueue.o: src/TaskQueue.cc include/TaskQueue.h
	g++ -c src/TaskQueue.cc -o bin/TaskQueue.o -g -I include

# 编译 TcpConnection.o
bin/TcpConnection.o: src/TcpConnection.cc include/TcpConnection.h
	g++ -c src/TcpConnection.cc -o bin/TcpConnection.o -g -I include

# 编译 TcpServer.o
bin/TcpServer.o: src/TcpServer.cc include/TcpServer.h
	g++ -c src/TcpServer.cc -o bin/TcpServer.o -g -I include

# 编译 TestEchoServer.o
bin/TestEchoserver.o: src/TestEchoserver.cc include/Echoserver.h
	g++ -c src/TestEchoserver.cc -o bin/TestEchoserver.o -g -I include

# 编译 ThreadPool.o
bin/ThreadPool.o: src/ThreadPool.cc include/ThreadPool.h
	g++ -c src/ThreadPool.cc -o bin/ThreadPool.o -g -I include

# 编译 WebPageQuery.o
bin/WebPageQuery.o: src/WebPageQuery.cc include/WebPageQuery.hh
	g++ -c src/WebPageQuery.cc -o bin/WebPageQuery.o -g -I include

# 编译 WebPageSearcher.o
bin/WebPageSearcher.o: src/WebPageSearcher.cc include/WebPageSearcher.hh include/Tlv.hh
	g++ -c src/WebPageSearcher.cc -o bin/WebPageSearcher.o -g -I include

bin/Tlv.o:src/Tlv.cc include/Tlv.hh
	g++ -c src/Tlv.cc -o bin/Tlv.o -I include/

bin/Echoserver.o:src/EchoServer.cc include/Echoserver.h
	g++ -c src/EchoServer.cc -o bin/Echoserver.o -I include/

# 清理目标文件
clean:
	rm -f bin/*.o ConfigTest.exe dirScanner.exe DictProducerTest.exe PageLibTest.exe

