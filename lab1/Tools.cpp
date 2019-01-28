/*
    Utility functions (e.g., for bit/byte manipulations) used in Y86 simulator.
    
    Author:    
    version:    
*/
#include <cstdlib>
#include <iostream>
#include <cassert>
#include <cstdint>
#include "Tools.h"

namespace Tools {
    
/*-----------------------------------------------------------------------------------------------
    getBits
	Extracts bits 'low' to 'high' (inclusive) from 'source' and returns the result as
	an 64-bit integer. 
	Example:
	
	getBits(12,15,0x0123456789abcdef);
	
	would return the value:
	
	0x00000000000000c;
	
	(Bits 12-15 of the 64-bit word, counting from the right correspond to hex digit 'c' in the
	source word. Note that any number of bits from 1 to 64 could be specified depending on the values
	of 'low' and 'high'.
	The value of high must be greater than or equal to low and high must be in the range 0 to 63. 
------------------------------------------------------------------------------------------------*/
uint64_t getBits(unsigned low, unsigned high, uint64_t source)
{
    assert(high < 64 && low <= high);
    uint64_t mask = (uint64_t) -1 >> (64 - (high - low + 1));
    uint64_t out = (source >> low) & mask;

    return out;
}
/*-----------------------------------------------------------------------------------------------
    setBits
	Sets (to 1) the bits from bit numbers 'low' to 'high' (inclusive) in 
	the source word and returns the resulting word.
	
	The value of high must be greater than or equal to low and high must be in the range 0 to 63. 
------------------------------------------------------------------------------------------------*/
uint64_t setBits(unsigned low, unsigned high, uint64_t source)
{
    assert(high < 64 && low <= high);
    uint64_t mask = (uint64_t) -1 >> (64 - (high - low + 1));
    mask <<= low;
    uint64_t out = (source >> low) | mask;

    return out;
}
/*-----------------------------------------------------------------------------------------------
    clearBits
	
	Clears (to 0) the bits from bit numbers 'low' to 'high' (inclusive) in 
	the source word and returns the resulting word.
	
	The value of high must be greater than or equal to low and high must be in the range 0 to 63. 
------------------------------------------------------------------------------------------------*/
uint64_t clearBits(unsigned low, unsigned high, uint64_t source)
{
    assert(high < 64 && low <= high);
    uint64_t mask = (uint64_t) -1 >> (64 - (high - low + 1));
    mask <<= low;
    uint64_t out = source & ~mask;

    return out;
}

/*-----------------------------------------------------------------------------------------------
    assignOneBit
	Sets the bit number 'bitNum' to the binary value (0 or 1) specified by 'bitVal' in
	the source word and returns the resulting word.
	
	'bitNum' must be in the range 0 to 63 (inclusive) and 'bitVal' must be 0 or 1.
------------------------------------------------------------------------------------------------*/
uint64_t assignOneBit(unsigned bitNum, unsigned bitVal, uint64_t source)
{
    assert(bitNum < 64 && (bitVal == 0 || bitVal == 1));
    uint64_t mask = (uint64_t) 1 << bitNum;
    if (bitVal == 0)
    {
        return source & ~mask; 
    }
    return source | mask;
}

/*-----------------------------------------------------------------------------------------------
    getByteNumber
	Returns the specified byte number from the source word.
	
	Example:
	getByteNumber(3,0x0011223344556677);
	
	will return the single byte value:
	
	0x44
	
	(Note that the '3' refers to byte 3 of a 8-byte unsigned integer (bytes are numbered from
	the right starting at 0 when looking at a word value in hex). 
------------------------------------------------------------------------------------------------*/
uint8_t getByteNumber(unsigned byteNum, uint64_t source)
{
    assert(byteNum < 8);
    return getBits(byteNum*8, byteNum*8 + 7, source);
}
/*-----------------------------------------------------------------------------------------------
    putByteNumber
	Returns the source word after replacing the specified byte (byteNum) with a given 
	byte value (byteVal).
	
	Example:
	putByteNumber(3,0x00,0x0011223344556677);
	
	will return the value:
	
	0x0011223300556677
	
	(Note that the '3' refers to byte 3 of a 8-byte unsigned integer (bytes are numbered from
	the right starting at 0 when looking at a word value in hex). 
------------------------------------------------------------------------------------------------*/
uint64_t putByteNumber(unsigned byteNum, uint8_t byteVal, uint64_t source)
{
    assert(byteNum < 8);
    unsigned startPos = byteNum*8;
    unsigned endPos = startPos + 8;
    uint64_t newNum = source;
    
    for (unsigned i = startPos; i < endPos; i++)
    {
      uint64_t desiredBit = getBits(i - startPos, i - startPos, byteVal);
      newNum = assignOneBit(i, desiredBit, newNum);
    }
    return newNum;
}
/*-----------------------------------------------------------------------------------------------
    buildWord
	
	Returns a 64 bit word consisting of the 8 parameter bytes, where b0 is the least significant
	and b7 is the most significant byte.
------------------------------------------------------------------------------------------------*/
uint64_t buildWord(unsigned char b0, unsigned char b1,unsigned char b2, unsigned char b3,
                          unsigned char b4, unsigned char b5,unsigned char b6, unsigned char b7)
{
    assert(b0 <= 0xff && b1 <= 0xff && b2 <= 0xff && b3 <= 0xff && b4 <= 0xff &&
           b5 <= 0xff && b6 <= 0xff && b7 <= 0xff); 

    return (uint64_t) b0 |
           (uint64_t) b1 << 8 |
           (uint64_t) b2 << 16 |
           (uint64_t) b3 << 24 |
           (uint64_t) b4 << 32 |
           (uint64_t) b5 << 40 |
           (uint64_t) b6 << 48 |
           (uint64_t) b7 << 56;
}
/*-----------------------------------------------------------------------------------------------
    isNegative

	Returns true if the input parameter is negative when interpreted as a signed value.
------------------------------------------------------------------------------------------------*/
bool isNegative(uint64_t source)
{
    return (getBits(63, 63, source) == 1);
}
/*-----------------------------------------------------------------------------------------------
    expandBits
	
	Reads the source and converts it to a character string consisting of 72 bytes--71 characters
	followed by a '\0' character (string terminator).
	Example usage: 
		char buf[72];
		expandBits(0xAABBCCDDEE001122UL,buf);

		Will cause the following string to be written to the buf[] array (not including quotes):
	
	"10101010 10111011 11001100 11011101 11101110 00000000 00010001 00100010"
	
	Note the space after every group of 8 digits except the last. The last byte of
	the string is the '\0' byte, that is not printable but used to indicate the end
	of a C string.
------------------------------------------------------------------------------------------------*/
void expandBits(uint64_t source, char *bits)
{
    assert(bits != __null);
    int biti = 63;
    int bufi = 0;
    while (biti >= 0)
    {
        char bitChar = getBits(biti, biti, source) + 48;  
        bits[bufi++] = bitChar;
        //printf("%c", bitChar);
        if ((biti % 8) == 0 && biti != 0) {
          //printf("%d ", biti);
          bits[bufi] = ' ';
          bufi++;
        }

        biti--;
    }
    bits[71] = 0;
    return;
}
/*-----------------------------------------------------------------------------------------------
    clearBuffer
	Treats pbuf as a pointer to an array of 'size' bytes and clears them all to zero.
------------------------------------------------------------------------------------------------*/
void clearBuffer(char * pbuf, int size)
{
    assert(pbuf != __null && size >= 0 && size <= 2147483647);
    for (int i = 0; i < size; i++)
    {
        pbuf[i] = (uint8_t) 0;
    } 
    return;
}

} // end namespace Y86
