//cost lineal
#include "Arbre.hpp"
template <typename T>
Abin<T>::Abin(nat n){
    int sum = 0;
    _arrel = re_Abin(_arrel, n, sum);
}

//cost lineal
template <typename T>
typename Abin<T>::node* Abin<T>::re_Abin(node *p, nat n, int &sum){
    if(sum >= n){
        return nullptr;
    }
    sum++;
    node *nn = new(node);
    nn->info = sum;
    nn->f_esq = nullptr;
    nn->f_dret = nullptr;
    p = nn;
    p->f_esq = re_Abin(p->f_esq, n, sum);
    p->f_dret = re_Abin(p->f_dret, n, sum);
    sum--;
    return nn;
}
