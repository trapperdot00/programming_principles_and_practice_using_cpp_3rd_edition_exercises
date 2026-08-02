#include <iostream>

std::ostream& print_array(std::ostream& os, int* a, int n)
{
	os << '{';
	for (int i = 0; i < n; ++i)
	{
		if (i)
		{
			os << ", ";
		}
		os << a[i];
	}
	return os << '}';
}

// Holds numbers in its template arguments to be unpacked in functions
template <int... Numbers>
struct Sequence
{
	using type = Sequence<Numbers...>;
};

// Iterates over numbers and puts it into Sequence's template arguments
template <int Number, int Count, typename Seq>
struct MakeSequenceImpl;

// Base case: Count == 0
// -> no more numbers to add, return the number-filled Sequence
template <int Number, int... Numbers>
struct MakeSequenceImpl<Number, 0, Sequence<Numbers...>> :
	Sequence<Numbers...>
{};

// Recursive case: Count != 0
// -> put the current number into Sequence
//    and recurse with Number = Number + 1; Count = Count - 1
template <int Number, int Count, int... Numbers>
struct MakeSequenceImpl<Number, Count, Sequence<Numbers...>> :
	MakeSequenceImpl<Number + 1, Count - 1, Sequence<Numbers..., Number>>
{};

// Helper for MakeSequenceImpl, that supplies an empty starting Sequence
template <int Start, int Count>
struct MakeSequence : MakeSequenceImpl<Start, Count, Sequence<>>
{};

// Extracts the held numbers of Sequence, and creates a new
// heap-allocated array from its values
// `sizeof...(Is)` returns how many numbers are in Sequence
// `Is...` unpacks the number-pack `Is` to use as initializer-values for the array
template <int... Is>
int* make_array(Sequence<Is...>)
{
	return new int[sizeof...(Is)]{Is...};
}

int main()
{
	constexpr int start = 100;
	constexpr int size = 10;
	int* ia = make_array(MakeSequence<start, size>{});
	print_array(std::cout, ia, size) << '\n';
	delete[] ia;
}
