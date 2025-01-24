#include "Name_pairs.h"

int main() {
	Name_pairs np1{
		{"john", "greg", "jim", "hank", "adam"},
		{24, 45, 19, 33, 55}
	};
	Name_pairs np2{np1};
	Name_pairs np3{
		{"robert", "tim", "bob", "steve", "fred"},
		{24, 45, 19, 33, 55}
	};

	std::cout << "np1:\n" << np1
		<< "\nnp2:\n" << np2
		<< "\nnp3:\n" << np3
		<< std::boolalpha
		<< "\nnp1 == np2: " << (np1 == np2)
		<< "\nnp1 != np2: " << (np1 != np2)
		<< "\nnp1 == np3: " << (np1 == np3)
		<< "\nnp1 != np3: " << (np1 != np3)
		<< "\nnp2 == np3: " << (np2 == np3)
		<< "\nnp2 != np3: " << (np2 != np3)
		<< '\n';
}
