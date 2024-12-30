#include <iostream>
#include <string>

char ask(const std::string &answers) {
	char c = '\0';
	while (answers.find(c) == std::string::npos)
		std::cin >> c;
	return c;
}

int main()
{
	int beg = 1;
	int end = 100;
	int mid = (end + beg) / 2;

	std::cout << "Think of a number between 1 and 100!\n";
	bool found = false;
	while (!found && beg != mid) {
		std::cout << "\nIs your number " << mid << "? (y/n): ";
		char answer = ask("yn");
		if (answer == 'n') {
			std::cout << "Is your number less than " << mid << "? (y/n): ";
			answer = ask("yn");
			if (answer == 'n') {
				beg = mid + 1;
			} else {
				end = mid;
			}
			mid = (end + beg) / 2;
		} else {
			found = true;
		}
	}
	std::cout << "Your number was " << mid << "!\n";
}
