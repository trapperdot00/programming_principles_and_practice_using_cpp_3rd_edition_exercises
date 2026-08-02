#include <vector>
#include <iostream>

std::ostream& print_vector(std::ostream& os, const std::vector<int>& vec)
{
	os << '{';
	for (std::vector<int>::size_type i = 0; i < vec.size(); ++i)
	{
		if (i)
		{
			os << ", ";
		}
		os << vec[i];
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

// Extracts the held numbers of Sequence, and returns a vector<int> from its values
// `Is...` unpacks the number-pack `Is` to use as initializer-values for the vector
template <int... Is>
std::vector<int> make_vector(Sequence<Is...>)
{
	return std::vector<int>{Is...};
}

int main()
{
	constexpr int start = 100;

	auto a = make_vector(MakeSequence<start, 10>{});
	auto b = make_vector(MakeSequence<start, 11>{});
	auto c = make_vector(MakeSequence<start, 20>{});

	print_vector(std::cout, a) << '\n';
	print_vector(std::cout, b) << '\n';
	print_vector(std::cout, c) << '\n';
}
