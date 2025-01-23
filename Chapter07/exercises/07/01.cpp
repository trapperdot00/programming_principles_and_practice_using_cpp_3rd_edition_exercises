#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <algorithm>

template <typename T>
auto read_n(size_t n) -> std::vector<T> {
	std::vector<T> ret;
	T temp = T();
	size_t i = 0;
	while (i < n && std::cin >> temp) {
		ret.push_back(std::move(temp));
		++i;
	}
	return ret;
}

template <typename T1, typename T2>
void print_pairs(const std::vector<T1>& vec1, const std::vector<T2>& vec2) {
	size_t n = std::min(vec1.size(), vec2.size());
	for (size_t i = 0; i < n; ++i) {
		std::cout << vec1[i] << '\t' << vec2[i] << '\n';
	}
}

// Sort two vectors based on the ordering of the first one
void sort_pairs(std::vector<std::string>& vec1, std::vector<double>& vec2) {
	std::vector<std::string> original = vec1;
	std::sort(vec1.begin(), vec1.end());	// Sort vec1
	const std::size_t n = std::min(vec1.size(), vec2.size());
	std::vector<double> second;
	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < n; ++j) {
			if (original[j] == vec1[i]) {
				second.push_back(vec2[j]);
			}
		}
	}
	vec2 = second;	// Sort vec2
}

int main() {
	constexpr size_t count = 5;
	
	std::vector<std::string> name;
	std::vector<double> age;
	name.reserve(count);
	age.reserve(count);

	std::cout << "Enter " << count << " names: ";
   	name = read_n<std::string>(count);

	std::cout << "Enter " << count << " ages: ";
	age = read_n<double>(count);

	std::cout << "Original pairs:\n";
	print_pairs(name, age);

	sort_pairs(name, age);
	std::cout << "\nSorted pairs:\n";
	print_pairs(name, age);
}
