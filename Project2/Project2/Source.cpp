#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#include <algorithm>
#include "Casino.h"
#include "Player.h"
#include "Karta.h"
#include "utilities.h"

int main()
{
	setlocale(LC_ALL, "");
	srand(time(NULL));
	char ch = '0';
	int declaredPlayers = 0;
	while (1) {

		viewHeadline();
		std::cout << "1) Rozpocznij nowa gre" << std::endl;
		std::cout << "2) Wyjdz z programu" << std::endl;
		std::cout << "Twoj wybor: ";
		
		switch (userInput<char>()) {
		case '1': {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			system("cls");
			viewHeadline();

			Casino casino1;

			//dodawanie graczy do kasyna
			int num;
			num = 0;
			do {
				std::cout << "Ilu ludzkich graczy dodac do stolu? (1-3): ";
				num = userInput<int>();
			} while (num < 0 || num > 3);

			std::string tempname;
			for (int i = 0; i < num; i++) {
				std::cout << "Podaj nazwe " << i + 1 << " gracza:" << std::endl;
				tempname = userInput<std::string>();
				while (tempname.size() > 20) {
					std::cout << "Wprowadzono powyzej 20 znakow w nazwie gracza, sproboj ponownie." << std::endl;
					tempname = userInput<std::string>();
				}

				casino1.addPlayer(tempname, i);
			}

			//dodawanie botów do kasyna
			num = 0;
			do {
				std::cout << "Ilu komputerowych graczy dodac do stolu? (1-3): ";
				num = userInput<int>();
			} while (num < 0 || num > 3);
			declaredPlayers += num;

			int ch;
			for (int i = 0; i < num; i++) {
				do {
					system("cls");
					viewHeadline();
					std::cout << "Wybierz odwage bota " << i + 1 << ":" << std::endl;
					std::cout << "1) Zachowawczy" << std::endl;
					std::cout << "2) Normalny" << std::endl;
					std::cout << "3) Ryzykant" << std::endl;
					ch = userInput<int>();
				} while (ch < 0 || ch > 3);
				
				casino1.addBot(i, ch);
			}

			//rozdanie graczom po 2 karty i pokazanie ich
			system("cls");
			viewHeadline();
			casino1.play(&casino1);

			break;
		}

		case '2':
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return 0;
		default:
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Nie rozpoznano akcji.\nSproboj ponownie." << std::endl;
		}
		system("cls");
	}

	return 0;
}