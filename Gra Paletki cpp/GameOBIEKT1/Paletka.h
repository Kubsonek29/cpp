#pragma once
#include "MoveObject.h"
#include "Plansza.h"
class Paletka :public MoveObject{
public:
    Plansza *p;
    char look;
    Paletka(int x, int y, int Vx, int Vy, char look, Plansza& p);
    void move();
    void setObject(char** tab);
};


