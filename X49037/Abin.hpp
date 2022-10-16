#include <iostream>
#include <cstdlib>
using namespace std;
typedef unsigned int nat;

template <typename T>
class Abin
{
public:
    Abin() : _arrel(NULL){};
    // Pre: cert
    // Post: el resultat és un arbre sense cap element
    Abin(Abin<T> &ae, const T &x, Abin<T> &ad);
    // Pre: cert
    // Post: el resultat és un arbre amb un element i dos subarbres

    // Les tres grans
    Abin(const Abin<T> &a);
    ~Abin();
    Abin<T> &operator=(const Abin<T> &a);

    // Escriu una línia amb els elements del nivell i-èssim, d’esquerra
    // a dreta. Cada element ha de sortir precedit d’un espai.
    void nivell(nat i) const;

private:
    struct node
    {
        node *f_esq;
        node *f_dret;
        T info;
    };
    node *_arrel;
    static node *copia_nodes(node *m);
    static void esborra_nodes(node *m);
    static void re_nivell(node *n, nat i);

    // Aquí va l’especificació dels mètodes privats addicionals
};

// Aquí va la implementació del mètode nivell

template <typename T>
void Abin<T>::nivell(nat i) const{
    nat j = i;
    re_nivell(_arrel, j);
}

template <typename T>
void Abin<T>::re_nivell(node *n, nat i){
    if(i == 0 or n == nullptr){
            if(n != nullptr) cout << " " << n->info;
            return;
        }
        --i;
        re_nivell(n->f_esq, i);
        re_nivell(n->f_dret, i);
}