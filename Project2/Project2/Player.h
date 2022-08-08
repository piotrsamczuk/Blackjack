#pragma once
#include <iostream>
#include "Karta.h"

class Casino;

class Player {
protected:
	std::string name;
	int handCount = 0;
	int handVal = 0;
	bool hit = 1; // 0- nie dobiera (pasuje), 1- dobiera
	Karta* hand[10];
public:
	Player() {};
	Player(std::string _name);
	void takeCard(Casino* _casino);
	int getHandVal();
	std::string getName();
	void setName(std::string _name);
	std::string getHand();
	void viewHand();
	bool hitChk();
	void setHit(char _ch);
};