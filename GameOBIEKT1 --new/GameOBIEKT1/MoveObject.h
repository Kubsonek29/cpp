#pragma once
class MoveObject{
public:
    int x;
    int y;
    int Vx;
    int Vy;
    MoveObject(int x, int y, int Vx, int Vy);
    virtual void move()=0;
};

