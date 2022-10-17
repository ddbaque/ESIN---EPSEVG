#include "abin.hpp"
#include <iostream>

using namespace std;

template <typename T>
list<T> Abin<T>::preordre() const
{
    list<T> lst;
    node *paux = _arrel;
    while (paux != nullptr)
    {
        lst.push_back(paux->info);

        if (!paux->thread_esq)
        {
            paux = paux->f_esq;
        }
        else if (!paux->thread_dret)
        {
            paux = paux->f_dret;
        }
        else
        {
            while (paux->thread_dret)
            {
                paux = paux->f_dret;
                if(paux == nullptr) break;
            }
            if(paux != nullptr) paux = paux->f_dret;
        }
    }
    return lst;
}