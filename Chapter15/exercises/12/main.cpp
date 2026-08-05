#include <string>
#include <string_view>
#include <iostream>
#include <cmath>
#include <functional>

struct God
{
	std::string name;
	std::string mythology;
	std::string vehicle;
	std::string weapon;
};

struct Link
{
	Link* add_ordered(Link*);

	God value;
	Link* prev;
	Link* next;
};

void free_list(Link* head)
{
	while (head)
	{
		Link* next = head->next;
		delete head;
		head = next;
	}
}

// Insert n before p
// n must point to a detached Link (not in any list)
Link* insert_detached(Link* p, Link* n)
{
	if (!p) return n;
	if (!n) return p;
	if (p == n) return p;
	n->next = p;
	if (p->prev)
		p->prev->next = n;
	n->prev = p->prev;
	p->prev = n;
	return n;
}

// Insert n after p
// n must point to a detached Link (not in any list)
Link* add_detached(Link* p, Link* n)
{
	if (!p) return n;
	if (!n) return p;
	if (p == n) return p;
	n->prev = p;
	if (p->next)
		p->next->prev = n;
	n->next = p->next;
	p->next = n;
	return n;
}

Link* detach(Link* p)
{
	if (p->prev)
		p->prev->next = p->next;
	if (p->next)
		p->next->prev = p->prev;
	p->prev = nullptr;
	p->next = nullptr;
	return p->next;
}

template <typename Pred>
Link* find_if(Link* p, Pred pred)
{
	for (; p; p = p->next)
	{
		if (pred(p->value))
			return p;
	}
	return nullptr;
}

Link* next(Link* p)
{
	return p->next;
}

Link* prev(Link* p)
{
	return p->prev;
}

Link* advance(Link* p, int n)
{
	if (!p) return nullptr;
	auto adv = (n < 0) ? prev : next;
	int abs_n = std::abs(n);
	for (; abs_n > 0; --abs_n)
	{
		p = adv(p);
		if (!p)
			return nullptr;
	}
	return p;
}

Link* Link::add_ordered(Link* p)
{
	if (!p)
		return this;
	auto pred = [name = std::cref(p->value.name)](const God& g) -> bool {
		return name.get() < g.name;
	};
	Link* node = find_if(this, pred);
	if (node)
	{
		Link* n = insert_detached(node, p);
		if (n->next == this)
		{
			return n;
		}
		return this;
	}
	else
	{
		return insert_detached(this, p);
	}
}

void print_all(Link* p)
{
	bool first = true;
	for (; p; p = p->next)
	{
		const God& value = p->value;
		if (!first)
			std::cout << '\n';
		else
			first = false;
		std::cout << "name: " << value.name << '\n';
		std::cout << "mythology: " << value.mythology << '\n';
		std::cout << "vehicle: " << value.vehicle << '\n';
		std::cout << "weapon: " << value.weapon << '\n';
	}
}

#define PRINT_ALL(X) \
	std::cout << "---- " << #X << " ----\n"; \
	print_all(X); \
	std::cout << "=====================\n"

int main()
{
	Link* greek_gods = new Link{God{"Zeus", "Greek", "",  "lightning"}};
	greek_gods = greek_gods->add_ordered(new Link{God{"Hera", "Greek", "Peacock-drawn chariot",  "Scepter"}});
	greek_gods = greek_gods->add_ordered(new Link{God{"Aphrodite", "Greek", "Deer-drawn chariot",  "Girdle of charm"}});
	greek_gods = greek_gods->add_ordered(new Link{God{"Poseidon", "Greek", "Sea chariot",  "Trident"}});
	greek_gods = greek_gods->add_ordered(new Link{God{"Hades", "Greek", "Black horse-drawn chariot",  "Helm of Darkness"}});

	Link* norse_gods = new Link{God{"Odin", "Norse", "Sleipnir",  "Gungnir"}};
	norse_gods = norse_gods->add_ordered(new Link{God{"Thor", "Norse", "Tanngrisnir and Tanngnjostr",  "Mjolnir"}});
	norse_gods = norse_gods->add_ordered(new Link{God{"Tyr", "Norse", "",  "sword"}});
	norse_gods = norse_gods->add_ordered(new Link{God{"Heimdall", "Norse", "Gulltoppr",  "Gjallarhorn"}});
	norse_gods = norse_gods->add_ordered(new Link{God{"Freyr", "Norse", "Gullinbursti",  "Svaelnir"}});

	Link* roman_gods = new Link{God{"Jupiter", "Roman", "Eagle",  "thunderbolt"}};
	roman_gods = roman_gods->add_ordered(new Link{God{"Juno", "Roman", "Peacock-drawn chariot",  "Scepter"}});
	roman_gods = roman_gods->add_ordered(new Link{God{"Neptune", "Roman", "Sea chariot",  "Trident"}});
	roman_gods = roman_gods->add_ordered(new Link{God{"Mars", "Roman", "Fiery horse-drawn chariot",  "Spear"}});
	roman_gods = roman_gods->add_ordered(new Link{God{"Apollo", "Roman", "Sun chariot",  "Bow and arrows"}});

	PRINT_ALL(greek_gods);
	PRINT_ALL(norse_gods);
	PRINT_ALL(roman_gods);

	free_list(greek_gods);
	free_list(norse_gods);
	free_list(roman_gods);
}
