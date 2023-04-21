#include "LeShips.h"

LeShips::LeShips(char look, int size) {
	this->look = look;
	this->size = size;
	tabx = new int[size];
	taby = new int[size];
}