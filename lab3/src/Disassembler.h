/*
    File:   Tools.h
    Desc:   Declarations for utility functions used in
            Y86 simulator.
*/    
#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H
#include <cstdint>
#include <iostream>
#include <string>

namespace Disassembler {
    std::string halt(std::string instruction);
    std::string nop(std::string instruction);
    std::string rrmovq(std::string instruction);
    std::string irmovq(std::string instruction);
    std::string rmmovq(std::string instruction);
    std::string mrmovq(std::string instruction);
    std::string opq(std::string instruction);
    std::string jxx(std::string instruction);
    std::string call(std::string instruction);
    std::string ret(std::string instruction);
    std::string pushq(std::string instruction);
    std::string popq(std::string instruction);
}

#endif
