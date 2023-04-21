#pragma once
#include "Map.h"
#include "Player.h"
#include "AI.h"
#include "LeShips.h"

class ShipsMove
{
	Player* player;
	AI* ai;
	Map* map1;
	Map* map2;
public:
	int countlost;
	int countlostai;
	char missedlook;
	char shotlook;
	char shiplook;
	int* checkShip;
	int* checkShipai;
	ShipsMove(Player& player, AI& ai, Map& map1, Map& map2, char missedlook, char shotlook, char shiplook);
	void moveplayer();
	void moveai();
	void checkShipPlayer();
	void checkShipAI();
};

