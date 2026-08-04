#include <cstring>

namespace
{
	// Double free
	void disaster1()
	{
		int* p = new int;
		delete p;
		delete p;
	}

	// Memory leaking
	void disaster2()
	{
		int* p = new int;
	}

	// Out-of-bounds memory access (stack-buffer overflow)
	void disaster3()
	{
		int arr[5];
		int* outofbounds = arr + 5;
		*outofbounds = 100;
	}

	// Uninitialized pointer dereferencing
	void disaster4()
	{
		int* p;
		*p = 100;
	}

	// Null pointer dereferencing
	void disaster5()
	{
		int* p = nullptr;
		*p = 5;
	}

	// Mismatched delete operator
	void disaster6()
	{
		int* p = new int;
		delete[] p;
	}

	// Mismatched delete operator
	void disaster7()
	{
		int* p = new int[5];
		delete p;
	}

	// Casting a pointer to another one with a different pointed-to type
	// and using it (possible stack-buffer overflow)
	void disaster8()
	{
		int i;
		int* pi = &i;
		double* pd = reinterpret_cast<double*>(pi);
		*pd = 3.1415;
	}

	// Working with a C-String without null-terminator (stack-buffer overflow)
	// (GCC actually warns about this, wow)
	void disaster9()
	{
		const char cp[] = {'e', 'v', 'i', 'l'}; // no null terminator
		auto size = std::strlen(cp);
	}
}

int main()
{
	// Pick your poison
	disaster9();
}
