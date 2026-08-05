#include <iostream>
#include <cstdint>

void print_growth_direction(std::string_view storage, int& a, int& b)
{
	auto a_addr = reinterpret_cast<uintptr_t>(&a);
	auto b_addr = reinterpret_cast<uintptr_t>(&b);

	std::cout << "The " << storage << " grows ";
	if (a_addr < b_addr)
	{
		std::cout << "upward";
	}
	else if (b_addr < a_addr)
	{
		std::cout << "downward";
	}
	else
	{
		std::cout << "nowhere (?)";
	}
	std::cout << ".\n";
}

void print_stack_growth_direction_helper(int& a)
{
	int b;
	print_growth_direction("stack", a, b);
}

void print_stack_growth_direction()
{
	int a;
	print_stack_growth_direction_helper(a);
}

void print_free_store_growth_direction()
{
	int* a = new int;
	int* b = new int;

	print_growth_direction("free store", *a, *b);

	delete b;
	delete a;
}

int main()
{
	print_stack_growth_direction();
	print_free_store_growth_direction();
}
