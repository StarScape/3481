CXX = g++
CXXFLAGS = -Wall -ggdb -std=c++11
OBJ = bin/main.o bin/Disassembler.o bin/Tools.o

build: $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ)  -o y86dis

bin/main.o: src/main.cpp src/Tools.h src/Disassembler.h
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o bin/main.o

bin/Disassembler.o: src/Disassembler.cpp src/Disassembler.h
	$(CXX) $(CXXFLAGS) -c src/Disassembler.cpp -o bin/Disassembler.o

bin/Tools.o: src/Tools.cpp src/Tools.h
	$(CXX) $(CXXFLAGS) -c src/Tools.cpp -o bin/Tools.o

test:
	ls ./Test/*.obj | xargs -n 1 y86dis | tr -d [:blank:] > alloutput
	ls ./Test/*.obj | xargs -n 1 efbdis | tr -d [:blank:] >  efboutput 
	diff alloutput efboutput > diffoutput

clean:
	rm -f *.o