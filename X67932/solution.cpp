#include <iostream>
#include "llista.hpp"

using namespace std;

void Llista::fusiona_suma(Llista &l2, nat n)
{

    node *it = _prim->seg;     // element que apunta el fantasma de p.i.
    node *it2 = l2._prim->seg; // element que apunta el fantasma de l2
    node *pant = nullptr;

    bool entrat = false;

    while (it != _prim && it2 != l2._prim)
    {
        entrat = true;
        for (int i = 0; i < n && it != _prim; i++)
        {
            pant = it;
            it = it->seg;
        }
        for (int i = 0; i < n && it2 != l2._prim; i++)
        {
            if (pant != nullptr)
            {
                pant->seg = it2;
                it2->ant = pant;
                pant = it2;
                it2 = it2->seg;
            }
        }
        if (pant != nullptr)
        {
            pant->seg = it;
            if (it != _prim)
                it->ant = pant;
        }

    }
    while (it2 != l2._prim && entrat)
    {
        if (pant != nullptr)
        {
            pant->seg = it2;
            it2->ant = pant;
            pant = it2;
            it2 = it2->seg;
        }
    }
    while(it != _prim && entrat)
    {
        pant = it;
        it = it->seg;
    }

    if(_prim->seg == _prim){
        _prim = new(node);
        _prim = l2._prim;
    }else if(l2._long > 0){
        pant->seg = _prim;
        _prim->ant = pant;
    }

    int suma = 0;
    it = _prim->seg;
    while(it != _prim){
        suma += it->info;
        pant = it;
        it = it->seg;
    }
    node *p = new(node);
    p->info = suma;
    if(_prim->seg == _prim){
        _prim = new(node);
        _prim->seg = p;
        p->seg = _prim;
        p->ant = _prim;
        _prim->ant = p;
    }else{
        p->seg = _prim->seg;
        _prim->seg->ant = p;
        _prim->seg = p;
        p->ant = _prim;
        pant->seg = _prim;
    }
    _long += l2._long + 1;
    l2._prim = new(node);
    l2._prim->seg = l2._prim;
    l2._prim->seg->ant = l2._prim;
    l2._long = 0;
}

