#ifndef ABSTRACT_PROT_H
#define ABSTRACT_PROT_H

class Abstract_prot {
public:
	int value() const { return val; }
protected:
	// Abstract class: no public constructors
	Abstract_prot(int i)
		: val{i} {}
private:
	int val;
};

#endif
