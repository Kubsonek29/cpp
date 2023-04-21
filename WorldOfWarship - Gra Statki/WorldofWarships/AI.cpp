#include "AI.h"
#include <iostream>
#include "windows.h"

AI::AI(Map& mapa, Map& mapa2, int numberofships) {
	this->mapa = &mapa;
	this->mapa2 = &mapa2;
	this->size = numberofships;
	this->statki = new LeShips * [numberofships];
}
