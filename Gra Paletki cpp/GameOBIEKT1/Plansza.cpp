#include "Plansza.h"
#include <iostream>
using namespace std;

Plansza::Plansza(int x, int y){
    tab=(char**)malloc(x*sizeof(char*));
    for(int i = 0; i < x; i++){
        tab[i]=(char*)malloc(y*sizeof(char));
    }
    for(int i = 0 ; i < x; i++){
        for(int j = 0 ; j < y; j++){
            tab[i][j]='.';
        }
    }
}



