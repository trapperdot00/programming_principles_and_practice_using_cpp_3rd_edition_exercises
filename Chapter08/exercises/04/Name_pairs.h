#ifndef NAME_PAIRS_H
#define NAME_PAIRS_H

#include "Name_pair.h"

#include <vector>
#include <algorithm>
#include <stdexcept>

// Class that holds name-age pairs
class Name_pairs {
public:
	using element_type = Name_pair;
	using container_type = std::vector<element_type>;
	using size_type = container_type::size_type;

	Name_pairs() {}
	Name_pairs(const container_type& v)
		: np(v) {}
	Name_pairs(container_type&& v)
		: np(std::move(v)) {}

	void read();
	void sort();

	container_type get() const { return np; }
	size_type size() const { return np.size(); }

	element_type& operator[](size_t n) { return np[n]; }
	const element_type& operator[](size_t n) const { return np[n]; }
private:
	
	container_type np;
};

template <typename T>
auto only_unique_elements(std::vector<T>) -> bool;

std::ostream& operator<<(std::ostream&, const Name_pairs&);
bool operator==(const Name_pairs&, const Name_pairs&);
bool operator!=(const Name_pairs&, const Name_pairs&);

#endif
