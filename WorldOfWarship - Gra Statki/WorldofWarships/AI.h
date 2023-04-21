#pragma once
#include "Map.h"
#include "Leships.h"

class AI
{
public:
	Map* mapa;
	Map* mapa2;
	LeShips** statki;
	int size;
	AI(Map& mapa, Map& mapa2,int numberofships);
	//void move();
};

