#include <string>

struct Link
{
	Link(const std::string& v, Link* s = nullptr) :
		value{v}, succ{s}
	{}
	std::string value;
	Link* succ;
};

Link* insert(Link* p, Link* n)
{
	if (n == nullptr)
		return p;
	if (p == nullptr)
		return n;
	n->succ = p;
	return n;
}

int main()
{
	Link* norse_gods = new Link{"Thor"};
	norse_gods = insert(norse_gods, new Link{"Odin"});
	norse_gods = insert(norse_gods, new Link{"Freja"});

	while (norse_gods)
	{
		Link* next = norse_gods->succ;
		delete norse_gods;
		norse_gods = next;
	}
	norse_gods = nullptr;
}
