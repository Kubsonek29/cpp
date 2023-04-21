#include <iostream>
#include <string>
using namespace std;
template <class T>
class wielomian{
    int st;
    T* wsp;
public:
    wielomian();
    wielomian(const wielomian &x);
    wielomian(string s);
    wielomian(int st, T* wsp);
    ~wielomian();
    T get_st();
    T* get_wsp();
    wielomian& operator = (const wielomian<T> &w);
    wielomian operator + (const wielomian<T> &w) const;
    wielomian operator * (wielomian<T> &w);
    T operator [] (int w);
    bool operator == (wielomian<T> &w);
    wielomian operator * (T w);
    template <class B> friend wielomian<B> operator * (B size, wielomian<B> &w); //lub zmienic tu na inta zalezy...
    template <class B> friend ostream& operator << (ostream &o, wielomian<B> const &w);
};

template <class T>
T wielomian<T>::get_st() {
    return st;
}

template <class T>
T* wielomian<T>::get_wsp() {
    return wsp;
}

template <class T>
wielomian<T>::wielomian(){
    st = 0;
    wsp = new T[1];
    *wsp=0;
}

template <class T>
wielomian<T>::wielomian(const wielomian<T> &w){
    st=w.st;
    wsp=new T[st+1];
    for(int i=0; i<=st; i++)
        wsp[i]=w.wsp[i];
}

template <class T>
wielomian<T>::wielomian(int st, T* wsp) {
    this->st = st;
    this->wsp = new T[st + 1];
    for(int i = 0; i <= st; i++){
        *(this->wsp+i) = *(wsp+i);
    }
}

template <class T>
wielomian<T>::wielomian(string strtab){
    string tmp2=strtab;
    string tmp3;
    cout << "Napis:" << strtab << endl;
    int savelength=strtab.length();
    int tmpst[strtab.length()];
    T tmpwsp[strtab.length()];
    for(int i = 0; i < strtab.length();i++){
        tmpst[i]=0;
        tmpwsp[i]=0;
    }
    int ctr=0;
    int ctr2=0;
    int catst=0;
    int catwsp=0;
    string ending;
    ending=strtab.substr(strtab.length()-1,strtab.length());


    //obróbka danych
    if(strtab[0]=='X'){
        strtab = '1' + strtab;
    }
    if(strtab[0]!='-'){
        strtab = '+' + strtab;
    }
    strtab+='+';
    for(int i = 0; i < strtab.length();i++){
        if(strtab[i]=='+' || strtab[i]=='-'){
            if(strtab[i+1]=='X'){
                strtab.insert(i+1,"1");
            }
            else{
                tmp3 = strtab.substr(i+1,strtab.length());
                size_t found = tmp3.find_first_of("+-");
                tmp3 = tmp3.substr(0,found);
                if(tmp3.find('X') == string::npos && tmp3!=""){
                    strtab.insert(i+found+1,"X^0");
                }
            }
        }
    }
    strtab=strtab.substr(0,strtab.length()-1);

    for(int i = 0; i < strtab.length(); i++){
        if(strtab[i]=='X'){
            if(ctr2==0){
                tmp2 = strtab.substr(0,i);
                ctr2 = tmp2.length()+1;
            }
            else{
                tmp2=tmp2.substr(0,strtab.length());
            }
            tmpwsp[ctr]=stold(tmp2);
            catwsp++;
            if(strtab[i+1]=='^'){
                tmp2 = strtab.substr(i+2,strtab.length());
                size_t found = tmp2.find_first_of("+-");
                ctr2 = found;
                tmp3=tmp2;
                tmp2 = strtab.substr(i+2,found);
                tmpst[ctr]=stold(tmp2);
                if(tmp2.size()==tmp3.size()){
                    break;
                }
                else{
                    tmp2 = tmp3.substr(found,strtab.length());
                }
            }
            else{
                tmp2 = strtab.substr(i+1,strtab.length());
                tmp3 = tmp2;
                ctr2+=i;
                tmpst[ctr]=1;
            }
            catst++;
            ctr++;
        }
    }

    int size=0;
    for(int i = 0; i <= catst;i++){
        if(tmpst[i]>size){
            size=tmpst[i];
        }
    }

    this->wsp = new T[size+1];
    this->st = size;

    for(int i = 0; i<=st; i++){
        wsp[i]=0;
    }

    for(int i = 0; i < savelength; i++){
        wsp[st-tmpst[i]]+=tmpwsp[i];
    }
    for(int i = 0; i <=st; i++){
        cout << wsp[i] << endl;
    }
}

