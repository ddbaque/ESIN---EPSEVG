#include <iostream>
using namespace std;
typedef unsigned int nat;

template <typename Clau>
class dicc
{

public:
    // Constructora per defecte. Crea un diccionari buit.
    dicc();

    // Destructora
    ~dicc();

    // Insereix la clau k en el diccionari. Si ja hi era, no fa res.
    void insereix(const Clau &k);

    // Retorna quants elements (claus) té el diccionari.
    nat quants() const;

    // Retorna la segona clau.
    // Pre: El diccionari té com a mínim 2 claus.
    Clau segona() const;

private:
    struct node
    {
        Clau _k;     // Clau
        node *_esq;  // fill esquerre
        node *_dret; // fill dret
        nat _n;      // Nombre de nodes del subarbre
        node(const Clau &k, node *esq = NULL, node *dret = NULL);
    };
    node *_arrel;

    static void esborra_nodes(node *m);
    node *segona_clau_aux(node *n) const;
    node *element_per_posicio(node* n, nat pos) const;
    static node *insereix_bst(node *n, const Clau &k, bool &ins);

    // Aquí va l’especificació dels mètodes privats addicionals
};

// Aquí va la implementació dels mètodes públics i privats
template <typename Clau>
Clau dicc<Clau>::segona() const
{
    node *segona_clau = element_per_posicio(_arrel, 2);
    return segona_clau->_k;
}

template <typename Clau>
typename dicc<Clau>::node *dicc<Clau>::segona_clau_aux(node *n) const
{
    if (n == NULL || n->_esq == NULL)
    {
        return n;
    }
    node *segona_clau_esq = segona_clau_aux(n->_esq);
    if (segona_clau_esq == NULL || segona_clau_esq->_n == 1)
    {
        return n;
    }
    return segona_clau_esq;
}
template <typename Clau>
typename dicc<Clau>::node* dicc<Clau>::element_per_posicio(node* n, nat pos) const {
    if (n == NULL) {
        return n;
    }
    nat grandaria_esq = n->_esq != NULL ? n->_esq->_n : 0;
    if (pos == grandaria_esq + 1) {
        return n;
    }
    else if (pos <= grandaria_esq) {
        return element_per_posicio(n->_esq, pos);
    }
    else {
        return element_per_posicio(n->_dret, pos - grandaria_esq - 1);
    }
}