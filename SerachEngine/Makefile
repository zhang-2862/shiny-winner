all: ConfigTest.exe
ConfigTest.exe: bin/Configuration.o bin/ConfigTest.o
	g++ bin/Configuration.o bin/ConfigTest.o -o configTest.exe
bin/Configuration.o: src/Configuration.cc include/Configuration.hh
	g++ -c src/Configuration.cc -o bin/Configuration.o -g -I include
bin/ConfigTest.o: src/ConfigTest.cc
	g++ -c src/ConfigTest.cc -o bin/ConfigTest.o -g -I include
