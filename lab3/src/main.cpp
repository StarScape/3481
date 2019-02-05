/*
    Systems I, Lab 3
    Jack Arrington and Jack Elliot

    SOME NOTES:

        * We used the std::map structure, as suggested.
        * The program output aligns just the same as yours,
          but we choose to omit some of the trailing whitespace
          because we couldn't see the point of it.
*/
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <map>

#include "Tools.h"
#include "Disassembler.h"

int main(int argc, char *argv[])
{
    using namespace std;

    // Opcodes and the associated function pointers
    // to translate them to strings
    map<char, string (*)(string)> opcodeFunctions;
    opcodeFunctions[0]  = Disassembler::halt;
    opcodeFunctions[1]  = Disassembler::nop;
    opcodeFunctions[2]  = Disassembler::rrmovqOrCmovxx;
    opcodeFunctions[3]  = Disassembler::irmovq;
    opcodeFunctions[4]  = Disassembler::rmmovq;
    opcodeFunctions[5]  = Disassembler::mrmovq;
    opcodeFunctions[6]  = Disassembler::opq;
    opcodeFunctions[7]  = Disassembler::jxx;
    opcodeFunctions[8]  = Disassembler::call;
    opcodeFunctions[9]  = Disassembler::ret;
    opcodeFunctions[10] = Disassembler::pushq;
    opcodeFunctions[11] = Disassembler::popq;

    if (argc < 2)
    {
        cerr << "No input file!" << endl;
        return 0;
    }

    ifstream input(argv[1]);
    string out;

    if (!input)
    {
        cerr << "The input file could not be read" << endl;
        exit(1);
    }
 
    while (input)
    {
        string line;
        getline(input, line);
        int len = line.length();
        if (len < 1) continue;

        string addr = line.substr(0, 5);
        string instructionStr = line.substr(7, line.length() - 1);
		
		// Strip whitespace		
		size_t last = instructionStr.find_last_not_of(' ');
		string instruction = instructionStr.substr(0, last + 1);
        string mnemonic;

        // Blank line
        if (instructionStr.at(0) == ' ')
        {
            mnemonic = "";
        }

        // Quad
        else if (instruction.length() == 16)
        {
            mnemonic = Disassembler::quad(instruction);
        }

        // An instruction
        else
        {
            // Get opcode and convert to char
            char opcode = Tools::hexToInt(instruction.substr(0, 1));
            if (opcode > 11)
                mnemonic = "illegal op";
            else
                mnemonic = opcodeFunctions[opcode](instruction);
        }

        out += addr + ":    " + mnemonic + "\n";
    }

    cout << out;
    return 0;
}
