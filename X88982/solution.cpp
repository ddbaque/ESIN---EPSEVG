#include <iostream>
#include "llista.hpp"

using namespace std;

void Llista::fusiona_suma(Llista &l2, nat n) {
    node* pNode1 = _prim;
    node* pNode2 = l2._prim;
    int counter = n - 1;
    bool addToFirst = true;

    while (l2._long != 0 || (l2._long == 0 && (pNode1 != NULL && pNode1->seg != NULL))) {
        if (counter <= 0) {
            addToFirst = !addToFirst;
            counter = n;
        }
        --counter;



        if (pNode1 == NULL) { // Crea el primer elemento si la primera lista esta vacia
            _prim = new node;
            pNode1 = _prim;
            pNode1->info = pNode2->info;
            pNode1->seg = NULL;
            ++_long;

            node* pAux = pNode2;
            pNode2 = pNode2->seg;
            delete pAux;
            --l2._long;
            if (pNode2 == NULL) l2._prim = NULL;
            else l2._prim = pNode2;
        }
        else if (pNode1->seg == NULL) { // Crea el siguiente elemento ya no hace falta el contador porque la primera lista esta vacia
            pNode1->seg = new node;
            pNode1->seg->info = pNode2->info;
            pNode1->seg->seg = NULL;
            pNode1 = pNode1->seg;
            ++_long;

            node* pAux = pNode2;
            pNode2 = pNode2->seg;
            delete pAux;
            --l2._long;
            if (pNode2 == NULL) l2._prim = NULL;
            else l2._prim = pNode2;
        }

        else if (addToFirst || l2._long == 0) { // Pasa al siguiente e incrementa suma
            pNode1 = pNode1->seg;
        }
        else if (!addToFirst) { // Añade elementos a la primera lista pero ninguna de las dos esta vacia
            node* pNext = pNode1->seg;
            pNode1->seg = new node;
            pNode1->seg->info = pNode2->info;
            pNode1->seg->seg = pNext;
            pNode1 = pNode1->seg;
            ++_long;

            node* pAux = pNode2;
            pNode2 = pNode2->seg;
            delete pAux;
            --l2._long;
            if (pNode2 == NULL) l2._prim = NULL;
            else l2._prim = pNode2;
        }
    }



    int sum = 0;
    node* pNode = _prim;
    while (pNode != NULL) {
        sum += pNode->info;
        pNode = pNode->seg;
    }



    node* pAux = _prim;
    _prim = new node;
    _prim->seg = pAux;
    _prim->info = sum;
    _long += 1;
}