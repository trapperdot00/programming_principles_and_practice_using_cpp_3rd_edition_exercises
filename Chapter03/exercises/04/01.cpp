#include <vector>
#include <iostream>

double sum(const std::vector<double> &vec) {
	double ret = 0.0;
	for (double d : vec)
		ret += d;
	return ret;
}

double mean(const std::vector<double> &vec) {
	return sum(vec) / vec.size();
}

double min(const std::vector<double> &vec) {
	double smallest = 0.0;
	for (std::vector<double>::size_type i = 0; i<vec.size(); ++i)
		if (i==0 || vec[i]<smallest)
			smallest = vec[i];
	return smallest;
}

double max(const std::vector<double> &vec) {
	double largest = 0.0;
	for (std::vector<double>::size_type i = 0; i<vec.size(); ++i)
		if (i==0 || vec[i]>largest)
			largest = vec[i];
	return largest;
}

int main()
{
	std::vector<double> distances;
	for (double d; std::cin >> d; )
		distances.push_back(d);

	std::cout << "Total distance: " << sum(distances)
		<< "\nSmallest distance: " << min(distances)
		<< "\nLargest distance: " << max(distances)
		<< "\nMean distance: " << mean(distances)
		<< '\n';
}
