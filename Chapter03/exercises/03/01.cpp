#include <iostream>
#include <vector>
#include <algorithm>

// 0 1 2 3   4
// Median from sorted vector
double median(const std::vector<double> &vec) {
	if (vec.size() % 2)
		return vec[vec.size()/2];
	else
		return (vec[vec.size()/2] + vec[vec.size()/2-1]) / 2;
}

int main()
{
	std::vector<double> temps;

	for (double temp; std::cin >> temp; )
		temps.push_back(temp);

	double sum = 0.0;
	for (double x : temps)
		sum += x;
	std::cout << "Average temperature: " << sum/temps.size() << '\n';

	std::ranges::sort(temps);
	if (!temps.empty())
		std::cout << "Median temperature: " << median(temps) << '\n';
	else
		std::cout << "No median: no data!\n";
}
