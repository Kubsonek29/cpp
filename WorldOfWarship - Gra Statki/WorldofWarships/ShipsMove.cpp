#include "ShipsMove.h"
#include <iostream>
#include <map>
#include "windows.h"
using namespace std;

ShipsMove::ShipsMove(Player& player, AI& ai, Map& map1, Map& map2, char missedlook, char shotlook, char shiplook) {
	this->player = &player;
	this->ai = &ai;
	this->map1 = &map1;
	this->map2 = &map2;
	this->missedlook = missedlook;
	this->shotlook = shotlook;
	this->shiplook = shiplook;
	this->checkShip = new int[9];
	this->checkShipai = new int[9];
	this->countlost = 0;
	this->countlostai = 0;
	for (int i = 0; i < 9; i++) {
		checkShip[i] = 1;
		checkShipai[i] = 1;
	}
}

void ShipsMove::moveplayer() {
	int x=0;
	int y=0;
	int tmpx;
	char tmpy;
	int timer = 1;
	std::map<char, int> maps;
	maps['A'] = 1; maps['B'] = 2; maps['C'] = 3; maps['D'] = 4; maps['E'] = 5; maps['F'] = 6; maps['G'] = 7; maps['H'] = 8; maps['I'] = 9;
	while (timer) {
		std::map<char, int>::iterator it = maps.begin();
		cout << endl;
		cout << "Podaj koordynaty do odstrzalu np. A8, G2" << std::endl;
		cin >> tmpy >> tmpx;
		if (tmpx < 1 || tmpx > 9  || (tmpy != 'A' && tmpy != 'B' && tmpy != 'C' && tmpy != 'D' && tmpy != 'E' && tmpy != 'F' && tmpy != 'G' && tmpy != 'H' && tmpy != 'I')) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			throw exception("Podano zly typ koordynatow... try again!\n");
		}
		for (auto n : maps) {
			if (tmpy == it->first) {
				y = it->second;
			}
			++it;
		}
		x = tmpx;
		it = maps.begin();
		cout << "Podano -> " << x << " =x y= " << y << endl;
		if (map2->tab[x][y] == shiplook) {
			cout << "trafiony" << endl;
			for (int i = 0; i < ai->size; i++) {
				for (int j = 0; j < ai->statki[i]->size; j++) {
					if (ai->statki[i]->tabx[j] == x && ai->statki[i]->taby[j] == y) {
						ai->statki[i]->tabx[j] = 0;
						ai->statki[i]->taby[j] = 0;
						break;
					}
				}
			}
			map2->tab[x][y] = shotlook;
			timer = 0;
		}
		else if (map2->tab[x][y] == shotlook) {
			cout << "u already shot in here" << endl;
		}
		else {
			if (map2->tab[x][y] != missedlook) {
				cout << "Unluckily but u missed!" << endl;
				map2->tab[x][y] = missedlook;
				timer = 0;
			}
			else {
				cout << "juz tu strzelales i jest pusto bing chilling" << endl;
			}
		}
	}
}

void ShipsMove::moveai() {
	int timer = 1;
	int x;
	int y;
	while(timer){
		x = rand() % (map1->x - 1) + 1;
		y = rand() % (map1->y - 1) + 1;
		if (map1->tab[x][y] == shiplook) {
			for (int i = 0; i < player->size; i++) {
				for (int j = 0; j < player->statki[i]->size; j++) {
					if (player->statki[i]->tabx[j] == x && player->statki[i]->taby[j] == y) {
						player->statki[i]->tabx[j] = 0;
						player->statki[i]->taby[j] = 0;
						break;
					}
				}
			}
			map1->tab[x][y] = shotlook;
			timer = 0;
			cout << "you got shot in " << x << " " << y << endl;
		} 
		else if (map1->tab[x][y] == shotlook) {
			continue;
		}
		else if (map1->tab[x][y] == missedlook) {
			continue;
		}
		else {
			map1->tab[x][y] = missedlook;
			cout << "AI didnt hit you..." << endl;
			timer = 0;
		}
	}
}

void ShipsMove::checkShipPlayer() {
	int check;
	for (int i = 0; i < player->size; i++) {
		check = 0;
		for (int j = 0; j < player->statki[i]->size; j++) {
			if (player->statki[i]->tabx[j] == 0 && player->statki[i]->taby[j] == 0 && checkShip[i]==1) {
				check++;
			}
		}
		if (check == player->statki[i]->size) {
			countlost++;
			cout << "Zniszczono " << countlost << " statek graczowi!\t id statku == " << i << endl;
			checkShip[i] = 0;
			for (int k = 0; k < map1->x; k++) {
				for (int l = 0; l < map1->y; l++) {
					if (map1->tab[k][l] == 'S') {
						map1->tab[k][l] = 'X';
					}
				}
			}
		}
	}
}

void ShipsMove::checkShipAI() {
	int check;
	for (int i = 0; i < ai->size; i++) {
		check = 0;
		for (int j = 0; j < ai->statki[i]->size; j++) {
			if (ai->statki[i]->tabx[j] == 0 && ai->statki[i]->taby[j] == 0 && checkShipai[i] == 1) {
				check++;
			}
		}
		if (check == ai->statki[i]->size) {
			countlostai++;
			cout << "Zniszczono " << countlostai << " statek ai!\t id statku == " << i << endl;
			checkShipai[i] = 0;
			for (int k = 0; k < map2->x; k++) {
				for (int l = 0; l < map2->y; l++) {
					if (map2->tab[k][l] == 'S') {
						map2->tab[k][l] = 'X';
					}
				}
			}
		}
	}
}

