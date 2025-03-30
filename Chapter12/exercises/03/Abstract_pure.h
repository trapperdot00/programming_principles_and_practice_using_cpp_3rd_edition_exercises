#ifndef ABSTRACT_PURE_H
#define ABSTRACT_PURE_H

class Abstract_pure {
public:
	Abstract_pure(int i)
		: val{i}
	{}
	int value() const { return val; }
	
	// Abstract class: has pure virtual function
	virtual void func() const = 0;
private:
	int val;
};

#endif
