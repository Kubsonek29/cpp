#pragma once
#include "MoveObject.h"
#include "Plansza.h"
#include "Paletka.h"
#include "Paletka_AI.h"

class Pilka :public MoveObject{
public:
    Paletka *s;
    Paletka_AI *z;
    Plansza *p;
    char ball;
    Pilka(int x, int y, int Vx, int Vy, char ball, Plansza& p1, Paletka& p2, Paletka_AI& z);
    void move();
};
