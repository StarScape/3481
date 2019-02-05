#include <iostream>
#include <string>

#include "Disassembler.h"
#include "Tools.h"

using namespace std;

// Contains functions to translate hex instructions to
// their approaite mnemonic strings, along with helper functions
namespace Disassembler {

	string getRegName(int regNum)
	{
		string name;
		switch (regNum)
		{
			case 0:
				name = "%rax";
				break;
			case 1:
				name = "%rcx";
				break;
			case 2:
				name = "%rdx";
				break;
			case 3:
				name = "%rbx";
				break;
			case 4:
				name = "%rsp";
				break;
			case 5:
				name = "%rbp";
				break;
			case 6:
				name = "%rsi";
				break;
			case 7:
				name = "%rdi";
				break;
			case 8:
				name = "%r8";
				break;
			case 9:
				name = "%r9";
				break;
			case 10:
				name = "%r10";
				break;
			case 11:
				name = "%r11";
				break;
			case 12:
				name = "%r12";
				break;
			case 13:
				name = "%r13";
				break;
			case 14:
				name = "%r14";
				break;
		}

		return name;
	}

	// Helper methods to get rA and rB reg names
	string getRA(string instruction)
	{
		int regNum = Tools::hexToInt(instruction.substr(2, 1));
		return getRegName(regNum);
	}

	string getRB(string instruction)
	{
		int regNum = Tools::hexToInt(instruction.substr(3, 1));
		return getRegName(regNum);
	}

	int getFn(string instruction)
	{
		return Tools::hexToInt(instruction.substr(1, 1));
	}

	// Get's an immediate value/destination, i specifies start position
	string getImmediate(string instruction, int i)
	{
		string raw = instruction.substr(i, 16);
		string flipped("");

		for(int i = 7; i >= 0; i--)
		{
			flipped += raw.substr(i*2, 2);
		}

		size_t firstNonZero = flipped.find_first_not_of("0");
		string val = "0";

		// If not all zeros 
		if (firstNonZero != (size_t) -1)
			val = flipped.substr(firstNonZero, flipped.length() - firstNonZero);

		return "0x" + val;
	}

	// Get immediate for the most common use case (irmovq, rmmovq, and mrmovq)
	string getImmediate(string instruction)
	{
		return getImmediate(instruction, 4);
	}

	// For call and jxx, really just a clever use of getImmediate
	string getDest(string instruction)
	{
		return getImmediate(instruction, 2);
	}

	/*--------------------------------------------------------------------------
	The following functions return the approriate string for each hex instruction.
	We have chosen to get the hex string as strings because, well, turns out its simpler that way.
	----------------------------------------------------------------------------*/
	string halt(string instruction)
	{
		return "halt";
	}

	string nop(string instruction)
	{
		return "nop";
	}


	string rrmovq(string instruction)
	{
		string rA = getRA(instruction);
		string rB = getRB(instruction);

		return "rrmovq " + rA + ", " + rB;
	}

	string irmovq(string instruction)
	{
		string imm = getImmediate(instruction);
		string rB = getRB(instruction);

		return "irmovq    $" + imm + ", " + rB;
	}

	string rmmovq(string instruction)
	{
		string rA = getRA(instruction);
		string rB = getRB(instruction);
		string D = getImmediate(instruction);

		return "rmmovq    " + rA + ", $" + D + "(" + rB + ")";
	}

	string mrmovq(string instruction)
	{
		string rA = getRA(instruction);
		string rB = getRB(instruction);
		string imm = getImmediate(instruction);

		return "mrmovq    $" + imm + "(" + rB + "), " + rA;
	}

	string opq(string instruction)
	{
		string mnemonic = "";
		string rA = getRA(instruction);
		string rB = getRB(instruction);
		int fn = getFn(instruction);

		switch (fn)
		{
			case 0:
				mnemonic = "addq      ";
				break;
			case 1:
				mnemonic = "subq      ";
				break;
			case 2:
				mnemonic = "andq      ";
				break;
			case 3:
				mnemonic = "xorq      ";
				break;
		}

		return mnemonic + rA + ", " + rB;
	}

	string jxx(string instruction)
	{
		string mnemonic = "";
		string rA = getRA(instruction);
		string rB = getRB(instruction);
		int fn = getFn(instruction);
		string dest = getDest(instruction);

		switch (fn)
		{
			case 0:
				mnemonic = "jmp       ";
				break;
			case 1:
				mnemonic = "jle       ";
				break;
			case 2:
				mnemonic = "jl        ";
				break;
			case 3:
				mnemonic = "je        ";
				break;
			case 4:
				mnemonic = "jne       ";
				break;
			case 5:
				mnemonic = "jge       ";
				break;
			case 6:
				mnemonic = "jg        ";
				break;
		}

		return mnemonic + dest;
	}

	string cmovxx(string instruction)
	{
		string mnemonic("cmov");
		string rA = getRA(instruction);
		string rB = getRB(instruction);
		int fn = getFn(instruction);

		switch (fn)
		{
			case 1:
				mnemonic += "le    ";
				break;
			case 2:
				mnemonic += "l     ";
				break;
			case 3:
				mnemonic += "e     ";
				break;
			case 4:
				mnemonic += "ne    ";
				break;
			case 5:
				mnemonic += "ge    ";
				break;
			case 6:
				mnemonic += "g     ";
				break;
		}
		mnemonic += "" + rA + ", " + rB;

		return mnemonic;
	}

	string call(string instruction)
	{
		string dest = getDest(instruction);
		string mnemonic = "call      ";
		return mnemonic + dest;
	}

	string ret(string instruction)
	{
		return "ret";
	}

	string pushq(string instruction)
	{
		return "pushq    " + getRA(instruction);
	}

	string popq(string instruction)
	{
		return "popq     " + getRA(instruction);
	}

	string quad(string instruction)
	{
		string flipped = "";
		for (int i = 7; i >= 0; i--)
			flipped += instruction.substr(i*2, 2);

		return ".quad     0x" + flipped;
	}

	// rrmovq and cmov have the same opcode, so we check and call the approriate function
	string rrmovqOrCmovxx(string instruction)
	{
		if (instruction.at(1) == '0')
		{
			return rrmovq(instruction);
		}
		else
		{
			return cmovxx(instruction);
		}
	}
}
