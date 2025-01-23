#include <vector>
#include <iostream>
#include <stdexcept>

double calculate(const std::vector<double>& vec1, const std::vector<double>& vec2) {
	if (vec1.size() != vec2.size())
		throw std::runtime_error{"the two vectors have differing sizes"};
	double ret = 0.0;
	for (size_t i = 0; i < vec1.size(); ++i)
		ret += vec1[i]*vec2[i];
	return ret;
}

int main() {
	std::vector<double> price = {10,20,30,40,50,60,70,80,90,100};
	std::vector<double> weight = {2,3,5,1,2,9,10,5,4,3};
	std::cout << calculate(price, weight) << '\n';
}
