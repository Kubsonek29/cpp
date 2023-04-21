#include "windows.h"
#include "Paletka.h"

Paletka::Paletka(int x, int y, int Vx, int Vy, char look, Plansza& p1) :MoveObject(x, y, Vx, Vy){
    this->look=look;
    this->p=&p1;
}

void Paletka::move(){
    if( GetKeyState('W') & 0x8000 ){
        if (x != 2) {
            x = x - Vx;
        }
    }
    if( GetKeyState('S') & 0x8000 ){
        if(x != p->x-3){
            x = x + Vx;
        }
    }
}

