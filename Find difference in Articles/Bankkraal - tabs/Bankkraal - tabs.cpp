#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
using namespace std;

string readfile(string file) {
    ifstream myfile(file, ios::out);
    string line;
    string output = "";
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            for (int i = 0; i < line.length(); i++) {
                if (line[i] != '\n' && line[i] != ',' && line[i] != '(' && line[i] !=')' && line[i]!='.' && line[i] != '\t' && line[i]!= ';' && line[i]!= ':') {
                    output += line[i];
                }
            }
        }
    }
    return output;
}

map<string,int> countwords(string output) {
    map<string, int> mop;
    map<string, int>::iterator itx;
    string tmp;
    int k = 0;
    int check = 0;
    for (int i = 0; i < output.length(); i++) {
        if (output[i]!=' ' && check==0) {
            k = i;
            check = 1;
        }
        else if (output[i] == ' ') {
            if (mop.count(output.substr(k, i - k))==0) {
                mop.insert(make_pair(output.substr(k, i - k), 1));
            }
            else {
                mop.find(output.substr(k, i - k))->second++;
            }
            check = 0;
        }
    }
    return mop;
}

map<string,int> comparediff(map<string,int> mop1, map<string,int> mop2) {
    map<string, int> bigmop;
    map<string, int>::iterator itx( bigmop.begin() );
    set_difference(mop1.begin(), mop1.end(), mop2.begin(), mop2.end(), inserter(bigmop, itx), bigmop.value_comp());
    return bigmop;
}

void bigNuts(map<string, int> bigmop1, string tytul1, map<string, int> bigmop2, string tytul2, map<string, int> bigmop3, string tytul3) {
    map<string, int>::iterator itx;
    cout << "Difference in words between " << tytul1 << endl;
    for (itx = bigmop1.begin(); itx != bigmop1.end(); itx++) {
        cout << itx->first << " ==> " << itx->second << endl;
    }
    cout << endl;
    cout << "Difference in words between " << tytul2 << endl;
    for (itx = bigmop2.begin(); itx != bigmop2.end(); itx++) {
        cout << itx->first << " ==> " << itx->second << endl;
    }
    cout << endl;
    cout << "Difference in words between " << tytul3 << endl;
    for (itx = bigmop3.begin(); itx != bigmop3.end(); itx++) {
        cout << itx->first << " ==> " << itx->second << endl;
    }
}

int main()
{  
    bigNuts(comparediff(countwords(readfile("file2.txt")), countwords(readfile("filebrain.txt"))), "file2 - filebrain", comparediff(countwords(readfile("file2.txt")), countwords(readfile("fil3.txt"))), "file2 - fil3", comparediff(countwords(readfile("filebrain.txt")), countwords(readfile("fil3.txt"))), "filebrain - fil3");
}









/*
int tab1[7] = { 8,4,3,10,15,2,1 };
    int tab2[8] = { 3,10,2,8,9,13,20,50 };
    int biggersize = 8;
    /*
    map<int, int> m;
    map<int, int>::iterator it;
    for (int i = 0; i < biggersize; i++) {
        m.insert(make_pair(tab2[i], 0));
    }
    for (auto n : tab2) {
        ///
    }


set<int> x(tab1, tab2);
set<int> y(7, 8);
//set<int, greater<int>> inter;
vector<int> vec;
vector<int>::iterator itx;
set_intersection(x.begin(), x.end(), y.begin(), y.end(), inserter(vec, vec.begin()));
//set_difference 3 artykuly parami sprawdzic jakie wyrazy sie roznia;
for (itx = vec.begin(); itx != vec.end(); itx++) {
    cout << *itx << endl;
}

/*
const int size = 7;
int tab1[size] = { 8,4,3,10,15,2,1 };
int tab2[size] = { 3,10,2,8,9,13,20 };
int holdtab[size];

list<int> holder;
list<int>::iterator it;
for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
        if (tab1[i] == tab2[j]) {
            holder.push_back(tab1[i]);
        }
    }
}
for (it = holder.begin(); it != holder.end(); it++) {
    cout << *it << endl;
}

cout << endl;

int k = 0;
for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
        if (tab1[i] == tab2[j]) {
            holdtab[k] = tab1[i];
            k++;
        }
    }
}
for (int i = 0; i < k; i++) {
    cout << holdtab[i] << endl;
}
cout << "Hello World!\n";
*/