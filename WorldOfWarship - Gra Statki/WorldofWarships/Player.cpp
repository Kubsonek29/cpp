#include "Player.h"
#include <iostream>
#include "windows.h"
using namespace std;

Player::Player(Map& mapa, Map& mapa2,int numberofships) {
	this->mapa = &mapa;
	this->mapa2 = &mapa2;
	this->size = numberofships;
	this->statki = new LeShips * [numberofships];
}


