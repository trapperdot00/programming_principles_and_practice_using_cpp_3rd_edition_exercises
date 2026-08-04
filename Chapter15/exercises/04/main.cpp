#include <string_view>
#include <cstdint>
#include <iostream>
#include <map>

std::ostream& print_ordering()
{
	int* p = new int;

	static int static_i;
	int stack_i;
	int& free_store_i = *p;

	auto static_addr = reinterpret_cast<uintptr_t>(&static_i);
	auto stack_addr  = reinterpret_cast<uintptr_t>(&stack_i);
	auto free_store_addr   = reinterpret_cast<uintptr_t>(&free_store_i);

	// Sorts the elements based on the key automatically
	std::map<uintptr_t, std::string_view> storage = {
		{ static_addr, "static"     },
		{ stack_addr , "stack"      },
		{ free_store_addr  , "free store" },
	};
	std::cout << "Storage ordering (lowest-to-highest address):\n";
	for (const auto& p : storage)
	{
		std::cout << "[" << p.second << "]\n";
	}

	delete p;
	return std::cout;
}

std::ostream& print_stack_growth_helper(int& a)
{
	int b;
	auto a_addr = reinterpret_cast<uintptr_t>(&a);
	auto b_addr = reinterpret_cast<uintptr_t>(&b);
	std::cout << "The stack grows ";
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
	return std::cout << ".\n";
}

std::ostream& print_stack_growth()
{
	int a;
	return print_stack_growth_helper(a);
}

std::ostream& print_free_store_array_address_ordering()
{
	constexpr int size = 10;
	int* arr = new int[size];

	int* first = arr;
	int* last = arr + (size - 1);

	auto first_addr = reinterpret_cast<uintptr_t>(first);
	auto last_addr  = reinterpret_cast<uintptr_t>(last);

	std::cout << "In free store arrays, elements with higher indices are allocated at ";
	if (first_addr < last_addr)
	{
		std::cout << "higher addresses";
	}
	else if (last_addr < first_addr)
	{
		std::cout << "lower addresses";
	}
	else
	{
		std::cout << "the same addresses (?)";
	}

	delete[] arr;
	return std::cout << ".\n";
}

int main()
{
	print_ordering() << '\n';
	print_stack_growth() << '\n';
	print_free_store_array_address_ordering();
}
