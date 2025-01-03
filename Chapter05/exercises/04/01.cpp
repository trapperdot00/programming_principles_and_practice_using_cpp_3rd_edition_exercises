#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include <algorithm>

class not_found{};
class read_error{};

class Name_value {
	friend bool operator<(const Name_value&, const Name_value&);
public:
	Name_value(const std::string& s, int i)
		: n(s), v(i)
	{}

	std::string name() const { return n; }
	int value() const { return v; }

private:
	std::string n;
	int v;
};
bool operator<(const Name_value& lhs, const Name_value& rhs) {
	return lhs.n < rhs.n;
}

// Requires sorted vector!
bool is_unique(const std::vector<Name_value>& vec) {
	for (size_t i = 1; i < vec.size(); ++i) {
		if (vec[i-1].name() == vec[i].name())
			return false;
	}
	return true;
}

std::vector<size_t> search_for(const std::vector<Name_value>& vec, int val) {
	std::vector<size_t> v;
	for (size_t i = 0; i < vec.size(); ++i)
		if (vec[i].value() == val)
			v.push_back(i);
	if (v.empty())
		throw not_found{};
	return v;
}

int main()
try {
	std::vector<Name_value> scores;

	std::cout << "Enter name-value pairs:\n";
	std::string name;
	int value;
	while (std::cin >> name >> value && (name != "NoName" || value != 0)) {
		scores.push_back({name, value});
	}
	if (!std::cin || scores.empty())
		throw read_error{};
	std::sort(scores.begin(), scores.end());
	if (!is_unique(scores))
		throw std::runtime_error("repetition in names!");

	std::cout << "\nEnter value to search for:\n";
	for (int val; std::cin >> val; ) try {
		std::vector<size_t> indexes = search_for(scores, val);
		for (size_t pos : indexes) {
			const Name_value& ref = scores[pos];
			std::cout << ref.name() << '\t' << ref.value() << '\n';
		}	
	} catch (not_found& e) {
		std::cerr << "Not found!\n";
	}

} catch (std::exception& e) {
	std::cerr << "error: " << e.what() << '\n';
} catch (read_error& e) {
	std::cerr << "No data!\n";
}
