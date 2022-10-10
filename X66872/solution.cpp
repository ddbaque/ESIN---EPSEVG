#include <iostream>
#include "llista.hpp"

using namespace std;

void Llista::separa(Llista &l2){
    node *it = _prim;
/*     node *it2 = l2._prim;
 */    node *pant = nullptr;
    node *pant2 = nullptr;
    int i = 1;
    while(it != nullptr){
        if(i % 2 == 0){
            if(pant2 == nullptr){
                l2._prim = it;
            }else{
                pant2->seg = it;
            }
            pant->seg = it->seg;
            pant2 = it;
            l2._long++;
        }
        if(pant == nullptr or i % 2 != 0){
            pant = it;
        }
        it = it->seg;
        i++;
    }
    if(l2._long > 0 && pant2->seg != nullptr){
        pant2->seg = nullptr;
    }
    _long -= l2._long;
}

