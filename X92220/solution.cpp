#include <iostream>
#include "llista.hpp"

void Llista::fusiona_suma(Llista &l2, nat n)
{
    node *it = _prim->seg;
    node *it2 = l2._prim->seg;
    node *pant = nullptr;

    bool t = false;

    while (it2 != l2._prim && it != _prim)
    {
        t = true;
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
                pant = it2;
                it2 = it2->seg;
            }
        }
        if (pant != nullptr)
            pant->seg = it;
    }
    while(it2 != l2._prim && t){
        pant->seg = it2;
        pant = it2;
        it2 = it2->seg;
    }
    while(it != _prim && t){
        pant = it; 
        it = it->seg;
    }
    if (_prim->seg == _prim)
    {
        _prim = new(node);
        _prim = l2._prim;
        
    }else if(l2._long != 0){
        pant->seg = _prim;
    }

    //* SUMA DELS ELEMENTS DEL PARAMETRE IMPLICIT E INSERCIÓ
    int suma = 0;
    it = _prim->seg;
    while (it != _prim)
    {
        suma += it->info;
        pant = it;
        it = it->seg;
    }
    node *p = new (node);
    p->info = suma;
    if(_prim->seg == _prim){
        _prim = new(node);
        _prim->seg = p;
        p->seg = _prim;
    }else{
        p->seg = _prim->seg;
        _prim->seg = p;

        pant->seg = _prim;
    }

    _long += l2._long + 1;
    l2._prim = new(node);
    l2._prim->seg = l2._prim;
    l2._long = 0;
} 