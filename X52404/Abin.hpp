#include <cstdlib>
#include <iostream>
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

    // operador << d’escriptura
    template <class U>
    friend std::ostream &operator<<(std::ostream &, const Abin<U> &a);

    // operador >> de lectura
    template <class U>
    friend std::istream &operator>>(std::istream &, Abin<U> &a);

    // Modifica el contingut de l’arbre per tal de guardar a cada node la suma dels
    // nodes del seu subarbre.
    void arbre_sumes();

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
    static void print_nodes(node *m, ostream &os, string d1);
    void re_arbre_sumes(node *n, int &sum){
        if(n == nullptr){
            return;
        }
        re_arbre_sumes(n->f_esq, sum);
        re_arbre_sumes(n->f_dret, sum);
        sum =  (!(n->f_esq == nullptr ) ? n->f_esq->info : 0) + (!(n->f_dret == nullptr) ? n->f_dret->info : 0);
        n->info += sum;
    }
        
};

// Aquí va la implementació del mètode arbre_sumes

template <typename T>
void Abin<T>::arbre_sumes(){
    int sum;
    re_arbre_sumes(_arrel, sum);
}