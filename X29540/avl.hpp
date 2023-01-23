#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
typedef unsigned int nat;

template <typename Clau>
class dicc
{
public:
    dicc() : _arrel(NULL){};
    // Pre: Cert
    // Post: El resultat és un dicc sense cap element

    ~dicc();
    // Pre: Cert
    // Post: El dicc ha estat destruït

   pair<Clau, char> insereix(const Clau &k);
   // Pre: Cert
    // Post: La clau k s’ha inserit en el diccionari si no hi era. Retorna la clau dels nodes
    // visitats a on hi ha el desequilibri més proper a les fulles i un caràcter amb el seu
    // tipus de desequilibri: ’E’: Esquerre, ’D’: Dret, ’ ’: No s’ha trobat cap desequilibri

private:
    struct node
    {
        Clau _k;     // Clau
        node *_esq;  // fill esquerre
        node *_dret; // fill dret
        nat _h;      // Altura del subarbre
    };
    node *_arrel;

    static void esborra_nodes(node *m);
    static int altura(node *n);
    static int factor_eq(node *n);
    static node *insereix(node *n, const Clau &k, pair<Clau, char> &p, bool &t);
};

template <typename Clau>
pair<Clau, char> dicc<Clau>::insereix(const Clau &k){
    pair<Clau, char> p;
    p.second = ' ';
    bool t = false;
    _arrel = insereix(_arrel, k, p, t);
    return p;
}

template <typename Clau>
typename dicc<Clau>::node *dicc<Clau>::insereix(node *n, const Clau &k, pair<Clau, char> &p, bool &t){
    if(n == nullptr){
        node *n = new(node);
        n->_k = k;
        n->_h = 1;
        return n;
    }else{
        if(k < n->_k){
            n->_esq = insereix(n->_esq, k, p, t);
        }else if(k > n->_k){
            n->_dret = insereix(n->_dret, k, p, t);
        }
        
        n->_h = 1 + max(altura(n->_esq), altura(n->_dret));
        if(factor_eq(n) > 1 && !t){
            t = true;
            p.first = n->_k;
            if(altura(n->_esq) > altura(n->_dret)) p.second = 'E';
            else p.second = 'D';
        }
        return n;
    }
}

template <typename Clau>
int dicc<Clau>::altura(node *n)
{
    if(n == nullptr) return 0;
    return n->_h;
}

template <typename Clau>
int dicc<Clau>::factor_eq(node *n)
{
    if(n == nullptr) return 0;
    return abs(altura(n->_esq) - altura(n->_dret));
}
