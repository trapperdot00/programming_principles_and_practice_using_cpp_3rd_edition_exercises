/*	Rework of Chapter04/exercises/10
 *
 *	Program that asks for a size,
 *	then reads floating-point numbers,
 *	then prints the sum of all numbers and the
 *	difference of numbers next to each other
 */

#include <stdexcept>
#include <iostream>
#include <vector>
#include <limits>
#include <utility>
#include <numeric>

// Read and return one read value from cin
// Error on invalid input
template <typename T>
T read() {
	T t;
	if (!(std::cin >> t))
		throw std::runtime_error("invalid input");
	return t;
}

// Read multiple values of a given type into a vector from cin
// Error on empty sequence
template <typename T>
std::vector<T> read_sequence() {
	std::vector<T> t;
	for (T temp; std::cin >> temp; )
		t.push_back(std::move(temp));
	if (t.empty())
		throw std::runtime_error("empty sequence");
	return t;
}

// Print a vector's elements up until a given size
// Error if size is greater than the vector's size
template <typename T>
void print_elements(const std::vector<T>& vec, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		if (i >= vec.size())
			throw std::runtime_error("out of vector range");
		std::cout << vec[i] << ' ';
	}
}

// Print sum of elements in a vector with some printed context
template <typename T>
void print_sum(const std::vector<T>& vec, size_t n) {
	std::cout << "The sum of the first " << n << " numbers ( ";
	print_elements(vec, n);
	std::cout << ") is: " <<
		std::accumulate(vec.cbegin(), vec.cbegin() + n, 0.0) << '\n';
}

// Calculate differences of elements in a vector up until the size n
// Error on underflow
template <typename T> 
std::vector<T> differences(const std::vector<T>& vec, std::size_t n) {
	std::vector<T> ret;
	for (size_t i = 1; i < n; ++i) {
		if (vec[i-1] < std::numeric_limits<T>::lowest() + vec[i])
			throw std::runtime_error("differences: underflow");
		ret.push_back(vec[i-1] - vec[i]);
	}
	return ret;
}

// Print all elements of a vector
template <typename T>
void print_vector(const std::vector<T>& vec) {
	for (const T& t : vec)
		std::cout << t << ' ';
}

// Print differences of elements in a vector with some printed context
template <typename T>
void print_differences(const std::vector<T>& vec) {
	std::cout << "Differences: ";
	print_vector(vec);
	std::cout << '\n';
}

// Main sequence of actions
void program()
try {
	std::cout << "Please enter the number of values you want to sum: ";
	size_t size = read<size_t>();
	if (size == 0)
		throw std::runtime_error("size cannot be 0");
	std::cout << "Please enter some floating-point numbers (press '|' to stop): ";
	std::vector<double> numbers = read_sequence<double>();
	if (size > numbers.size())
		throw std::runtime_error("size cannot be greater than the size of the sequence");
	print_sum(numbers, size);
	if (size > 1)
		print_differences(differences(numbers, size));
} catch (std::exception& e) {
	std::cerr << "error: " << e.what() << '\n';
}

int main()
try {
	program();
} catch (std::exception& e) {
	std::cerr << "error: " << e.what() << '\n';
}
