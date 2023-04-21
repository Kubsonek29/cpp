// pch.h: wstępnie skompilowany plik nagłówka.
// Wymienione poniżej pliki są kompilowane tylko raz, co poprawia wydajność kompilacji dla przyszłych kompilacji.
// Ma to także wpływ na wydajność funkcji IntelliSense, w tym uzupełnianie kodu i wiele funkcji przeglądania kodu.
// Jednak WSZYSTKIE wymienione tutaj pliki będą ponownie kompilowane, jeśli którykolwiek z nich zostanie zaktualizowany między kompilacjami.
// Nie dodawaj tutaj plików, które będziesz często aktualizować (obniża to korzystny wpływ na wydajność).

#ifndef PCH_H
#define PCH_H

// w tym miejscu dodaj nagłówki, które mają być wstępnie kompilowane

#endif //PCH_H

#include <iostream>
#include <string>
using namespace std;

template <class C>
class complex {
    C re;
    C im;
public:
    complex();
    complex(C re, C im);
    complex(const complex& c);
    complex(string s);
    complex& operator = (const complex<C>& c);
    complex operator + (const complex<C>& c);
    complex operator * (const complex<C>& c);
    complex operator - (const complex<C>& c);
    complex operator / (const complex<C>& c);
    complex operator += (const complex<C>& c);
    complex operator -= (const complex<C>& c);
    complex operator *= (const complex<C>& c);
    complex operator /= (const complex<C>& c);
    template <class B> friend ostream& operator << (ostream& o, complex<B> const& w);
    template <class B> friend istream& operator >> (istream& o, complex<B> const& w);
    bool operator == (complex<C>& c);
    bool operator != (complex<C>& c);
    template <class B> friend complex<B> operator + (B number, complex<B>& w);
    template <class B> friend complex<B> operator - (B number, complex<B>& w);
    template <class B> friend complex<B> operator * (B number, complex<B>& w);
    complex operator + (C number);
    complex operator - (C number);
    complex operator * (C number);
    C get_re();
    C get_im();
    ~complex();
};

template <class C>
complex<C>::complex() {
    re = 0;
    im = 0;
}

template <class C>
C complex<C>::get_re() {
    return re;
}

template <class C>
C complex<C>::get_im() {
    return im;
}

template <class C>
complex<C>::complex(C re, C im) {
    this->re = re;
    this->im = im;
}

template <class C>
complex<C>::complex(const complex& c) {
    re = c.re;
    im = c.im;
}
template <class C>
complex<C>::complex(string s) {
    this->re = 0;
    this->im = 0;
    C wpis;
    C tempim = 0;
    C tempre = 0;
    if (s[0] != '-') {
        s = '+' + s;
    }
    s += '+';
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == 'i') {
            if (s[i - 1] == '+' || s[i - 1] == '-' || s[0] == 'i') {
                s.insert(i, "1");
            }
        }
    }
    string tmp = s;
    string tmp2 = s;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '+' || s[i] == '-') {
            if (i == 0) {
                tmp = tmp.substr(i);
            }
            else {
                tmp = s.substr(i);
            }
            if (tmp == "+" || tmp.empty()) {
                break;
            }
            tmp2 = tmp.substr(1);
            size_t found2 = tmp2.find_first_of("+-");
            tmp = tmp.substr(0, found2 + 1);
            if (tmp.find('i') != string::npos) {
                wpis = stold(tmp);
                tempim += wpis;
            }
            else {
                wpis = stold(tmp);
                tempre += wpis;
            }
            tmp = tmp2;
        }
    }
    re = tempre;
    im = tempim;
}

template <class C>
complex<C>& complex<C>::operator = (const complex& c) {
    re = c.re;
    im = c.im;
    return *this;
}

template <class C>
complex<C> complex<C>::operator + (const complex& c) {
    complex<C> tmp;
    tmp.re = re + c.re;
    tmp.im = im + c.im;
    return tmp;
}

template <class C>
complex<C> complex<C>::operator - (const complex& c) {
    complex<C> tmp;
    tmp.re = re - c.re;
    tmp.im = im - c.im;
    return tmp;
}

template <class C>
complex<C> complex<C>::operator * (const complex& c) {
    complex<C> tmp;
    tmp.re = re * c.re - im * c.im;
    tmp.im = re * c.im + im * c.re;
    return tmp;
}

template <class C>
complex<C> complex<C>::operator / (const complex& c) {
    complex<C> tmp;
    tmp.re = (re * c.re + im * c.im) / (c.re * c.re + c.im * c.im);
    tmp.im = (im * c.re - re * c.im) / (c.re * c.re + c.im * c.im);
    return tmp;
}

template <class C>
complex<C> complex<C>::operator += (const complex& c) {
    re += c.re;
    im += c.im;
    return *this;
}

template <class C>
complex<C> complex<C>::operator -= (const complex& c) {
    re -= c.re;
    im -= c.im;
    return *this;
}

template <class C>
complex<C> complex<C>::operator *= (const complex& c) {
    C tmp;
    tmp = re * c.re - im * c.im;
    im = re * c.im + im * c.re;
    re = tmp;
    return *this;
}

template <class C>
complex<C> complex<C>::operator /= (const complex& c) {
    C tmp;
    tmp = (re * c.re + im * c.im) / (c.re * c.re + c.im * c.im);
    im = (im * c.re - re * c.im) / (c.re * c.re + c.im * c.im);
    re = tmp;
    return *this;
}

template <class C>
ostream& operator << (ostream& o, complex<C> const& c) {
    if (c.re)
        o << c.re;
    if (c.im) {
        if (c.im > 0) {
            o << "+";
        }
        o << c.im << "i" << endl;
    }
    if (!c.re && !c.im)
        cout << "0" << endl;
    return o;
}

template <class C>
istream& operator >> (istream& o, complex<C>& c) {
    string s;
    o >> s;
    complex<C> w1(s);
    c = w1;
    return o;
}

template <class C>
bool complex<C>::operator == (complex<C>& c) {
    if (im != c.im)
        return false;
    else if (re != c.re)
        return false;
    else
        return true;
}

template <class C>
bool complex<C>::operator != (complex<C>& c) {
    if (im != c.im)
        return true;
    else if (re != c.re)
        return true;
    else
        return false;
}

template <class C>
complex<C> operator + (C number, complex<C>& c) {
    complex<C> abc;
    abc.re = number + c.re;
    abc.im = c.im;
    return abc;
}

template <class C>
complex<C> operator - (C number, complex<C>& c) {
    complex<C> abc;
    abc.re = c.re - number;
    abc.im = c.im;
    return abc;
}

template <class C>
complex<C> operator * (C number, complex<C>& c) {
    complex<C> abc;
    abc.re = c.re * number;
    abc.im = c.im * number;
    return abc;
}

template <class C>
complex<C> complex<C>::operator + (C number) {
    complex<C> abc;
    abc.re = re + number;
    abc.im = im;
    return abc;
}

template <class C>
complex<C> complex<C>::operator - (C number) {
    complex<C> abc;
    abc.re = re - number;
    abc.im = im;
    return abc;
}

template <class C>
complex<C> complex<C>::operator * (C number) {
    complex<C> abc;
    abc.re = re * number;
    abc.im = im * number;
    return abc;
}

template <class C>
complex<C>::~complex() {}

