#include <iostream>
#include "testP.h"
#include <string>
using namespace std;



int main(){
    int tab[4]={3,4,5,6};
    string s="5X";
    wielomian<double> w5("100.4+5.3X^4+6.66X^8+34X");
    cout << w5;
    wielomian<double> w4("5X^4+35.5X^3");
    cout << w4;
    wielomian<double> w1 = w4*w5;
    cout << w1;
    wielomian<double> w2 = 5.0*w1;
    cout << w2;
    cout << w2[0];

    //string s="5-15X^8-10X^5+100X";
    //cout << "Podaj polynomial:" << endl;
    //cin >> s;
    //wielomian <int>w1(s);
    //cout<<(int)w1;
    /*
    cout << "Podaj polynomiala2:" << endl;
    cin >> s;
    wielomian w2(s);
    cout<<w2;
    wielomian w3;
    w3=w1+w2;
    cout<<w3;
     */

    /*
    wielomian w1;
    wielomian w2;
    wielomian w3;
    wielomian w4;
    wielomian w5;
    w1.wczytaj();
    //w2.wczytaj();
    //w1.wyswietl();
    //w1[4];
    cout<<w1;
    //cout<<w2;
    //w1==w2;
    if(w1==w2){
        cout<<"sa rowne";
    }
    w3=w1*5;
    cout<<w3;
    cout<<w1;
    w4=5*w1;
    cout<<w4;
    cout<<w1;
    w5=5*w1;
    cout<<w5;
    cout<<w1;


    //w2.wyswietl();
    //w3=w1+w2;
    //w3.wyswietl();
    //w3=w1*w2;
    //w3.wyswietl();
    // 4 3, 6 2
    // 24x^2+26x+6
     */
    return 0;
}













/*
int st;
cout <<"Podaj maksymalny stopien wielomianu (int): \n";
cin >> st;
int wsp[st];
int wsp2[st];
int wsp3[st];
for(int i = 0; i < st+1; i++){
    cout << "Podaj wspolczynnik (int) do 1 wielomianu do x o potedze " << st-i << "\n";
    cin >> wsp[i];
}
for(int j = 0; j < st+1; j++){
    cout << "Podaj wspolczynnik (int) do 2 wielomianu do x o potedze " << st-j << "\n";
    cin >> wsp2[j];
}
wielomian w1(st,wsp);
wielomian w2(st,wsp2);
w1.wyswietl();
w2.wyswietl();
wielomian w3(st,wsp3);
//w3.dodaj(st,wsp,wsp2);
w3.dodaj2(st,w1,w2); ///zrobic to zeby bylo wielomian.dodaj(w1) i zeby mozna bylo dodawac wielomiany o roznych potegach
w3.wyswietl();
*/



/*
template <class T> //typ int albo double do roznych typow
//ze zwracanem T[] sorttab(T t[], int t_size)
T sorttab(T *t, int t_size){
    T tmp;
    T *tab = new T[t_size];
    for(int i = 0; i < t_size;i++){
        for(int j = 0; j < t_size; j++){
            if(t[i]>t[j]){
                tmp=t[i];
                t[i]=t[j];
                t[j]=tmp;
            }
        }
    }
    memcpy(tab,&t,t_size);
    return tab; //srednio dziala
}
*/



/*class point{
public:
    int dlugosc;
    int y;

    int* tmp=NULL;

    point(){}

    point(int d){
        dlugosc = d;
        tmp = new int[dlugosc];
    }

    void wypelnij();
    void wyswietl();
};
void point::wypelnij(){
    for(int i = 0;i<dlugosc;i++){
        tmp[i]=(rand()%10);
    }
}
void point::wyswietl(){
    for(int i = 0; i < dlugosc; i++){
        cout << tmp[i]<< " ";
    }
    cout << endl;
}
int main(){
    srand(time(NULL));
    point *x;
    x = new point[5];
    int tmp;
    for(int i = 0; i < 5; i++){
        x[i]=point(10);
        //x[i].dlugosc = 10;
        //x[i].tmp = new int[10];
        x[i].wypelnij();
        x[i].wyswietl();
    }

    for(int i = 0; i < 5; i++){
        delete []x[i].tmp;
    }
    delete []x;

    //dlugosc.tmp = (int*)malloc(sizeof(int)*10);
    //dlugosc.tmp = new int[10];
    //delete []dlugosc.tmp;

    return 0;
}
*/


