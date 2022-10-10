#include <iostream>
#include "llista.hpp"

using namespace std;

void Llista::fusiona_suma(Llista &l2, nat n){
    node *pt1 = _prim;
    node *pt2 = l2._prim;
    node *ptseg1 = nullptr;
    int sum = 0;
    cout << "flag 1" << endl;
    while(pt1 != nullptr && pt2 != nullptr){
        for(int i = 0; i < n && pt1 != nullptr; i++){
            sum += pt1->info;
            if(i < n -1) pt1 = pt1->seg;
        }
        ptseg1 = pt1;
            cout << "flag 4" << endl;
        cout << "flag 3" << endl;
        for(int i = 0; i < n && pt2->seg != nullptr; i++){
            sum += pt2->info;
            if(i == 0) pt1->seg = pt2;
            cout << "flag 2" << endl;   
            pt2 = pt2->seg;
        }
        pt1 = pt1->seg;
    pt2->seg = ptseg1;
    }
    //añadir el nodo SUMA
    node *p = new(node);
    p->info = sum;
    if(_prim != nullptr){
        pt1 = _prim;
        _prim = p;
        p->seg = pt1;
    }else{
        _prim = p;
        p->seg = nullptr;
    }
    cout << "explota " << endl;
}