#pragma once
#include "LeShips.h"
#include "AI.h"
#include "Map.h"
#include "Player.h"
#include "ShipsMove.h"

class RiverManager
{
	AI* ai;
	Player* player;
	Map* map;
	Map* map2;
	ShipsMove* movement;

	int all_size_player;
	int all_size_ai;
	char shiplook;
	bool status = true;
	int printer;
public:
	RiverManager(int x, int y);
	bool loadpreset();
	int beginningpack();
	void showmenu();
	int menutool();
	void setshipsontheriver();
	void setYahrrontheriver();
	void printgame();
	void printgameai();
	void clear();
	void clearai();
	void starterpackplayer();
	void starterpackai();
	void starterpackloaded();
	bool checkstatus();
	bool checkstatusP();
	void changestatusfalse();
	void SaveTheGameToFile();
	bool ReadTheGameFromFile();
	virtual void move();
	~RiverManager();
};

