#include "Map.h"
#include <iostream>

Map::Map(int x, int y, char look) {
	this->x = x;
	this->y = y;
	this->look = look;
	tab = new char* [y];
	for (int i = 0; i < x; i++) {
		tab[i] = new char [x];
	}
	for (int i = 1; i < x; i++) {
		for (int j = 1; j < y; j++) {
			tab[i][j]=look;
		}
	}
	tab[0][0] = '@';
	tab[1][0] = '1';
	tab[2][0] = '2';
	tab[3][0] = '3';
	tab[4][0] = '4';
	tab[5][0] = '5';
	tab[6][0] = '6';
	tab[7][0] = '7';
	tab[8][0] = '8';
	tab[9][0] = '9';
	tab[0][1] = 'A';
	tab[0][2] = 'B';
	tab[0][3] = 'C';
	tab[0][4] = 'D';
	tab[0][5] = 'E';
	tab[0][6] = 'F';
	tab[0][7] = 'G';
	tab[0][8] = 'H';
	tab[0][9] = 'I';
}



///
/*
	this->x = x;
	this->y = y;
	tab = new char* [y];
	for (int i = 0; i < x; i++) {
		tab[i] = new char [x];
	}
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			tab[i][j]='s';
		}
	}
*/
///


/*
	Map* mapa = new Map(15, 30);
	for (int i = 0; i < mapa->x; i++) {
		for (int j = 0; j < mapa->y; j++) {
			cout << mapa->tab[i][j];
		}
		cout << endl;
	}
*/