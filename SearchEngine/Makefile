all: ConfigTest.exe DirScannerTest.exe DictProducerTest.exe  

# 生成 DictProducerTest.exe
DictProducerTest.exe: bin/DictProducer.o bin/DictProducerTest.o bin/DirScanner.o bin/Configuration.o
	g++ bin/DictProducer.o bin/DictProducerTest.o bin/DirScanner.o bin/Configuration.o -o DictProducerTest.exe


# 生成 ConfigTest.exe
ConfigTest.exe: bin/Configuration.o bin/ConfigTest.o
	g++ bin/Configuration.o bin/ConfigTest.o -o configTest.exe

# 生成 DirScannerTest.exe
DirScannerTest.exe: bin/DirScanner.o bin/DirScannerTest.o
	g++ bin/DirScanner.o bin/DirScannerTest.o -o dirScanner.exe

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

# 清理目标文件
clean:
	rm -f bin/*.o ConfigTest.exe dirScanner.exe DictProducerTest.exe

