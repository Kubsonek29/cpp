#pragma once
#include "MoveObject.h"
#include "Plansza.h"
#include "Pilka.h"
#include "Paletka_AI.h"
#include "Paletka.h"

class Gra{
    MoveObject** t;
    Pilka* bol;
    Paletka* gracz;
    Paletka_AI* AI;
    Plansza* p;

public:
    Gra(int x, int y);
    ~Gra();
    void wyswietl();
    void setObject();
    void clear();
    void move();
    void startgame();
    int checkstatus();
};

