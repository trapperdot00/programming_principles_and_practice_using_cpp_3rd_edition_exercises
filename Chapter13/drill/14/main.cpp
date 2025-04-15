#include "Person.h"

#include <iostream>

int main() {
	Person p{"Goofy", 63};
	std::cout << p.name << ' ' << p.age << '\n';
}
