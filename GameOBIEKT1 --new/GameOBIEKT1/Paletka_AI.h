#pragma once
#include "MoveObject.h"
#include "Plansza.h"

class Paletka_AI :public MoveObject{
public:
    //Pilka *fifa;
    Plansza *p;
    char look;
    Paletka_AI(int x, int y, int Vx, int Vy, char look, Plansza& p1/*, Pilka& bal*/);
    void move();
};
