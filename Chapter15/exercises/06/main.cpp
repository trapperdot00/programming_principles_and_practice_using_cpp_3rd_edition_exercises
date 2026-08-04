#include <iostream>
#include <cstddef>
#include <utility>

class my_array
{
public:
	my_array() = default;

	my_array(const my_array& other) :
		data{new char[other.size]},
		size{other.size},
		capacity{size}
	{
		for (std::size_t i = 0; i < size; ++i)
		{
			data[i] = other.data[i];
		}
	}

	my_array(my_array&& other) noexcept :
		data{other.data},
		size{other.size},
		capacity{other.capacity}
	{
		other.data = nullptr;
		other.size = 0;
		other.capacity = 0;
	}

	friend void swap(my_array& lhs, my_array& rhs)
	{
		using std::swap;
		swap(lhs.data, rhs.data);
		swap(lhs.size, rhs.size);
		swap(lhs.capacity, rhs.capacity);
	}

	my_array& operator=(my_array other)
	{
		swap(*this, other);
		return *this;
	}

	~my_array()
	{
		delete[] data;
	}

	void append(char c)
	{
		if (size == capacity)
		{
			reallocate();
		}
		data[size] = c;
		++size;
	}

	char& operator[](std::size_t n) { return data[n]; }
	const char& operator[](std::size_t n) const { return data[n]; }
	char* begin() { return data; }
	const char* begin() const { return data; }
	char* end() { return data + size; }
	const char* end() const { return data + size; }
private:
	void reallocate()
	{
		std::size_t new_capacity = (capacity == 0) ? 1 : 2 * capacity;
		char* new_data = new char[new_capacity];
		for (std::size_t i = 0; i < size; ++i)
		{
			new_data[i] = data[i];
		}
		delete[] data;
		data = new_data;
		capacity = new_capacity;
	}
private:
	char* data           = nullptr;
	std::size_t size     = 0;
	std::size_t capacity = 0;
};

int main()
{
	my_array arr;

	std::cout << "Enter characters, exit using '!'\n";
	for (char c; std::cin.get(c) && c != '!'; arr.append(c)) ;

	std::cout << "Read characters:\n";
	for (char c : arr)
	{
		std::cout << c;
	}
}
