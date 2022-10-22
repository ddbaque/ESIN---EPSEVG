#include <iostream>
#include "llista.hpp"

void Llista::fusiona_suma(Llista &l2, nat n)
{
    node *it = _prim->seg;
    node *it2 = l2._prim->seg;
    node *pant = nullptr;

    while (it2 != nullptr && _prim->seg != nullptr)
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
                pant = it2;
                it2 = it2->seg;
            }
        }
        if (pant != nullptr)
            pant->seg = it;
    }
    if (_prim->seg == nullptr)
    {
        _prim->seg = new(node);
        _prim->seg = l2._prim->seg;
    }
    _long += l2._long + 1;
    l2._prim->seg = nullptr;
    l2._long = 0;

    //* SUMA DELS ELEMENTS DEL PARAMETRE IMPLICIT E INSERCIÓ
    int suma = 0;
    it = this->_prim->seg;
    while (it != nullptr)
    {
        suma += it->info;
        it = it->seg;
    }
    node *p = new (node);
    p->info = suma;
    p->seg = _prim->seg;
    _prim->seg = p;
}