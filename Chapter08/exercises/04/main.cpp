#include "Name_pairs.h"

int main() {
	Name_pair np1{"adam", 54};
	Name_pair np2{np1};
	Name_pair np3{"david", 43};
	Name_pair np4;
	std::string name{"gabe"};
	Name_pair np5{name, 18};

	std::cout << "np1: " << np1
		<< "\nnp2: " << np2
		<< "\nnp3: " << np3
		<< "\nnp4: " << np4
		<< "\nnp5: " << np5
		<< '\n';

	std::cout << "np5: name: " << np5.name()
		<< " age: " << np5.age() << '\n';

	std::cout << std::boolalpha
		<< "\nnp1 == np2: " << (np1 == np2)
		<< "\nnp1 != np2: " << (np1 != np2)
		<< "\nnp1 == np3: " << (np1 == np3)
		<< "\nnp1 != np3: " << (np1 != np3)
		<< "\n\n";

	Name_pairs nps1;
	nps1.read();
	std::cout << "\nName-age pairs (size " << nps1.size() << "):\n" << nps1;

	nps1.sort();
	std::cout << "\nSorted name-age pairs:\n" << nps1;

	std::cout << "\nManual printing #1 (get()):\n";
	auto vec = nps1.get();
	for (const auto& pair : vec)
		std::cout << pair.name() << " | " << pair.age() << '\n';

	std::cout << "\nManual printing #2 (subscript):\n";
	for (Name_pairs::size_type i = 0; i < nps1.size(); ++i)
		std::cout << nps1[i].name() << " | " << nps1[i].age() << '\n';

	const auto nps2{nps1};
	std::cout << "\nManual printing #3 (get() const):\n";
	auto cvec = nps2.get();
	for (const auto& pair : cvec)
		std::cout << pair.name() << " | " << pair.age() << '\n';

	std::cout << "\nManual printing #4 (const subscript):\n";
	for (Name_pairs::size_type i = 0; i < nps2.size(); ++i)
		std::cout << nps2[i].name() << " | " << nps2[i].age() << '\n';

	std::cout << "\nnps1 == nps2: " << (nps1 == nps2)
		<< "\nnps1 != nps2: " << (nps1 != nps2) << '\n';
}
