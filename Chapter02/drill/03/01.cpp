#include <iostream>
#include <string>

int main()
{
	std::cout << "Enter the name of the person you want to write to:\n";
	std::string first_name;
	std::cin >> first_name;
	std::cout << "Dear " << first_name
			<< ",\n\tHow are you? I am fine. I miss you.\n"
			<< "When are you coming to visit?\n";
	std::cout << "Enter your friend's name:\n";
	std::string friend_name;
	std::cin >> friend_name;
	std::cout << "Have you seen " << friend_name << " lately?\n";
}
