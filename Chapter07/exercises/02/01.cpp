#include <vector>
#include <string>
#include <iostream>

void print(const std::string& s, const std::vector<int>& vec) {
	std::cout << s;
	for (int i : vec)
		std::cout << ' ' << i;
	std::cout << '\n';
}

int main() {
	std::vector<int> numbers = {0,1,2,3,4,5,6,7,8,9};
	std::string label = "These are our numbers:";
	print(label, numbers);
}
