CXX = g++
CXXFLAGS = -Wall -g -std=c++11
OBJ = main.o Disassembler.o Tools.o

build: main.o Tools.o Disassembler.o
	$(CXX) $(CXXFLAGS) $(OBJ)  -o dis

main.o: src/main.cpp src/Tools.h src/Disassembler.h
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o main.o

Disassembler.o: src/Disassembler.cpp src/Disassembler.h
	$(CXX) $(CXXFLAGS) -c src/Disassembler.cpp -o Disassembler.o

Tools.o: src/Tools.cpp src/Tools.h
	$(CXX) $(CXXFLAGS) -c src/Tools.cpp -o Tools.o

clean:
	rm -f *.o