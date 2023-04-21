#include "RiverManager.h"
#include <iostream>
#include <fstream>
#include "windows.h"
#include <cstdlib>
#include <map>
#include <string>
using namespace std;

RiverManager::RiverManager(int x, int y) {
	map = new Map(x, y,'~');
	map2 = new Map(x, y,'~');
	player = new Player(*map, *map2, 9);
	ai = new AI(*map, *map2, 9);
	for (int i = 0; i < 9; i++) { //max 9 statkow;
		player->statki[i] = new LeShips(char(254), 9);  //max 9 dlugosc
		ai->statki[i] = new LeShips(char(254), 9);
	}
	shiplook = char(254);
	movement = new ShipsMove(*player, *ai, *map ,*map2, 'M', 'S', shiplook);
	all_size_player = 0;
	all_size_ai = 0;
	printer = 0;
}

void RiverManager::printgame() {
	for (int i = 0; i < map->x; i++) {
		for (int j = 0; j < map->y; j++) {
			cout << " " << map->tab[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void RiverManager::printgameai() {
	for (int i = 0; i < map2->x; i++) {
		for (int j = 0; j < map2->y; j++) {
			cout << " " << map2->tab[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void RiverManager::clear() {
	for (int i = 1; i < map->x; i++) {
		for (int j = 1; j < map->y; j++) {
			map->tab[i][j] = map->look;
		}
	}
}

void RiverManager::clearai() {
	for (int i = 1; i < map2->x; i++) {
		for (int j = 1; j < map2->y; j++) {
			if (map2->tab[i][j] != 'M' && map2->tab[i][j] != 'S' && map2->tab[i][j] != 'X') {
				map2->tab[i][j] = map2->look;
			}
		}
	}
}

void RiverManager::starterpackplayer() { 
	int s_size;
	std::map<char, int> maps;
	maps['A'] = 1; maps['B'] = 2; maps['C'] = 3; maps['D'] = 4; maps['E'] = 5; maps['F'] = 6; maps['G'] = 7; maps['H'] = 8; maps['I'] = 9;
	int x;
	int holdx;
	char y;
	char holdy;
	int tmpx=0;
	int tmpy=0;
	int contship=0;
	std::map<char, int>::iterator it = maps.begin();
	cout << "Podaj ilosc statkow w grze -> ";
	cin >> all_size_player;
	if (all_size_player < 1 || all_size_player > 9) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		throw exception("Invalid number of ships... Try again!");
	}
	player->size = all_size_player;
	cout << endl;
	for (int i = 1; i <= all_size_player; i++) {
		int gam = 1;
		int kers = 1;
		int savex = 0;
		int savey = 0;
		while (gam) {
			cout << "Podaj rozmiar " << i << " statku -> ";
			cin >> s_size;
			if (s_size < 1 || s_size > 9) {
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cout << "Invalid size of a ship... Try again!" << endl;
				Sleep(1000);
			}
			else {
				gam = 0;
			}
		}
		cout << endl;
		player->statki[i - 1]->size = s_size;
		int timer = 1;
		int badcheck = 0;
		if (i > 1) {
			for (int i = 1; i < map->x; i++) {
				for (int j = 1; j < map->y; j++) {
					if (map->tab[i][j] == '#') {
						map->tab[i][j] = shiplook;
					}
				}
			}
		}
		for (int j = 1; j <= s_size; j++) {
			timer = 1;
			while (timer) {
				bool changer = true;
				printgame();
				int gem = 1;
				while (gem) {
					cout << "Podaj " << j << " koordynaty " << i << " statku   - size => " << s_size << "\tnp: B3, H8 lub zeby wyczyscic aktualny statek '00'  ->   ";
					cin >> y >> x;
					if (y == '0' || x == '0') {
						cin.clear();
						cin.ignore(INT_MAX, '\n');
						for (int k = 0; k < j - 1; k++) {
							map->tab[player->statki[i - 1]->tabx[k]][player->statki[i - 1]->taby[k]] = map->look;
							player->statki[i - 1]->tabx[k] = 0;
							player->statki[i - 1]->taby[k] = 0;
						}
						cout << "Zresetowano " << i << " aktualny statek" << endl;
						j = 1;
						printgame();
						continue;
					}
					if (x < 1 || x > 9 || (y != 'A' && y != 'B' && y != 'C' && y != 'D' && y != 'E' && y != 'F' && y != 'G' && y != 'H' && y != 'I')) {
						cin.clear();
						cin.ignore(INT_MAX, '\n');
						cout << endl << "Invalid cooradinate for ship... Try again!" << endl;
						Sleep(1000);
					}
					else {
						gem = 0;
					}
				}
				cout << y << " " << x << endl;
				for (auto n : maps) {
					if (y == it->first) {
						tmpy = it->second;
					}
					++it;
				}
				tmpx = x;
				if (j == 1) {
					savex = tmpx;
					savey = tmpy;
				}
				it = maps.begin();
				badcheck = 0;
				if (j > 2) {
					if (contship == 1) {
						if (tmpx == holdx + 1 && tmpy == holdy) {
							changer = true;
						}
						else if (tmpx == savex - kers && tmpy == holdy) {
							kers++;
							changer = false;
						}
						else {   
							badcheck = 1;
						}
					}
					else if (contship == 2) {
						if (tmpx == holdx - 1 && tmpy == holdy) {
							changer = true;
						}
						else if (tmpx == savex + kers && tmpy == holdy) {
							kers++;
							changer = false;
						}
						else {
							badcheck = 1;
						}
					}
					else if (contship==3) {
						if (tmpx == holdx && tmpy == holdy + 1) {
							changer = true;
						}
						else if (tmpx == holdx && tmpy == savey - kers) {
							kers++;
							changer = false;
						}
						else {
							badcheck = 1;
						}
					}
					else if (contship==4) {
						if (tmpx == holdx && tmpy == holdy - 1) {
							changer = true;
						}
						else if (tmpx == holdx && tmpy == savey + kers) {
							kers++;
							changer = false;
						}
						else {
							badcheck = 1;
						}
					}
					if (badcheck == 1) {
						cout << "Podano niepoprawne dane... Try again!" << endl;
						Sleep(1000);
					}
				}
				if (j == 2) {
					if (tmpx == holdx + 1 && tmpy == holdy ){
						contship = 1;
					}
					else if (tmpx == holdx - 1 && tmpy == holdy) {
						contship = 2;
					}
					else if (tmpx == holdx && tmpy == holdy + 1) {
						contship = 3;
					}
					else if (tmpx == holdx && tmpy == holdy - 1) {
						contship = 4; 
					}
					else {
						cout << endl << "Podana wspolrzedna nie laczy sie ze statkiem...   " << endl;
						badcheck = 1;
					}
				}
				if (tmpx > 9 || tmpx <= 0 || tmpy > 9 || tmpy <= 0) {
					cout << endl << "Bledne koordynaty... Sprobuj ponownie..." << endl;
					badcheck = 1;
				}
				if (tmpx == 9 && tmpy == 9) {
					if (map->tab[tmpx][tmpy] == shiplook || map->tab[tmpx - 1][tmpy - 1] == shiplook || map->tab[tmpx][tmpy - 1] == shiplook || map->tab[tmpx - 1][tmpy] == shiplook) {
						cout << endl << "Statki musza miec odstep od siebie co najmniej 1 kratke... (na ukos te¿)... " << endl;
						badcheck = 1;
					}
				}
				else if (tmpx == 9) {
					if (map->tab[tmpx][tmpy] == shiplook || map->tab[tmpx][tmpy - 1] == shiplook || map->tab[tmpx][tmpy + 1] == shiplook || map->tab[tmpx - 1][tmpy - 1] == shiplook || map->tab[tmpx - 1][tmpy] == shiplook || map->tab[tmpx - 1][tmpy + 1] == shiplook) {
						cout << endl << "Statki musza miec odstep od siebie co najmniej 1 kratke... (na ukos te¿)... " << endl;
						badcheck = 1;
					}
				}
				else if (tmpy == 9) {
					if (map->tab[tmpx][tmpy] == shiplook || map->tab[tmpx - 1][tmpy] == shiplook || map->tab[tmpx - 1][tmpy - 1] == shiplook || map->tab[tmpx][tmpy - 1] == shiplook || map->tab[tmpx + 1][tmpy - 1] == shiplook || map->tab[tmpx + 1][tmpy] == shiplook) {
						cout << endl << "Statki musza miec odstep od siebie co najmniej 1 kratke... (na ukos te¿)... " << endl;
						badcheck = 1;
					}
				}
				else if (tmpx < 9 && tmpy < 9) {
					if (map->tab[tmpx][tmpy] == shiplook || map->tab[tmpx - 1][tmpy - 1] == shiplook || map->tab[tmpx - 1][tmpy] == shiplook || map->tab[tmpx - 1][tmpy + 1] == shiplook || map->tab[tmpx][tmpy - 1] == shiplook || map->tab[tmpx][tmpy + 1] == shiplook || map->tab[tmpx + 1][tmpy - 1] == shiplook || map->tab[tmpx + 1][tmpy] == shiplook || map->tab[tmpx + 1][tmpy + 1] == shiplook) {
						cout << endl << "Statki musza miec odstep od siebie co najmniej 1 kratke... (na ukos te¿)... " << endl;
						badcheck = 1;
					}
				}
				if (badcheck == 0) {
					player->statki[i - 1]->tabx[j - 1] = tmpx;
					player->statki[i - 1]->taby[j - 1] = tmpy;
					map->tab[tmpx][tmpy] = '#';
					cout << endl << player->statki[i - 1]->tabx[j - 1] << endl;
					cout << endl << player->statki[i - 1]->taby[j - 1] << endl;
					timer = 0;
					if (changer == true) {
						holdx = tmpx;
						holdy = tmpy;
					}
				}
			}
		}
	}
	for (int i = 1; i < map->x; i++) {
		for (int j = 1; j < map->y; j++) {
			if (map->tab[i][j] == '#') {
				map->tab[i][j] = shiplook;
			}
		}
	}
}

void RiverManager::starterpackloaded() {
	int s_size=0;
	std::map<char, int> maps;
	maps['A'] = 1; maps['B'] = 2; maps['C'] = 3; maps['D'] = 4; maps['E'] = 5; maps['F'] = 6; maps['G'] = 7; maps['H'] = 8; maps['I'] = 9;
	int x;
	int holdx;
	char y;
	char holdy;
	int tmpx = 0;
	int tmpy = 0;
	int contship = 0;
	std::map<char, int>::iterator it = maps.begin();
	for (int i = 1; i <= all_size_player; i++) {
		int gam = 1;
		int kers = 1;
		int savex = 0;
		int savey = 0;
		int timer = 1;
		int badcheck = 0;
		if (i > 1) {
			for (int i = 1; i < map->x; i++) {
				for (int j = 1; j < map->y; j++) {
					if (map->tab[i][j] == '#') {
						map->tab[i][j] = shiplook;
					}
				}
			}
		}
		for (int j = 1; j <= player->statki[i-1]->size; j++) {
			timer = 1;
			while (timer) {
				bool changer = true;
				printgame();
				int gem = 1;
				while (gem) {
					cout << "Podaj " << j << " koordynaty " << i << " statku   - size => " << player->statki[i-1]->size <<"\tnp: B3, H8 lub zeby wyczyscic aktualny statek '00'  ->   ";
					cin >> y >> x;
					if (y == '0' || x=='0') {
						cin.clear();
						cin.ignore(INT_MAX, '\n');
						for (int k = 0; k < j-1; k++) {
							map->tab[player->statki[i - 1]->tabx[k]][player->statki[i - 1]->taby[k]] = map->look;
							player->statki[i - 1]->tabx[k] = 0;
							player->statki[i - 1]->taby[k] = 0;
						}
						cout << "Zresetowano " << i << " aktualny statek" << endl;
						j = 1;
						printgame();
						continue;
					}
					if (x < 1 || x > 9 || (y != 'A' && y != 'B' && y != 'C' && y != 'D' && y != 'E' && y != 'F' && y != 'G' && y != 'H' && y != 'I')) {
						cin.clear();
						cin.ignore(INT_MAX, '\n');
						cout << endl << "Invalid cooradinate for ship... Try again!" << endl;
						Sleep(1000);
					}
					else {
						gem = 0;
					}
				}
				cout << y << " " << x << endl;
				for (auto n : maps) {
					if (y == it->first) {
						tmpy = it->second;
					}
					++it;
				}
				tmpx = x;
				if (j == 1) {
					savex = tmpx;
					savey = tmpy;
				}
				it = maps.begin();
				badcheck = 0;
				if (j > 2) {
					if (contship == 1) {
						if (tmpx == holdx + 1 && tmpy == holdy) {
							changer = true;
						}
						else if (tmpx == savex - kers && tmpy == holdy) {
							kers++;
							changer = false;
						}
						else {
							badcheck = 1;
						}
					}
					else if (contship == 2) {
						if (tmpx == holdx - 1 && tmpy == holdy) {
							changer = true;
						}
						else if (tmpx == savex + kers && tmpy == holdy) {
							kers++;
							changer = false;
						}
						else {
							badcheck = 1;
						}
					}
					else if (contship == 3) {
						if (tmpx == holdx && tmpy == holdy + 1) {
							changer = true;
						}
						else if (tmpx == holdx && tmpy == savey - kers) {
							kers++;
							changer = false;
						}
						else {
							badcheck = 1;
						}
					}
					else if (contship == 4) {
						if (tmpx == holdx && tmpy == holdy - 1) {
							changer = true;
						}
						else if (tmpx == holdx && tmpy == savey + kers) {
							kers++;
							changer = false;
						}
						else {
							badcheck = 1;
						}
					}
					if (badcheck == 1) {
						cout << "Podano niepoprawne dane... Try again!" << endl;
						Sleep(1000);
					}
				}
				if (j == 2) {
					if (tmpx == holdx + 1 && tmpy == holdy) {
						contship = 1;
					}
					else if (tmpx == holdx - 1 && tmpy == holdy) {
						contship = 2;
					}
					else if (tmpx == holdx && tmpy == holdy + 1) {
						contship = 3;
					}
					else if (tmpx == holdx && tmpy == holdy - 1) {
						contship = 4;
					}
					else {
						cout << endl << "Podana wspolrzedna nie laczy sie ze statkiem...   " << endl;
						badcheck = 1;
					}
				}
				if (tmpx > 9 || tmpx <= 0 || tmpy > 9 || tmpy <= 0) {
					cout << endl << "Bledne koordynaty... Sprobuj ponownie..." << endl;
					badcheck = 1;
				}
				if (tmpx == 9 && tmpy == 9) {
					if (map->tab[tmpx][tmpy] == shiplook || map->tab[tmpx - 1][tmpy - 1] == shiplook || map->tab[tmpx][tmpy - 1] == shiplook || map->tab[tmpx - 1][tmpy] == shiplook) {
						cout << endl << "Statki musza miec odstep od siebie co najmniej 1 kratke... (na ukos te¿)... " << endl;
						badcheck = 1;
					}
				}
				else if (tmpx == 9) {
					if (map->tab[tmpx][tmpy] == shiplook || map->tab[tmpx][tmpy - 1] == shiplook || map->tab[tmpx][tmpy + 1] == shiplook || map->tab[tmpx - 1][tmpy - 1] == shiplook || map->tab[tmpx - 1][tmpy] == shiplook || map->tab[tmpx - 1][tmpy + 1] == shiplook) {
						cout << endl << "Statki musza miec odstep od siebie co najmniej 1 kratke... (na ukos te¿)... " << endl;
						badcheck = 1;
					}
				}
				else if (tmpy == 9) {
					if (map->tab[tmpx][tmpy] == shiplook || map->tab[tmpx - 1][tmpy] == shiplook || map->tab[tmpx - 1][tmpy - 1] == shiplook || map->tab[tmpx][tmpy - 1] == shiplook || map->tab[tmpx + 1][tmpy - 1] == shiplook || map->tab[tmpx + 1][tmpy] == shiplook) {
						cout << endl << "Statki musza miec odstep od siebie co najmniej 1 kratke... (na ukos te¿)... " << endl;
						badcheck = 1;
					}
				}
				else if (tmpx < 9 && tmpy < 9) {
					if (map->tab[tmpx][tmpy] == shiplook || map->tab[tmpx - 1][tmpy - 1] == shiplook || map->tab[tmpx - 1][tmpy] == shiplook || map->tab[tmpx - 1][tmpy + 1] == shiplook || map->tab[tmpx][tmpy - 1] == shiplook || map->tab[tmpx][tmpy + 1] == shiplook || map->tab[tmpx + 1][tmpy - 1] == shiplook || map->tab[tmpx + 1][tmpy] == shiplook || map->tab[tmpx + 1][tmpy + 1] == shiplook) {
						cout << endl << "Statki musza miec odstep od siebie co najmniej 1 kratke... (na ukos te¿)... " << endl;
						badcheck = 1;
					}
				}
				if (badcheck == 0) {
					player->statki[i - 1]->tabx[j - 1] = tmpx;
					player->statki[i - 1]->taby[j - 1] = tmpy;
					map->tab[tmpx][tmpy] = '#';
					cout << endl << player->statki[i - 1]->tabx[j - 1] << endl;
					cout << endl << player->statki[i - 1]->taby[j - 1] << endl;
					timer = 0;
					if (changer == true) {
						holdx = tmpx;
						holdy = tmpy;
					}
				}
			}
		}
	}
	for (int i = 1; i < map->x; i++) {
		for (int j = 1; j < map->y; j++) {
			if (map->tab[i][j] == '#') {
				map->tab[i][j] = shiplook;
			}
		}
	}
}


void RiverManager::starterpackai() {  
	srand(time(NULL));
	int x;
	int y;
	int timer;
	int safety = 0;
	int safer = 0;
	int tmpx;
	int tmpy;
	all_size_ai = all_size_player;
	ai->size = player->size;
	int decider;
	for (int i = 0; i < all_size_player; i++) {
		do {
			x = rand() % (map2->x-1) + 1;
			y = rand() % (map2->y-1) + 1;
			if (map2->tab[x][y] == map2->look &&  (x+player->statki[i]->size<=map->x && y || player->statki[i]->size <= map->y || x - player->statki[i]->size > 0 || y - player->statki[i]->size > 0)) {
				break;
			}
		} while (map2->tab[x][y] != shiplook);
		timer = 1;
		tmpx = x;
		tmpy = y;
		while (timer) {
			decider = rand() % 3;
			if (decider == 0) { 
				int badcheck = 0;
				int checker = 0;
				for (int k = 0; k < player->statki[i]->size; k++) {
					if (x + k >= map->x) {
						badcheck = 1;
						break;
					}
					if (tmpx + k == 9 && tmpy == 9) {
						if (map2->tab[tmpx+k][tmpy] == shiplook || map2->tab[tmpx + k - 1][tmpy - 1] == shiplook || map2->tab[tmpx + k][tmpy - 1] == shiplook || map2->tab[tmpx + k - 1][tmpy] == shiplook) {
							badcheck = 1;
						}
					}
					else if (tmpx + k == 9) {
						if (map2->tab[tmpx + k][tmpy] == shiplook || map2->tab[tmpx + k][tmpy - 1] == shiplook || map2->tab[tmpx + k][tmpy + 1] == shiplook || map2->tab[tmpx + k - 1][tmpy - 1] == shiplook || map2->tab[tmpx + k - 1][tmpy] == shiplook || map2->tab[tmpx + k - 1][tmpy + 1] == shiplook) {
							badcheck = 1;
						}
					}
					else if (tmpy == 9) {
						if (map2->tab[tmpx + k][tmpy] == shiplook || map2->tab[tmpx + k - 1][tmpy] == shiplook || map2->tab[tmpx + k - 1][tmpy - 1] == shiplook || map2->tab[tmpx + k][tmpy - 1] == shiplook || map2->tab[tmpx + k + 1][tmpy - 1] == shiplook || map2->tab[tmpx + k + 1][tmpy] == shiplook) {
							badcheck = 1;
						}
					}
					else if (tmpx + k < 9 && tmpy < 9) {
						if (map2->tab[tmpx + k][tmpy] == shiplook || map2->tab[tmpx + k - 1][tmpy - 1] == shiplook || map2->tab[tmpx + k - 1][tmpy] == shiplook || map2->tab[tmpx + k - 1][tmpy + 1] == shiplook || map2->tab[tmpx + k][tmpy - 1] == shiplook || map2->tab[tmpx + k][tmpy + 1] == shiplook || map2->tab[tmpx + k + 1][tmpy - 1] == shiplook || map2->tab[tmpx + k + 1][tmpy] == shiplook || map2->tab[tmpx + k + 1][tmpy + 1] == shiplook) {
							badcheck = 1;
						}
					}
					if (map2->tab[x + k][y] == shiplook) {
						badcheck = 1;
						break;
					}
					
				}
				if (badcheck == 0) {
					ai->statki[i]->size = player->statki[i]->size;
					for (int k = 0; k < player->statki[i]->size; k++) {
						ai->statki[i]->tabx[k] = x+k;
						ai->statki[i]->taby[k] = y;
						map2->tab[ai->statki[i]->tabx[k]][ai->statki[i]->taby[k]] = shiplook;
					}
					timer = 0;
				}
			}
			else if (decider == 1) { 
				int badcheck = 0;
				for (int k = 0; k < player->statki[i]->size; k++) {
					if (x - k == 0) {
						badcheck = 1;
						break;
					}
					if (tmpx - k == 9 && tmpy == 9) {
						if (map2->tab[tmpx - k][tmpy] == shiplook || map2->tab[tmpx - k - 1][tmpy - 1] == shiplook || map2->tab[tmpx - k][tmpy - 1] == shiplook || map2->tab[tmpx - k - 1][tmpy] == shiplook) {
							badcheck = 1;
						}
					}
					else if (tmpx - k == 9) {
						if (map2->tab[tmpx - k][tmpy] == shiplook || map2->tab[tmpx - k][tmpy - 1] == shiplook || map2->tab[tmpx - k][tmpy + 1] == shiplook || map2->tab[tmpx - k - 1][tmpy - 1] == shiplook || map2->tab[tmpx - k - 1][tmpy] == shiplook || map2->tab[tmpx - k - 1][tmpy + 1] == shiplook) {
							badcheck = 1;
						}
					}
					else if (tmpy == 9) {
						if (map2->tab[tmpx - k][tmpy] == shiplook || map2->tab[tmpx - k - 1][tmpy] == shiplook || map2->tab[tmpx - k - 1][tmpy - 1] == shiplook || map2->tab[tmpx - k][tmpy - 1] == shiplook || map2->tab[tmpx - k + 1][tmpy - 1] == shiplook || map2->tab[tmpx - k + 1][tmpy] == shiplook) {
							badcheck = 1;
						}
					}
					else if (tmpx - k < 9 && tmpy < 9) {
						if (map2->tab[tmpx - k][tmpy] == shiplook || map2->tab[tmpx - k - 1][tmpy - 1] == shiplook || map2->tab[tmpx - k - 1][tmpy] == shiplook || map2->tab[tmpx - k - 1][tmpy + 1] == shiplook || map2->tab[tmpx - k][tmpy - 1] == shiplook || map2->tab[tmpx - k][tmpy + 1] == shiplook || map2->tab[tmpx - k + 1][tmpy - 1] == shiplook || map2->tab[tmpx - k + 1][tmpy] == shiplook || map2->tab[tmpx - k + 1][tmpy + 1] == shiplook) {
							badcheck = 1;
						}
					}
					if (map2->tab[x - k][y] == shiplook) {
						badcheck = 1;
						break;
					}
				}
				if (badcheck == 0) {
					ai->statki[i]->size = player->statki[i]->size;
					for (int k = player->statki[i]->size-1; k >= 0; k--) {
						ai->statki[i]->tabx[k] = x-k;
						ai->statki[i]->taby[k] = y;
						map2->tab[ai->statki[i]->tabx[k]][ai->statki[i]->taby[k]] = shiplook;
					}

					timer = 0;
				}
			}
			else if (decider == 2) { 
				int badcheck = 0;
				for (int k = 0; k < player->statki[i]->size; k++) {
					if (y + k >= map->y) {
						badcheck = 1;
						break;
					}
					if (tmpx == 9 && tmpy + k == 9) {
						if (map2->tab[tmpx][tmpy + k] == shiplook || map2->tab[tmpx - 1][tmpy - 1 + k] == shiplook || map2->tab[tmpx][tmpy - 1 + k] == shiplook || map2->tab[tmpx - 1][tmpy + k] == shiplook) {
							badcheck = 1;
						}
					}
					else if (tmpx == 9) {
						if (map2->tab[tmpx][tmpy + k] == shiplook || map2->tab[tmpx][tmpy - 1 + k] == shiplook || map2->tab[tmpx][tmpy + 1 + k] == shiplook || map2->tab[tmpx - 1][tmpy - 1 + k] == shiplook || map2->tab[tmpx- 1][tmpy + k] == shiplook || map2->tab[tmpx - 1][tmpy + 1 + k] == shiplook) {
							badcheck = 1;
						}
					}
					else if (tmpy + k == 9) {
						if (map2->tab[tmpx][tmpy + k] == shiplook || map2->tab[tmpx - 1][tmpy + k] == shiplook || map2->tab[tmpx - 1][tmpy - 1 + k] == shiplook || map2->tab[tmpx][tmpy - 1 + k] == shiplook || map2->tab[tmpx + 1][tmpy - 1 + k] == shiplook || map2->tab[tmpx + 1][tmpy + k] == shiplook) {
							badcheck = 1;
						}
					}
					else if (tmpx < 9 && tmpy + k < 9) {
						if (map2->tab[tmpx][tmpy + k] == shiplook || map2->tab[tmpx - 1][tmpy - 1 + k] == shiplook || map2->tab[tmpx - 1][tmpy + k] == shiplook || map2->tab[tmpx - 1][tmpy + 1 + k] == shiplook || map2->tab[tmpx][tmpy - 1 + k] == shiplook || map2->tab[tmpx][tmpy + 1 + k] == shiplook || map2->tab[tmpx + 1][tmpy - 1 + k] == shiplook || map2->tab[tmpx + 1][tmpy + k] == shiplook || map2->tab[tmpx + 1][tmpy + 1 + k] == shiplook) {
							badcheck = 1;
						}
					}
					if (map2->tab[x][y + k] == shiplook) {
						badcheck = 1;
						break;
					}
				}
				if (badcheck == 0) {
					ai->statki[i]->size = player->statki[i]->size;
					for (int k = 0; k < player->statki[i]->size; k++) {
						ai->statki[i]->tabx[k] = x; 
						ai->statki[i]->taby[k] = y+k;
						map2->tab[ai->statki[i]->tabx[k]][ai->statki[i]->taby[k]] = shiplook;
					}
					timer = 0;
				}
			}
			else if (decider == 3) {
				int badcheck = 0;
				for (int k = 0; k < player->statki[i]->size; k++) {
					if (y - k == 0) {
						badcheck = 1;
						break;
					}
					if (tmpx == 9 && tmpy - k == 9) {
						if (map2->tab[tmpx][tmpy - k] == shiplook || map2->tab[tmpx - 1][tmpy - 1 - k] == shiplook || map2->tab[tmpx][tmpy - 1 - k] == shiplook || map2->tab[tmpx - 1][tmpy - k] == shiplook) {
							badcheck = 1;
						}
					}
					else if (tmpx == 9) {
						if (map2->tab[tmpx][tmpy - k] == shiplook || map2->tab[tmpx][tmpy - 1 - k] == shiplook || map2->tab[tmpx][tmpy + 1 - k] == shiplook || map2->tab[tmpx - 1][tmpy - 1 - k] == shiplook || map2->tab[tmpx - 1][tmpy - k] == shiplook || map2->tab[tmpx - 1][tmpy + 1 - k] == shiplook) {
							badcheck = 1;
						}
					}
					else if (tmpy - k == 9) {
						if (map2->tab[tmpx][tmpy - k] == shiplook || map2->tab[tmpx - 1][tmpy - k] == shiplook || map2->tab[tmpx - 1][tmpy - 1 - k] == shiplook || map2->tab[tmpx][tmpy - 1 - k] == shiplook || map2->tab[tmpx + 1][tmpy - 1 - k] == shiplook || map2->tab[tmpx + 1][tmpy - k] == shiplook) {
							badcheck = 1;
						}
					}
					else if (tmpx < 9 && tmpy - k < 9) {
						if (map2->tab[tmpx][tmpy - k] == shiplook || map2->tab[tmpx - 1][tmpy - 1 - k] == shiplook || map2->tab[tmpx - 1][tmpy - k] == shiplook || map2->tab[tmpx - 1][tmpy + 1 - k] == shiplook || map2->tab[tmpx][tmpy - 1 - k] == shiplook || map2->tab[tmpx][tmpy + 1 - k] == shiplook || map2->tab[tmpx + 1][tmpy - 1 - k] == shiplook || map2->tab[tmpx + 1][tmpy - k] == shiplook || map2->tab[tmpx + 1][tmpy + 1 - k] == shiplook) {
							badcheck = 1;
						}
					}
					if (map2->tab[x][y-k] == shiplook) {
						badcheck = 1;
						break;
					}
				}
				if (badcheck == 0) {
					ai->statki[i]->size = player->statki[i]->size;
					for (int k = player->statki[i]->size-1; k >= 0; k--) {
						ai->statki[i]->tabx[k] = x;
						ai->statki[i]->taby[k] = y-k;
						map2->tab[ai->statki[i]->tabx[k]][ai->statki[i]->taby[k]] = shiplook;
					}
					timer = 0;
				}
			}
			safety++;
			if (safety > 100) {
				safety = 0;
				safer++;
				i--;
				break;
			}
			if (safer > 50) {
				safer = 0;
				clearai();
				i = 0;
				break;
			}
		}
	}
	/// <summary>
	cout << endl;
	for (int i = 0; i < all_size_ai; i++) {
		for (int j = 0; j < ai->statki[i]->size; j++) {
			cout << ai->statki[i]->tabx[j] << "=x y=" << ai->statki[i]->taby[j] << endl;
		}
		cout << endl;
	}
	/// </summary>
}

void RiverManager::setshipsontheriver() {

	for (int i = 0; i < all_size_player; i++) {
		for (int j = 0; j < player->statki[i]->size; j++) {
			map->tab[player->statki[i]->tabx[j]][player->statki[i]->taby[j]] = shiplook;
		}
	}
}

void RiverManager::setYahrrontheriver() { 
	for (int i = 0; i < all_size_ai; i++) {
		for (int j = 0; j < ai->statki[i]->size; j++) {
			if (ai->statki[i]->tabx[j] != 0 && ai->statki[i]->taby[j] != 0) {
				map2->tab[ai->statki[i]->tabx[j]][ai->statki[i]->taby[j]] = shiplook;
			}
		}
	}
}

void RiverManager::showmenu() {
	cout << "1 -> Save the game to the file [savefile.txt]" << endl;
	cout << "2 -> Quit the game and not save the game" << endl;
	cout << "3 -> Quit the game and save the game" << endl;
	cout << "4 -> Resume the game :)" << endl;
}

int RiverManager::menutool() {
	int tmp;
	showmenu();
	cin >> tmp;
	if (tmp != 1 && tmp != 2 && tmp != 3 && tmp != 4) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		throw invalid_argument("Zla opcja do menu...\n");
	}
	if (tmp == 1) {
		SaveTheGameToFile();
		cout << "Zapisano postêp gry do pliku wznawianie gry..." << endl;
		Sleep(250);
	}
	else if (tmp == 2) {
		cout << "Wychodzenie z gry..." << endl;
		Sleep(250);
		changestatusfalse();
	}
	else if (tmp == 3) {
		SaveTheGameToFile();
		cout << "Zapisano postêp gry... quitting..." << endl;
		Sleep(250);
		changestatusfalse();
	}
	else if (tmp == 4) {
		cout << "Wznawianie gry :)" << endl;
		Sleep(250);
	}
	return tmp;
}


bool RiverManager::checkstatus() {
	int badcheck = 0;
	int check=0;
	int badcheckai = 0;
	int checkai = 0;
	///
	for (int i = 0; i < all_size_player; i++) {
		for (int j = 0; j < player->statki[i]->size; j++) {
			if (player->statki[i]->tabx[j] == 0 && player->statki[i]->taby[j] == 0) {
				badcheck++;
			}
		}
		if (badcheck == player->statki[i]->size) {
			check++;
		}
		badcheck = 0;
	}
	///
	for (int i = 0; i < all_size_ai; i++) {
		for (int j = 0; j < ai->statki[i]->size; j++) {
			if (ai->statki[i]->tabx[j] == 0 && ai->statki[i]->taby[j] == 0) {
				badcheckai++;
			}
		}
		if (badcheckai == ai->statki[i]->size) {
			checkai++;
		}
		badcheckai = 0;
	}
	///
	if (check == all_size_player) {
		if (printer == 0) {
			cout << "AI won the game!!!" << endl;
			printer++;
		}
		Sleep(500);
		return false;
	}
	else if (checkai == all_size_ai) {
		if (printer == 0) {
			cout << "The Player won the game!!!" << endl;
			printer++;
		}
		Sleep(500);
		return false;
	}
	else {
		return true;
	}

}

bool RiverManager::checkstatusP() {
	for (int i = 0; i < player->size; i++) {
		for (int j = 0; j < player->statki[i]->size; j++) {
			if (player->statki[i]->tabx[j] <= 0 || player->statki[i]->taby[j] <= 0) {
				return false;
			}
		}
	}
	return true;
}

void RiverManager::changestatusfalse() {
	status = false;
}

void RiverManager::move() {
	movement->moveplayer();
	movement->moveai();
	movement->checkShipPlayer();
	movement->checkShipAI();
}

int RiverManager::beginningpack() {
	int timer = 1;
	int tmp;
	while (timer) {
		cout << "1 - Zacznij nowa gre [Player vs AI]" << endl;
		cout << "2 - Wczytaj gre z pliku [savefile.txt]" << endl;
		cout << "3 - Wczytaj ilosc statkow dla gracza z pliku [config.txt]" << endl;
		cin >> tmp;
		if (tmp != 1 && tmp != 2 && tmp!= 3) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			throw invalid_argument("Podano zla opcje...\n");
			Sleep(1000);
		}
		else {
			return tmp;
		}
	}
	return -1;
}

void RiverManager::SaveTheGameToFile() {
	fstream myfile;
	myfile.open("savefile.txt", ios::out);
	myfile << "Player:" << endl;
	for (int i = 0; i < all_size_player; i++) {
		myfile << i << endl;
		for (int j = 0; j < player->statki[i]->size; j++) {
			myfile << player->statki[i]->tabx[j] << " " << player->statki[i]->taby[j] << endl;
		}
	}
	myfile << "AI:" << endl;
	for (int i = 0; i < all_size_ai; i++) {
		myfile << i << endl;
		for (int j = 0; j < ai->statki[i]->size; j++) {
			myfile << ai->statki[i]->tabx[j] << " " << ai->statki[i]->taby[j] << endl;
		}
	}
	if (myfile) {
		cout << "succesfully saved" << endl;
	}
	myfile.close();
}

bool RiverManager::loadpreset() {
	fstream myfile;
	string line;
	string tmp = "";
	int count, sizeS;
	int i = 0;
	int counter = 0;
	int allsizep=0;
	myfile.open("config.txt", ios::in);
	if (myfile.is_open()) {
		while (myfile >> count >> sizeS) {
			if (i == 9) {
				throw exception("Config file has more ships than it should have...");
			}
			counter += count;
			for (; i < counter; i++) {
				player->statki[i]->size = sizeS;
				allsizep++;
			}
			cout << count << " " <<  sizeS << endl;
		}
		all_size_player = allsizep;
		player->size = allsizep;
		return true;
	}
	else {
		throw exception("No config file exists...");
		return false;
	}
}

bool RiverManager::ReadTheGameFromFile() {
	fstream myfile;
	string line;
	string tmp = "";
	int i=0;
	int x=0, y=0, number=0, sizeS=0, allsizep=0, allsizea=0;
	myfile.open("savefile.txt", ios::in);
	if (myfile.is_open()) {
		for (int i = 0; i < 9; i++) {
			player->statki[i]->size = 0;
			ai->statki[i]->size = 0;
		}
		while (getline(myfile, line)) {
			if (line == "Player:") {
				i = 1;
				continue;
			}
			if (line == "AI:") {
				i = 2;
				continue;
			}
			if (i == 1 || i == 2) {
				if (line.length() == 3 && isdigit(line[0]) && isdigit(line[2])) {
					if (i == 1) {
						player->statki[sizeS]->tabx[number] = stoi(line.substr(0, 1));
						player->statki[sizeS]->taby[number] = stoi(line.substr(2, 1));
						player->statki[sizeS]->size++;
						number++;
					}
					else if (i == 2) {
						ai->statki[sizeS]->tabx[number] = stoi(line.substr(0, 1));
						ai->statki[sizeS]->taby[number] = stoi(line.substr(2, 1));
						ai->statki[sizeS]->size++;
						number++;
					}
				}
				else {
					if (line != "") {
						sizeS = stoi(line);
						number = 0;
						if (i == 1) {
							allsizep++;
						}
						if (i == 2) {
							allsizea++;
						}
					}
				}
			}
		}
		all_size_player = allsizep;
		all_size_ai = allsizea;
		player->size = all_size_player;
		ai->size = all_size_ai;
	}
	else {
		throw exception("Nie ma pliku z zapisem...\n");
		return false;
	}
	myfile.close();
	return true;
}

RiverManager::~RiverManager() {
	delete ai;
	delete player;
	delete map;
	delete map2;
	delete movement;
	cout << "End Game";
}
