#include <string>
#include <vector>
#include <iostream>
#include <format>

// One row of fields
struct Entry {
	std::vector<std::string> fields;
};

// Widths for each field in an Entry
struct WidthData {
	std::vector<size_t> widths;
};

// Get maximum widths for the corresponding columns
WidthData get_widths(const std::vector<Entry>& vec) {
	WidthData ret;

	// Initially put the labels' widths as elements into ret
	if (!vec.empty())
		for (size_t i = 0; i < vec[0].fields.size(); ++i)
			ret.widths.push_back(vec[0].fields[i].size());
	
	// Iterate through data
	for (size_t i = 1; i < vec.size(); ++i) {
		// Widths and fields don't have the same sizes
		if (ret.widths.size() != vec[i].fields.size())
			throw std::runtime_error{"table format error"};

		// Update corresponding widths if current width is larger
		for (size_t j = 0; j < ret.widths.size(); ++j) {
			if (ret.widths[j] < vec[i].fields[j].size())
				ret.widths[j] = vec[i].fields[j].size();
		}
	}
	return ret;
}

// Print a vector of entries with a width of the maximum width datas for each field,
// add an amount to width
void print(const std::vector<Entry>& tbl, const WidthData& w, size_t n = 1) {
	for (const Entry& e : tbl) {
		for (size_t i = 0; i < w.widths.size(); ++i) {
			std::cout << std::format("{1:{0}}", w.widths[i] + n, e.fields[i]);
		}
		std::cout << '\n';
	}
}

int main() {
	// First element is the label
	const std::vector<Entry> table = {
		{{"Last name", "First name", "Phone number", "Email address"}},
		{{"Smith", "John", "+1234567890", "user1@mail.com"}},
		{{"Another", "John", "+123 (555) 0100", "whatisthismeanttobe@gmail.com"}},
		{{"Thousander", "Millionaire", "110001001", "okay@ok.com"}},
		{{"Avery Longname", "Thesis Exhausting", "+1231231231231231231234", "a@a.a"}},
		{{"A", "B", "C", "D"}},
		{{"Alphabetical", "Samurai", "+42-123-6266", "dontmail@nomail.com"}},
		{{"Mathematically", "Automatically", "+52 135 2764", "short@mail.com"}},
		{{"Gamer", "Gamer", "123", "gamer@gmail.com"}}
	};

	// Get maximum width for each column in table
	const WidthData widths = get_widths(table);

	// To make space between the neighboring fields,
	// widths are increased by this amount
	// If excess is 0 the longest string in the fields will reach the next column
	constexpr size_t excess = 2;
	
	print(table, widths, excess);
}
