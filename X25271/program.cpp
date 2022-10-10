#include <iostream>
#include "arbreBin.hpp"

using namespace std;

/* template <typename T>
int suma_fills(const arbreBin<T> &bt, bool &t){
    if(bt.es_buit()){
        return bt.arrel()b
    }else{
        return bt.arrel();
    }
    if(suma_fills(bt.fd(), t) + suma_fills(bt.fe(), t) != bt.arrel()) t = false;
} */

bool suma(const arbreBin<int> &bt){
    if(bt.es_buit()) return true;
    else 
}

int main(){
    arbreBin<int> bt;
    bool t = true;
    cin >> bt;
    cout << bt;
    /* suma_fills(bt, t);
    if(t) cout << "de locos" << endl;
    else cout << "puto" << endl; */
    if(t)
        cout << "\n" << suma(bt, t) << t << endl;
}
