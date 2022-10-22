#include <iostream>
#include "llista.hpp"

using namespace std;

void Llista::fusiona_suma(Llista &l2, nat n)
{

    node *it = _prim;
    node *it2 = l2._prim;
    node *pant = nullptr;
    /*     cout << "_long -> " << _long << " l2._long -> " << l2._long << endl;
     */
    while (it2 != nullptr && _prim != nullptr)
    {
        for (int i = 0; i < n && it != nullptr; i++)
        {
            pant = it;
            it = it->seg;
        }

        for (int i = 0; i < n && it2 != nullptr; i++)
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
            if (it != nullptr)
                it->ant = pant;
        }
    }
    if (_prim == nullptr)
    {
        _prim = new (node);
        _prim = l2._prim;
        _ult = new (node);
        _ult = l2._ult;
    }
    _long += l2._long + 1;
    l2._long = 0;
    l2._prim = nullptr;
    l2._ult = nullptr;

    //* SUMA DELS ELEMENTS DEL PARAMETRE IMPLICIT E INSERCIÓ
    int suma = 0;
    it = this->_prim;
    while (it != nullptr)
    {
        suma += it->info;
        pant = it;
        it = it->seg;
    }
    node *p = new (node);
    p->info = suma;

    p->seg = _prim;
    if(_prim != nullptr) _prim->ant = p;
    p->ant = nullptr;
    _prim = p;
    if(_ult == nullptr){
        _ult = p;
    }else _ult = pant;


    /* if (_long > 0)
    {
        p->seg = _prim;
        _prim->ant = p;
        p->ant = nullptr;
        _prim = p;
        _ult = pant;
    }
    else
    {
        p->seg = nullptr;
        _prim = new (node);
        _prim = p;
        p->ant = nullptr;
        _ult = new (node);
        _ult = p;
    } */
}
