#include <iostream>

// According to cppreference.com, the C++ standard defines that
//  - int should have at least 16 bits (2 bytes),
//  - double usually uses the IEEE-754 binary64 format (64 bits / 8 bytes)
//  - bool's size is implementation defined, and might differ from 1 bytes
//
// My machine's data model is LP64, which defines
//  - int's size to be 32 bits (4 bytes)
//  - long's size to be 64 bits (8 bytes)
//  - pointer sizes to be 64 bits (8 bytes)

int main()
{
	std::cout << "sizeof(int)   : " << sizeof(int)    << '\n'; // 4
	std::cout << "sizeof(double): " << sizeof(double) << '\n'; // 8
	std::cout << "sizeof(bool)  : " << sizeof(bool)   << '\n'; // 1
}
