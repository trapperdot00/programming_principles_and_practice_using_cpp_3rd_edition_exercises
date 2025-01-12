#include <stdexcept>
#include <iostream>

template <typename T1, typename T2>
constexpr T1 narrow(const T2& t) {
	T1 ret = t;
	if (ret != t)
		throw std::runtime_error("narrow: info loss");
	return ret;
}

template <typename T1, typename T2>
constexpr T1 narrow_convert(const T2& t) {
	T1 ret = narrow<T1>(t);
	return ret;
}

template <typename T1, typename T2>
consteval T1 implicit_convert(const T2& t) {
	T1 ret = t;
	return ret;
}

// int to double
// char to double
// char to int
// double to int
// int to char
// double to char

int main() {
	constexpr double d = 7.7;
	constexpr int i = 1001;
	constexpr char c = 'x';
	std::cout << "narrow int to double: " << narrow_convert<double>(i)
		<< "\nimplicit int to double: " << implicit_convert<double>(i)
		<< "\n\nnarrow char to double: " << narrow_convert<double>(c)
		<< "\nimplicit char to double: " << implicit_convert<double>(c)
		<< "\n\nnarrow char to int: " << narrow_convert<int>(c)
		<< "\nimplicit char to int: " << implicit_convert<int>(c)
//		<< "\n\nnarrow double to int: " << narrow_convert<int>(d)
		<< "\n\nimplicit double to int: " << implicit_convert<int>(d)
//		<< "\n\nnarrow int to char: " << narrow_convert<char>(i)
		<< "\n\nimplicit int to char: " << implicit_convert<char>(i)
//		<< "\n\nnarrow double to char: " << narrow_convert<char>(d)
		<< "\n\nimplicit double to char: " << implicit_convert<char>(d) << '\n';
}
