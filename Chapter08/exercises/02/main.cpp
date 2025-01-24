#include "Name_pairs.h"

int main() {
	Name_pairs np;
	np.read_names();
	np.read_ages();
	
	std::cout << "\nNames and ages:\n";
	np.print();

	np.sort();
	std::cout << "\nSorted names and ages:\n";
	np.print();
}
