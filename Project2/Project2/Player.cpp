#include "Player.h"
#include "Casino.h"
#include <iomanip>

Player::Player(std::string _name): name(_name) {}

void Player::takeCard(Casino* _casino) {
	if (handCount < 10) {
		hand[handCount] = _casino->getCard();
		handCount++;
	}
	else {
		std::cout << "Pelna reka.";
	}
}

int Player::getHandVal() {
	int val = 0;
	if (handCount > 0) {
		for (int i = 0; i < handCount; i++) {
			val += hand[i]->getWartosc();
		}
		return val;
	}
	else
		return val;
}

void Player::viewHand() {
	if (handCount > 0) {
		std::cout;
		for (int i = 0; i < handCount; i++) {
			hand[i]->wypisz();
		}
		std::cout << std::endl;
	}
}

std::string Player::getHand() {
	std::string temp{};
	std::string kolor{};
	for (int i = 0; i < handCount; i++) {
		switch (hand[i]->getKolor()) {
		case 3:
			kolor = "(Kier) ";
			break;
		case 4:
			kolor = "(Karo) ";
			break;
		case 5:
			kolor = "(Trefl) ";
			break;
		case 6:
			kolor = "(Pik) ";
			break;
		default:
			return "Blad odczytania koloru karty ";
		}
		temp += hand[i]->getFigura();
		temp.append(kolor);
	}
	return temp;
}

bool Player::hitChk() {
	return hit;
}

void Player::setHit(char _ch) {
	if (_ch == 'y')
		hit = 1;
	else if (_ch == 'n')
		hit = 0;
	else
		std::cout << "Wrong user input." << std::endl;
}

std::string Player::getName() {
	return name;
}

void Player::setName(std::string _name) {
	name = _name;
}