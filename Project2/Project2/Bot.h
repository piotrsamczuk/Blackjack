#pragma once
#include "Player.h"

#define RISKY 19
#define NORMAL 16
#define CONSERVATIVE 13

class Bot: public Player {
	int bhvr = 2; //1- zachowawczy dobiera do 12 pkt, 2-normalny dobiera do 15 pkt, 3-ryzykujacy dobiera do 18 pkt
	int botCount = 0;
public:
	int getBhvr();
	void changeBhvr(int _bvr);
};