#include <iostream>
#include "Gra.h"
#include "MoveObject.h"
#include "Pilka.h"
#include "Paletka.h"
#include "Paletka_AI.h"
#include "Plansza.h"
using namespace std;

Gra::Gra(int x, int y){
    p = new Plansza(x,y);
    p->x=x;
    p->y=y;
    for(int i = 0; i < y; i++){
        p->tab[0][i]='X';
        p->tab[x-1][i]='X';
    }
    t = new MoveObject*[3];
    gracz = new Paletka(x/2,2,1,1,'>',*p);
    AI = new Paletka_AI(x / 2, y - 3, 1, 1, '<', *p/*, *bol*/);
    bol = new Pilka(x/2, y/2, 2, 2, '+', *p, *gracz, *AI);
    t[0] = bol;
    t[1] = gracz;
    t[2] = AI;
}

void Gra::setObject(){
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            p->tab[bol->x + i][bol->y + j] = bol->ball;
        }
    }

    for (int i = -2; i <= 2; i++) {
        for (int j = -1; j <= 1; j++) {
            p->tab[gracz->x+i][gracz->y+j] = gracz->look;

        }
    }

    for (int i = -2; i <= 2; i++) {
        for (int j = -1; j <= 1; j++) {
            p->tab[AI->x+i][AI->y+j] = AI->look;
        }
    }
}

void Gra::wyswietl(){
    for(int i = 0; i < p->x; i++){
        for(int j = 0; j < p->y; j++){
            cout << p->tab[i][j];
        }
        cout << endl;
    }

}

void Gra::clear(){
    for(int i = 0; i < p->x; i++){
        for(int j = 0; j < p->y; j++){
            p->tab[i][j]='.';
        }
    }
}

void Gra::move(){
    for(int i = 0; i < 3; i++){
        t[i]->move();
    }
}

int Gra::checkstatus(){
    if (bol->y <= 0 || bol->y >= p->y) {
        bol->x = p->x / 2;
        bol->y = p->y / 2;
        bol->Vx = 2;
        bol->Vy = 2;
        return 0;
    }
    else {
        return 1;
    }
}

void Gra::startgame() {
    cout << "Hello in our funny game!" << endl;
    cout << "How should the player look like (char)?: " << endl;
    cin >> gracz->look;
    cout << "How should the AI look like(char)?: " << endl;
    cin >> AI->look;
}

Gra::~Gra(){
    //cout << "helo" << endl;
    //delete bol;
    //delete gracz;
    //delete AI;
    //delete p;
}
