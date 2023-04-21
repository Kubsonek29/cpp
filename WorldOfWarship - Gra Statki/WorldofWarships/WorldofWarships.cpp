#include <iostream>
#include "windows.h"
#include "RiverManager.h"
using namespace std;

int main()
{
	int gamer = 1;
	RiverManager Game(10, 10);
	int timer = 1;
	int choice=0;
	while (timer) {
		try {
			choice = Game.beginningpack();
		}
		catch (invalid_argument z) {
			cout << z.what() << endl << endl;
			Sleep(500);
		}
		if (choice == 3) {
			bool loader=false;
			try {
				loader = Game.loadpreset();
			}
			catch (exception z) {
				cout << z.what() << endl << endl;
				Sleep(1000);
			}
			if (loader == true) {
				timer = 0;
			}
		}
		if (choice == 2) {
			bool reader = false;
			try {
				reader = Game.ReadTheGameFromFile();
			}
			catch (exception z) {
				cout << z.what() << endl << endl;
			}
			if (reader == true) {
				timer = 0;
			}
		}
		if (choice == 1) {
			timer = 0;
		}
	}
	if (choice == 1) {
		timer = 1;
		while (timer) {
			try {
				Game.starterpackplayer();
			}
			catch (exception z) {
				cout << z.what() << endl << endl;
				Sleep(1000);
			}
			if (Game.checkstatusP()) {
				timer = 0;
			}
		}
		Game.starterpackai();
	}
	else if (choice == 2) {
		Game.setshipsontheriver();
		Game.setYahrrontheriver();
	}
	else if (choice == 3) {
		Game.starterpackloaded();
		Game.starterpackai();
	}
	while (gamer) {
		do {
			Game.printgame();
			//Game.printgameai(); see AI ships
			Game.clearai();
			Game.printgameai();
			Game.setYahrrontheriver();
			cout << "Press ESC to get to the menu after the round ends..." << endl << endl;
			try {
				Game.move();
			}
			catch (exception z) {
				cout << z.what() << endl << endl;
				Sleep(1000);
			}
		} while (Game.checkstatus() && GetAsyncKeyState(VK_ESCAPE) == 0);
		if (!Game.checkstatus()) {
			gamer = 0;
			break;
		}
		if (GetAsyncKeyState(VK_ESCAPE) == 0) {
			timer = 1;
			choice = 0;
			while (timer) {
				try {
					choice = Game.menutool();
				}
				catch (invalid_argument z) {
					cout << z.what() << endl << endl;
					Sleep(600);
				}
				if (choice == 1 || choice == 2 || choice == 3 || choice == 4) {
					timer = 0;
				}
				if (choice == 2 || choice == 3) {
					gamer = 0;
				}
			}
		}
	}
	std::cout << "Ending screen below: " << std::endl;
	Game.printgame();
	Game.printgameai();
	Sleep(3000);
	return 0;
}
