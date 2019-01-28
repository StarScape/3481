#include <cstdlib>
#include <iostream> // for std::cout , etc.
#include <iomanip>  // additional formatting for cout
#include <cstdint>  // standard int types like uint64_t 
#include <stdio.h> // in case you want to use printf
#include "Tools.h" // Tools function declarations


using namespace std;
using namespace Tools;  

int main(int argc, char *argv[])
{
	// Test code here...
   uint64_t x = 0x0123456789abcdef;
   char buf[72];
   expandBits(x, buf);
   printf("%s\n", buf);
}



