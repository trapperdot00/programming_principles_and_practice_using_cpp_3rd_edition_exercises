#include <iostream>
#include <functional>

namespace
{
	void log_constructor(const char* type)
	{
		std::cout << type << " constructor\n";
	}

	void log_destructor(const char* type)
	{
		std::cout << type << " destructor\n";
	}

	void log_section_start(const char* name)
	{
		static bool first = true;
		if (!first)
		{
			std::cout << '\n';
		}
		std::cout << "==== Section " << name << " ====\n";
		first = false;
	}

	void log_section_end()
	{
		std::cout << " - - - - - - - - -\n";
	}

	void run_section(const char* name, std::function<void()> func)
	{
		log_section_start(name);
		func();
		log_section_end();
	}
}

class A
{
public:
	A()
	{
		log_constructor("A");
	}
	~A()
	{
		log_destructor("A");
	}
};

class B
{
public:
	B()
	{
		log_constructor("B");
	}
	virtual ~B()
	{
		log_destructor("B");
	}
};

class C : public A
{
public:
	C()
	{
		log_constructor("C");
	}
	~C()
	{
		log_destructor("C");
	}
};

class D : public B
{
public:
	D()
	{
		log_constructor("D");
	}
	~D() override
	{
		log_destructor("D");
	}
};

class E : virtual public B
{
public:
	E()
	{
		log_constructor("E");
	}
	~E() override
	{
		log_destructor("E");
	}
};

class F : virtual public B
{
public:
	F()
	{
		log_constructor("F");
	}
	~F() override
	{
		log_destructor("F");
	}
};

// G's parts: B, E, F
// (since we inherited virtually from B in classes E and F
//  - to solve the diamond problem -
//  in G we only have one B subobject)
class G : public E, public F
{
public:
	G()
	{
		log_constructor("G");
	}
	~G() override
	{
		log_destructor("G");
	}
};

int main()
{
	run_section("1", []{
		A a;
	});

	run_section("2", []{
		B b;
	});

	run_section("3", []{
		C c;
	});

	run_section("4", []{
		D d;
	});

	run_section("5", []{
		A* p = new C;
		delete p; // Doesn't call C's destructor, as it is not virtual
				  // If C were to acquire resources, they wouldn't be freed
	});

	run_section("6", []{
		A* p = new C;
		delete static_cast<C*>(p); // Cheesing it out by casting to dynamic type
	});

	run_section("7", []{
		B* p = new D;
		delete p;
	});

	run_section("8", []{
		E e;
	});

	run_section("9", []{
		G g;
	});

	// We can see that the subobject destructors are called implicitly,
	// and in an order that is reversed compared to the subobject construction order
}
