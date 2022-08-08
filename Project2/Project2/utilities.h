#pragma once
#include <iostream>

template <typename T>
T userInput() {
	T input;
	while (1) {
		//std::cout << std::endl;
		std::cin >> input;
		if (std::cin.fail()) {
			std::cout << "Blad wprowadzania." << std::endl;
			std::cin.clear();														//reset flagi bledu
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');		//czyszczenie bufora maksymalnego rozmiaru bufora lub do znaku nowej linii
		}
		else
			break;
	}
	return input;
}

static void viewHeadline() {
	std::cout << std::right;
	std::cout.width(50);
	std::cout.fill(':');
	std::cout << "\n";
	std::cout.width(29);
	std::cout << "BLACKJACK";
	std::cout.width(21);
	std::cout.fill(':');
	std::cout << "\n";
	std::cout.width(50);
	std::cout.fill(':');
	std::cout << "\n" << std::endl;
	std::cout.fill(' ');
}