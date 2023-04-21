#include "Gra.h"
#include "windows.h"
#include <iostream>

using namespace std;

int main() {
    Gra w1(19, 80);
    cout << "\nPress A or D to move" << endl;
    w1.startgame();
    int yes = 1;
    int j = 0;
    while (yes) {
        while (w1.checkstatus()) {
            w1.clear();
            w1.setObject();
            w1.move();
            w1.wyswietl(); 
            Sleep(60);
            system("CLS");
        }
        system("CLS");
        if (j == 0) {
            cout << "\nPress Escape to Exit" << endl;
            cout << "Press Enter to play the game again!" << endl;
            j = 1;
        }
        while (!(GetKeyState(VK_RETURN) & 0x8000)) {
            if ((GetKeyState(VK_ESCAPE) & 0x8000)) {
                yes = 0;
                j = 0;
                break;
            }
            else {
                j = 0;
            }
        }
    }
    system("cls");
    cout << "Koniec";
    return 0;
}
