#include "Casino.h"
#include "Karta.h"
#include "Player.h"
//#include <codecvt>

Casino::Casino(){
	setDeck();
	shuffleDeck();
}

void Casino::setDeck() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			deck[j + (i * 13)].setKolor(i);
			deck[j + (i * 13)].setWartosc(j);
		}
	}
}

void Casino::shuffleDeck() {
	for (int i = 0; i < 100; i++) {
		std::swap(deck[rand() % 52], deck[rand() % 52]);
	}
}

Karta* Casino::getCard() {
	if(currCard < 52) {
		currCard++;
		return &deck[currCard - 1];
	}
	else {
		std::cout << "Koniec talii kart.";
		return 0;
	}
}

void Casino::addPlayer(const std::string &_name, int userId) {
	playerCount++;
	user[userId].setName(_name);
}

void Casino::addBot(int botId, int bhvr) {
	botCount++;
	botUser[botId].setName("BOT" + std::to_string(1 + botId));
	botUser[botId].changeBhvr(bhvr);
}

bool Casino::anyHits() {
	for (int i = 0; i < playerCount; i++) {
		if (user[i].hitChk())
			return 1;
	}
	return 0;
}

void Casino::play(Casino* _casino) {
	char ans;
	//rozdanie wszystkim dwoch kart
	for (int i = 0; i < playerCount; i++) {
		user[i].takeCard(_casino);
		user[i].takeCard(_casino);
		std::cout << std::left << std::setw(20) << user[i].getName() << ": ";
		user[i].viewHand();
	}
	for (int i = 0; i < botCount; i++) {
		botUser[i].takeCard(_casino);
		botUser[i].takeCard(_casino);
		std::cout << std::left << std::setw(20) << botUser[i].getName() << ": ";
		botUser[i].viewHand();
	}

	while (anyHits() && !allLost()) { //petla dziala dopoki ktos jeszcze dobiera, i wszyscy jeszcze nie przegrali

		//gracze decyduja o dobraniu kart
		for (int i = 0; i < playerCount; i++) {
			if (user[i].getHandVal() < 21 && user[i].hitChk()) {
				do {
				std::cout << std::endl << user[i].getName() << ", dobierasz? (y/n):";
				ans = userInput<char>();
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');		//potrzebne zabezpieczenie gdyby ktos zle wprowadzil 
				} while (ans != 'y' && ans != 'n');
				user[i].setHit(ans);
				if (user[i].hitChk() == 1)
					user[i].takeCard(_casino);
			}
			else {
				user[i].setHit('n');
			}
		}
		//boty dobieraja karty
		for (int i = 0; i < botCount; i++) {
			switch (botUser[i].getBhvr()) {
			case 1: {																								//bot zachowawczy
				if (botUser[i].getHandVal() < CONSERVATIVE && botUser[i].hitChk())
					botUser[i].takeCard(_casino);
				else
					botUser[i].setHit('n');
				break;
			case 2: {																								//bot normalny
				if (botUser[i].getHandVal() < NORMAL && botUser[i].hitChk())
					botUser[i].takeCard(_casino);
				else
					botUser[i].setHit('n');
				break;
			}
			case 3: {																								//bot ryzykujacy
				if (botUser[i].getHandVal() < RISKY && botUser[i].hitChk())
					botUser[i].takeCard(_casino);
				else
					botUser[i].setHit('n');
				break;
			default:
				std::cout << "Blad zachowania botow." << std::endl;
				system("pause");
			}
			}
			}
		}
		//wyswietlenie kart wszystkich graczy na ekran
		system("cls");		
		viewHeadline();
		for (int i = 0; i < playerCount; i++) {
			std::cout << std::left << std::setw(20) << user[i].getName() << ": ";
			user[i].viewHand();
		}
		for (int i = 0; i < botCount; i++) {
			std::cout << std::left << std::setw(20) << botUser[i].getName() << ": ";
			botUser[i].viewHand();
		}
	}
	//sprawdzenie wynikow i okreslenie zwyciezcow, nie jest to optymalna metoda przez 4 petle, ale dziala bez zarzutu
	int highscore = getHighscore();
	for (int i = 0; i < playerCount; i++) {
		if (user[i].getHandVal() == highscore)
			std::cout << user[i].getName() << " wygrywa!" << std::endl;
		else
			std::cout << user[i].getName() << " przegrywa." << std::endl;
	}
	for (int i = 0; i < botCount; i++) {
		if (botUser[i].getHandVal() == highscore)
			std::cout << botUser[i].getName() << " wygrywa!" << std::endl;
		else
			std::cout << botUser[i].getName() << " przegrywa." << std::endl;
	}
	//zapisywanie do pliku + zabezpieczenia
	std::cout << "Zapisywanie wynikow do pliku tekstowego, podaj nazwe pliku razem z rozszerzeniem: " << std::endl;
	saveResults(userInput<std::string>());
}

bool Casino::allLost() {
	for (int i = 0; i < playerCount; i++) {
		if (user[i].getHandVal() < 22)
			return 0;
	}
	return 1;
}

int Casino::getHighscore() {
	int max = 0;
	for (int i = 0; i < playerCount; i++) {
		if (user[i].getHandVal() > max && user[i].getHandVal() < 22)
			max = user[i].getHandVal();
	}
	for (int i = 0; i < botCount; i++) {
		if (botUser[i].getHandVal() > max && botUser[i].getHandVal() < 22)
			max = botUser[i].getHandVal();
	}
	if (max == 0) {
		std::cout << "Wszyscy przegrali." << std::endl;
	}
	return max;
}

std::string Casino::getName(int _userId) {
	return user[_userId].getName();
}

int Casino::getPlayerCount() {
	return playerCount;
}

void Casino::saveResults(std::string _filename) {
	std::ofstream file(_filename);
	if (file.is_open() && !file.fail()) {
		for (int i = 0; i < playerCount; i++) {
			file << std::left << std::setw(20) << user[i].getName();
			file << std::left << std::setw(60) << user[i].getHand();
			file << std::left << std::setw(3) << user[i].getHandVal() << std::endl;
		}
		for (int i = 0; i < botCount; i++) {
			file << std::left << std::setw(20) << botUser[i].getName();
			file << std::left << std::setw(60) << botUser[i].getHand();
			file << std::left << std::setw(3) << botUser[i].getHandVal() << std::endl;
		}
	}
	else {
		std::cout << "Nie udalo sie stworzyc pliku o tej nazwie z wynikami." << std::endl;
	}
	file.close();
}