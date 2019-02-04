#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <map>

#include "Tools.h"
#include "Disassembler.h"

int main()
{
    using namespace std;

    map<char, string (*)(string)> opcodeFunctions;

    opcodeFunctions[0]  = Disassembler::halt;
    opcodeFunctions[1]  = Disassembler::nop;
    opcodeFunctions[2]  = Disassembler::rrmovq;
    opcodeFunctions[3]  = Disassembler::irmovq;
    opcodeFunctions[4]  = Disassembler::rmmovq;
    opcodeFunctions[5]  = Disassembler::mrmovq;
    opcodeFunctions[6]  = Disassembler::opq;
    opcodeFunctions[7]  = Disassembler::jxx;
    opcodeFunctions[8]  = Disassembler::call;
    opcodeFunctions[9]  = Disassembler::ret;
    opcodeFunctions[10] = Disassembler::pushq;
    opcodeFunctions[11] = Disassembler::popq;

    ifstream input("test.obj");
    if (!input)
    {
        cerr << "The input file could not be read" << endl;
        exit(1);
    }
 
    while (input)
    {
        string line;
        string out;
        getline(input, line);
        int len = line.length();
        if (len < 1) continue;

        string addr = line.substr(0, 5);
        string instructionStr = line.substr(7, line.length() - 1);
		
		// Strip whitespace		
		size_t last = instructionStr.find_last_not_of(' ');
		string instruction = instructionStr.substr(0, last + 1);

        if (instructionStr.at(0) == ' ')
        {
         	// blank line
        }

        else if (instruction.length() == 8)
        {
         	// quad TODO: test
        }

        else
        {
        	// Get opcode and convert to  
        	char opcode = instruction.at(0) - 48;
        	opcodeFunctions[opcode](instruction);
        }
    }
    
    return 0;
}