template <class T>
wielomian<T>& wielomian<T>::operator = (const wielomian &x){
    delete[] wsp;
    st=x.st;
    wsp= new T[x.st+1];
    memcpy(wsp,x.wsp,(st+1)*sizeof(T));
    return *this;
}

template <class T>
wielomian<T> wielomian<T>::operator + (const wielomian &x) const{
    wielomian abc;
    int tmp;
    if(x.st > st){
        abc.st = x.st;
        tmp = x.st-st;
    }
    else{
        abc.st = st;
        tmp = st-x.st;
    }
    abc.wsp = new T[abc.st+1];
    for(int i = 0; i <= abc.st; i++){
        abc.wsp[i]=0;
    }
    if(x.st > st){
        for(int i = 0; i < tmp; i++){
            abc.wsp[i]=x.wsp[i];
        }
        for (int i = tmp; i <= abc.st; i++) {
            abc.wsp[i] = x.wsp[i] + wsp[i-tmp];
        }
    }
    else if(x.st < st){
        for (int i = 0; i < tmp; i++) {
            abc.wsp[i] = wsp[i];
        }
        for (int i = tmp; i <= abc.st; i++) {
            abc.wsp[i] = x.wsp[i-tmp] + wsp[i];
        }
    }
    else{
        for(int i = 0; i <= abc.st; i++){
            abc.wsp[i]=x.wsp[i]+wsp[i];
        }
    }
    return abc;
}

template <class T>
wielomian<T> wielomian<T>::operator * (wielomian<T> &x) {
    wielomian abc;
    abc.st = x.st + st;
    abc.wsp = new T[abc.st+1];
    for(int i = 0; i <= abc.st; i++){
        abc.wsp[i]=0;
    }
    for (int i = 0; i <= st; i++) {
        for (int j = 0; j <= x.st; j++) {
            abc.wsp[i + j] += wsp[i] * x.wsp[j];
        }
    }
    return abc;
}

template <class T>
T wielomian<T>::operator [] (int w){
    return wsp[w];
}

template <class T>
ostream& operator << (ostream &o, wielomian<T> const& w){
    for(int i = 0; i < w.st+1; i++){
        if(w.wsp[i]>0 && i!=0){
            o <<"+";
        }
        if(w.wsp[i]!=0){
            if(i==w.st){
                o << w.wsp[i];
            }
            else if(i==w.st-1){
                if(w.wsp[i]==1){
                    o << "X";
                }
                else if(w.wsp[i]==-1) {
                    o << "-X";
                }
                else{
                    o << w.wsp[i] << "X";
                }
            }
            else if(w.wsp[i]==1){
                o<< "X^" << w.st-i;
            }
            else{
                o << w.wsp[i] << "X^"<< w.st-i;
            }
        }
    }
    o << "=0" << endl;
    return o;
}

template <class T>
wielomian<T> wielomian<T>::operator * (T w){
    wielomian abc;
    abc.st = st;
    abc.wsp = new T[abc.st+1];
    for(int i = 0; i < st+1; i++){
        abc.wsp[i]=wsp[i]*w;
    }
    return abc;
}

template <class T>
wielomian<T> operator * (T size, wielomian<T> &w){
    wielomian<T> abc;
    abc.st = w.st;
    abc.wsp = new T[abc.st+1];
    for(int i = 0; i < w.st+1; i++){
        abc.wsp[i]=w.wsp[i]*size;
    }
    return abc;
}

template <class T>
bool wielomian<T>::operator == (wielomian<T> &w){
    if(st!=w.st){
        return false;
    }
    for(int i = 0; i < st; i++) {
        if (wsp[i] != w.wsp[i]) {
            return false;
        }
    }
    return true;
}

template <class T>
wielomian<T>::~wielomian(){
    delete[] wsp;
}
