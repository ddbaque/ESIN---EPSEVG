#include <iostream>
#include "llista.hpp"

using namespace std;

Llista::Llista(const vector<int> &v) :  _long(0) {
    size_t s = v.size();
    node *pant = NULL;
    for(int i = 0; i < s; i++){
        node *p = new(node);
        p->info = v[i];
        p->seg = NULL;
        if(pant == NULL){
            _prim = new(node);
            _prim->seg = p;
        }else{
            pant->seg = p;
        }
        if(i == 0) p->ant = _prim;
        else{
            p->ant = pant;
        }
        pant = p;
        if(i == s-1){
            p->seg = _prim;
            _prim->ant = p;
        }
    }
    _long = s;
    if(s == 0){
        _prim = new(node);
        _prim->seg = _prim;
        _prim->ant = _prim;
        
    }

}