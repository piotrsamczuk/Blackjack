#pragma once
#include "utilities.h"
#include "Karta.h"
#include "Player.h"
#include "Bot.h"
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <string>

class Casino {
	Karta deck[52];
	Player user[3];
	Bot botUser[3];
	int currCard = 0;
	int playerCount = 0;
	int botCount = 0;
public:
	Casino();
	void setDeck();
	void shuffleDeck();
	void addPlayer(const std::string &_name, int userId);
	void setBots(int declaredBots);
	void addBot(int declaredBots, int bhvr);
	Karta* getCard();
	int getPlayerCount();
	std::string getName(int _userId);
	int getMaxHandVal();
	int getHighscore();
	bool allLost();
	bool anyHits();
	void saveResults(std::string _filename);
	void play(Casino* _casino);
};