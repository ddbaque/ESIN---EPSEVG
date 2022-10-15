#include "abin.hpp"
#include <iostream>

using namespace std; 

template <typename T> 
list<T> Abin<T>::preordre() const{
    list<T> l;
    node *p =_arrel;
    if(_arrel != nullptr) l.push_back(p->info);
    while(p != _pri_inordre){
        p = p->f_esq;
        l.push_back(p->info);
    }

    while()
    
    cout << "salgo" << endl;
    return l;
}