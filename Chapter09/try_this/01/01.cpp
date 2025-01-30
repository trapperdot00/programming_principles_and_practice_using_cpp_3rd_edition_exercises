#include <iostream>
#include <chrono>

using namespace std::chrono;

int main() {
	constexpr int birth_year{2005};
	std::cout << "\t\tDecimal\t" << "Hexadecimal\t" << "Octal\n"
		<< "Birth year\t"
		<< birth_year << '\t'
		<< std::hex << birth_year << "\t\t"
		<< std::oct << birth_year << '\n'
		<< std::dec;	// Reset to default base
	int current_year{
		static_cast<int>(year_month_day{time_point_cast<days>(system_clock::now())}.year())
	};
	int age = current_year - birth_year;
	std::cout << "Age\t\t"
		<< age << '\t'
		<< std::hex << age << "\t\t"
		<< std::oct << age << '\n'
		<< std::dec;
}
