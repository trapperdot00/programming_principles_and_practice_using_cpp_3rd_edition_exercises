#include <vector>
#include <iostream>
#include <random>
#include <chrono>

std::vector<int> build_seq() {
	static std::default_random_engine e(std::chrono::steady_clock::now().time_since_epoch().count());
	static std::uniform_int_distribution<int> d(0, 2);
	constexpr int size = 255;
	std::vector<int> ret;
	for (int i = 0; i < size; ++i) {
		ret.push_back(d(e));
	}
	return ret;
}

int main()
{
	// move symbolic constants
	constexpr int rock = 0;
	constexpr int paper = 1;
	constexpr int scissors = 2;

	// status symbolic constants
	constexpr int win = 1;
	constexpr int loss = -1;
	constexpr int in_progress = 0;

	std::vector<int> move_sequence = build_seq();

	int status = 0;
	std::cout << "Rock, Paper, Scissors.\n";
	for (int current_move = 0; status == in_progress; ++current_move) {
		std::cout << "\nEnter move (Rock: 0; Paper: 1; Scissors: 2): ";
		int move = 0;
		while (std::cin >> move && (move < 0 || move > 2))
			std::cout << "Invalid number, try again: ";

		int ai_move	= move_sequence[current_move];
		switch (move) {
		case rock:
			switch (ai_move) {
			case rock:
				std::cout << "Rock meets rock. Nothing happens.\n";
				break;
			case paper:
				std::cout << "Paper wraps rock up. You lose!\n";
				status = loss;
				break;
			case scissors:
				std::cout << "Rock smashes scissors. You win!\n";
				status = win;
				break;
			}
			break;
		case paper:
			switch (ai_move) {
			case rock:
				std::cout << "Paper wraps up rock. You win!\n";
				status = win;
				break;
			case paper:
				std::cout << "Paper meets paper. Nothing happens.\n";
				break;
			case scissors:
				std::cout << "Scissors cut through paper. You lose!\n";
				status = loss;
				break;
			}
			break;
		case scissors:
			switch (ai_move) {
			case rock:
				std::cout << "Rock smashes scissors. You lose!\n";
				status = loss;
				break;
			case paper:
				std::cout << "Scissors cut through paper. You win!\n";
				status = win;
				break;
			case scissors:
				std::cout << "Scissors meet scissors. Nothing happens.\n";
				break;
			}
			break;
		}
	}
}
