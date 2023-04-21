#pragma once
#include "Map.h"
#include "LeShips.h"

class Player
{
public:
	Map* mapa;
	Map* mapa2;
	LeShips** statki;
	int size;
	Player(Map& mapa, Map& mapa2,int numberofships);
	//void move();
};

