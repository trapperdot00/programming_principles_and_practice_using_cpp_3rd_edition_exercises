#include "Person.h"

#include <iostream>
#include <vector>
#include <utility>

int main() {
	std::vector<Person> persons;
	std::cout << "Enter people:\n";
	for (Person p; std::cin >> p; )
		persons.push_back(std::move(p));

	std::cout << "\nPeople:\n";
	for (const Person& p : persons)
		std::cout << p << '\n';
}
