#include <iostream>

// Holds integers as its template arguments that can be
// extracted and unpacked in functions
template <int... Numbers>
struct Sequence
{};

// Constructs a Sequence<> containing Count amount of integers,
// starting from Number, with each number being the double of the previous one
template <int Number, int Count, typename Seq>
struct MakeSequenceImpl;

// Base case: Count == 0
// -> Returns the constructed Sequence<> containing numbers
template <int Number, int... Numbers>
struct MakeSequenceImpl<Number, 0, Sequence<Numbers...>> :
	Sequence<Numbers...>
{};

// Recursive case: Count != 0
// -> Appends the current Number into Sequence,
//    starts the next iteration with the parameters:
//    Number = Number * 2; Count = Count - 1, Numbers = { Numbers, Number }
template <int Number, int Count, int... Numbers>
struct MakeSequenceImpl<Number, Count, Sequence<Numbers...>> :
	MakeSequenceImpl<Number * 2, Count - 1, Sequence<Numbers..., Number>>
{};

// Helper that supplies the empty sequence into MakeSequence
template <int Start, int Count>
struct MakeSequence : MakeSequenceImpl<Start, Count, Sequence<>>
{};

// Creates a new heap-allocated array of ints initialized by the
// values of the given Sequence<>
template <int... Numbers>
int* make_array(Sequence<Numbers...>)
{
	return new int[sizeof...(Numbers)]{Numbers...};
}

int main()
{
	int* p1 = new int{7};
	std::cout << "p1: " << p1 << "; *p1: " << *p1 << '\n';

	constexpr int p2_size = 7;
	int* p2 = make_array(MakeSequence<1, p2_size>{});
	std::cout << "p2: " << p2 << "; *p2: {";
	for (int i = 0; i < p2_size; ++i)
	{
		if (i)
		{
			std::cout << ", ";
		}
		std::cout << p2[i];
	};
	std::cout << "}\n";

	int* p3 = p2;
	p2 = p1;
	p2 = p3;

	std::cout << "p1: " << p1 << "; *p1: " << *p1 << '\n';
	std::cout << "p2: " << p2 << "; *p2: {";
	for (int i = 0; i < p2_size; ++i)
	{
		if (i)
		{
			std::cout << ", ";
		}
		std::cout << p2[i];
	};
	std::cout << "}\n";

	delete p1;
	delete[] p2;

	p1 = make_array(MakeSequence<1, 10>{});
	p2 = new int[10];

	for (int i = 0; i < 10; ++i)
	{
		p2[i] = p1[i];
	}

	delete[] p1;
	delete[] p2;
}
