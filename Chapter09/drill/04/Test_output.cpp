#include <iostream>

int main() {
	int birth_year{2005};

	std::cout << "Decimal\tHexadecimal\tOctal\n"
		<< birth_year << '\t'
		<< std::hex << birth_year << "\t\t"
		<< std::oct << birth_year << '\n'
		<< std::dec;
}
