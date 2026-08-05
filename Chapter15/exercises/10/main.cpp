#include <string>
#include <iostream>

struct Link
{
	Link(std::string_view val, Link* prv = nullptr, Link* nxt = nullptr) :
		value{val},
		prev{prv},
		next{nxt}
	{}

	std::string value;
	Link* prev;
	Link* next;
};

inline void detach_from_list_impl(Link* link)
{
	if (link->prev)
		link->prev->next = link->next;
	if (link->next)
		link->next->prev = link->prev;
}

inline Link* insert_impl(Link* p, Link* n)
{
	n->next = p;
	if (p->prev)
		p->prev->next = n;
	n->prev = p->prev;
	p->prev = n;
	return n;
}

void detach_from_list(Link* link)
{
	if (!link) return;
	detach_from_list_impl(link);
	link->prev = nullptr;
	link->next = nullptr;
}

// insert n before p
Link* insert(Link* p, Link* n)
{
	if (!p) return n;
	if (!n) return p;
	return insert_impl(p, n);
}

// insert n before p,
// detaching n from its list before doing so
Link* insert_from_list(Link* p, Link* n)
{
	if (!p) return n;
	if (!n) return p;
	if (p == n) return p;
	detach_from_list_impl(n);
	return insert_impl(p, n);
}

std::ostream& print_list(std::ostream& os, Link* head)
{
	os << '{';
	for (Link* p = head; p; p = p->next)
	{
		if (p != head)
			os << ", ";
		os << p->value;
	}
	os << '}';
	return os;
}

std::ostream& print_list_reverse(std::ostream& os, Link* tail)
{
	os << '{';
	for (Link* p = tail; p; p = p->prev)
	{
		if (p != tail)
			os << ", ";
		os << p->value;
	}
	os << '}';
	return os;
}

Link* find_tail(Link* p)
{
	Link* prev = nullptr;
	for (Link* curr = p; curr; curr = curr->next)
	{
		prev = curr;
	}
	return prev;
}

int main()
{
	Link* norse_gods = new Link{"Thor"};
	norse_gods = insert(norse_gods, new Link{"Odin"});
	norse_gods = insert(norse_gods, new Link{"Freja"});

	print_list(std::cout, norse_gods) << '\n';
	print_list_reverse(std::cout, find_tail(norse_gods)) << '\n';
}
