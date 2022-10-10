Q#include "llista.hpp"
#include <iostream>

using namespace std;

Llista::Llista(const vector<int> &v) : _prim(NULL), _long(0) {
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
        pant = p;
    }
    _long = s;
    if(s == 0){
        _prim = new(node);
        _prim->seg = NULL;
    }
}
