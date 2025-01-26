#include "Patron.h"

size_t Patron::current_card_no = 0;

std::ostream& operator<<(std::ostream& os, const Patron& p) {
	return os << p.name() << '\n'
		<< p.cardno() << '\n'
		<< p.fees();
}
