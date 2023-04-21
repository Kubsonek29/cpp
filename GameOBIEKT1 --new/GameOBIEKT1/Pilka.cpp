#include "Pilka.h"

Pilka::Pilka(int x, int y, int Vx, int Vy, char ball, Plansza& p1, Paletka& p2, Paletka_AI& z) :MoveObject(x, y, Vx, Vy) {
    this->ball = ball;
    this->p = &p1;
    this->s = &p2;
    this->z = &z;
}

void Pilka::move() {
    if (p->tab[x - 1][y - 2] == s->look || p->tab[x][y - 2] == s->look || p->tab[x + 1][y - 2] == s->look) {
        Vy = -Vy;
    }
    else if (p->tab[x - 1][y + 2] == z->look || p->tab[x][y + 2] == z->look || p->tab[x + 1][y + 2] == z->look) {
        Vy = -Vy;
    }
    else if (x > 3 && x < p->x - 3 && (p->tab[x + 2][y - 2] == s->look || p->tab[x - 2][y - 2] == s->look || p->tab[x - 2][y + 2] == s->look || p->tab[x + 2][y + 2] == s->look)) {
        Vy = -Vy;
        Vx = -Vx;
    }
    if (p->tab[x][y] == s->look) {
        y = y + 2; //so call me maybe
    }
    if (x <= 1 || x >= p->x - 2) {
        Vx = -Vx;
    }
    x = x + Vx;
    y = y + Vy;

    //////////// AI paletka:
    if (x+1 != 2 && x-1 != p->x - 3) {
        //z->x=x;
        if (p->tab[x][y] == z->look) {
            y = y - 2; 
        }
        if (z->x > x) {
            z->x--;
        }
        else if (z->x < x) {
            z->x++;
        }
    }


}

/*  
* p->tab[x + 2][y - 2] == s->look || p->tab[x - 2][y - 2] == s->look || p->tab[x - 2][y + 2] == s->look || p->tab[x + 2][y + 2] == s->look
    if (x > 3 && x < p->x - 2) {
        if (p->tab[x][y - 2] == s->look || p->tab[x - 1][y - 2] == s->look || p->tab[x - 2][y - 2] == s->look || p->tab[x - 2][y - 1] == s->look || p->tab[x - 2][y] == s->look || p->tab[x - 2][y + 1] == s->look || p->tab[x - 2][y + 2] == s->look || p->tab[x - 1][y + 2] == s->look || p->tab[x][y + 2] == s->look) {
            Vy = -Vy;
        }
        if (p->tab[x][y - 2] == z->look || p->tab[x + 1][y - 2] == z->look || p->tab[x + 2][y - 2] == z->look || p->tab[x + 2][y - 1] == z->look || p->tab[x + 2][y] == z->look || p->tab[x + 2][y + 1] == z->look || p->tab[x + 2][y + 2] == z->look || p->tab[x + 1][y + 2] == z->look || p->tab[x][y + 2] == z->look) {
            Vy = -Vy;
        }
    }
    if (p->tab[x - 1][y + 1] == s->look || p->tab[x - 1][y] == s->look || p->tab[x - 1][y - 2] == s->look || p->tab[x][y - 2] == s->look || p->tab[x + 1][y - 2] == s->look || p->tab[x + 1][y] == s->look || p->tab[x + 1][y + 1] == s->look) {
        Vy = -Vy;
    }
    if (p->tab[x - 1][y + 1] == z->look || p->tab[x - 1][y] == z->look || p->tab[x - 1][y + 2] == z->look || p->tab[x][y + 2] == z->look || p->tab[x + 1][y + 2] == z->look || p->tab[x + 1][y]== z->look || p->tab[x + 1][y - 1] == z->look) {
        Vy = -Vy;
    }
    if (p->tab[x - 2][y + 2] == s->look || p->tab[x - 2][y] == s->look || p->tab[x + 2][y] == s->look || p->tab[x + 2][y + 2] == s->look) {
            Vy = -Vy;
    }
    if (p->tab[x - 2][y + 2] == z->look || p->tab[x - 2][y] == z->look || p->tab[x + 2][y] == z->look || p->tab[x + 2][y - 2] == z->look) {
            Vy = -Vy;
    }
    if (x > 3 && x < p->x - 3 && (p->tab[x+2][y-2]==s->look || p->tab[x-2][y-2] == s->look || p->tab[x-2][y+2] == s->look || p->tab[x+2][y+2] == s->look))
    */