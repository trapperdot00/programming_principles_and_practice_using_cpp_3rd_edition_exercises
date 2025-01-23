#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

struct my_result {
	double min;
	double max;
	double mean;
	double median;
};

// Calculate minimum, maximum, mean and median value from a vector
// Vector cannot be empty
// Uses standard library facilities, which might make it less readable
// Directly initializes returned struct of my_result in the return expression
auto calculate(std::vector<double> vec) -> my_result {
	if (vec.empty())
		throw std::runtime_error{"empty vector"};
	std::sort(vec.begin(), vec.end());
	return {vec.front(), vec.back(),
		std::accumulate(vec.cbegin(), vec.cend(), 0.0) / vec.size(),	// Mean
		vec.size() % 2 == 0 ? (vec[vec.size()/2-1]+vec[vec.size()/2])/2 : vec[vec.size()/2]};	// Median
}

// Reads doubles until std::cin fails
// Returns the read doubles in a vector
std::vector<double> read() {
	std::vector<double> vec;
	for (double temp; std::cin >> temp; )
		vec.push_back(temp);
	return vec;
}

int main() {
	std::cout << "Enter numbers: ";
	std::vector<double> numbers = read();
	my_result res = calculate(numbers);

	std::cout << "Numbers:\t";
	for (double d : numbers)
		std::cout << d << ' ';
	std::cout << "\nMinimum:\t" << res.min
		<< "\nMaximum:\t" << res.max
		<< "\nMean:\t\t" << res.mean
		<< "\nMedian:\t\t" << res.median
		<< '\n';
}
