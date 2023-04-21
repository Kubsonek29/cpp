#include <iostream>
#include <string>
#include "complex.h"
using namespace std;

int main() {
    complex<double> w4("1.3-3.4i+4");
    cout << w4;
    complex<int> z;
    //cin>>z;
    cout<<z;
    complex<int> x(5,6);
    complex<int> y(3,-2);
    complex<int> w;
    complex<int> w1;
    complex<int> w2;
    w=x+y;
    cout<<w;
    int a = 3;
    complex<int> w3;
    w3=6+w;
    cout<<w3;
    w3=w*5;
    cout << w3;
    return 0;
}
