#include "Paletka_AI.h"

Paletka_AI::Paletka_AI(int x, int y, int Vx, int Vy, char look, Plansza& p1/*, Pilka& bal*/) :MoveObject(x, y, Vx, Vy) {
    this->look=look;
    this->p = &p1;
    //this->fifa = &bal;
}
void Paletka_AI::move(){
    /*if (x != 2 && x != p->x - 3) {
        x = fifa->x;
        y = fifa->y;
    }*/
}
