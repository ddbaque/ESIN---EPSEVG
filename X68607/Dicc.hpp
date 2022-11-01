#include <iostream>
using namespace std;

typedef unsigned int nat;

template <typename Clau>
class dicc
{

public:
    // Constructora per defecte. Crea un diccionari buit.
    dicc();

    // Les tres grans: Constructora per còpia, destructora, operador d’assignació
    dicc(const dicc &d);
    ~dicc();
    dicc &operator=(const dicc &d);

    // Insereix la clau k en el diccionari. Si ja hi era, no fa res.
    void insereix(const Clau &k);

    // Elimina la clau k del diccionari. Si no hi era, no fa res.
    void elimina(const Clau &k);

    // Consulta si la clau k està en el diccionari.
    bool consulta(const Clau &k) const;

    // Retorna quants elements (claus) té el diccionari.
    nat quants() const;

    // Impressió per cout de claus del diccionari en ordre ascendent, separades per
    // un espai, començant per ’[’ i acabant per ’]’, en dues versions:
    // Imprimeix totes les claus
    void print() const;
    // Imprimeix les claus entre k1 i k2 ambdós incloses. Pre: k1 <= k2
    void print_interval(const Clau &k1, const Clau &k2) const;

    // Retorna la clau més petita i la més gran respectivament.
    // Pre: El diccionari no està buit
    Clau min() const;
    Clau max() const;

    // Retorna la clau de la posició i-èssima (comptant-les en ordre ascendent).
    // Pre: El diccionari no està buit. 1 <= i <= quants()
    Clau iessim(nat i) const;

private:
    struct node
    {
        Clau _k;
        node *_esq;
        node *_dret;
    };
    nat _mida;
    node *_arrel;
    static node *copia_nodes(node *m);
    static void esborra_nodes(node *n);
    static node *insereix(node *n, const Clau &k);
    static void consulta_clau(node *n, const Clau &k, bool &t);
    static void print(node *n, bool &t);
};

// Aquí va la implementació dels mètodes públics i privats

template <typename Clau>
// Constructora per defecte. Crea un diccionari buit.
dicc<Clau>::dicc()
{
    _arrel = nullptr;
    _mida = 0;
}

template <typename Clau>
dicc<Clau>::dicc(const dicc<Clau> &d)
{
    _arrel = copia_nodes(d._arrel);
    _mida = d._mida;
}

template <typename Clau>
dicc<Clau>::~dicc()
{
    esborra_nodes(_arrel);
    _mida = 0;
}

template <typename Clau>
void dicc<Clau>::esborra_nodes(node *n)
{
    /* Pre: cert */
    /* Post: no fa res si n és NULL, sinó allibera
       espai dels nodes de l'arbre binari apuntat per n */
    if (n != NULL)
    {
        esborra_nodes(n->f_esq);
        esborra_nodes(n->f_dret);
        delete n;
    }
};

template <typename Clau>
typename dicc<Clau>::node *dicc<Clau>::copia_nodes(node *m)
{
    /* Pre: cert */
    /* Post: si m és NULL, el resultat és NULL; sinó,
       el resultat apunta al primer node d'un arbre binari
       de nodes que són còpia de l'arbre apuntat per m */
    node *n;
    if (m == NULL)
        n = NULL;
    else
    {
        n = new node;
        try
        {
            n->info = m->info;
            n->f_esq = copia_nodes(m->f_esq);
            n->f_dret = copia_nodes(m->f_dret);
        }
        catch (...)
        {
            delete n;
            throw;
        }
    }
    return n;
};

template <typename Clau>
dicc<Clau> &dicc<Clau>::operator=(const dicc<Clau> &a)
{
    if (this != &a)
    {
        node *aux;
        aux = copia_nodes(a._arrel);
        esborra_nodes(_arrel);
        _arrel = aux;
    }
    _mida = a._mida;
    return (*this);
};

template <typename Clau>
// Insereix la clau k en el diccionari. Si ja hi era, no fa res.
void dicc<Clau>::insereix(const Clau &k)
{
    bool hi_es_k = consulta(k);
    if (!hi_es_k)
    {
        _arrel = insereix(_arrel, k);
        _mida++;
    }
}

template <typename Clau>
typename dicc<Clau>::node *dicc<Clau>::insereix(node *n, const Clau &k)
{
    if (n == nullptr)
    {
        n = new (node);
        n->_k = k;
        n->_dret = nullptr;
        n->_esq = nullptr;
        return n;
    }
    else
    {
        if (n->_k > k)
            n->_esq = insereix(n->_esq, k);
        else
            n->_dret = insereix(n->_dret, k);
        return n;
    }
}

template <typename Clau>
bool dicc<Clau>::consulta(const Clau &k) const
{
    bool t = false;
    consulta_clau(_arrel, k, t);
    return t;
}

template <typename Clau>
void dicc<Clau>::consulta_clau(node *n, const Clau &k, bool &t)
{
    if (n != nullptr)
    {
        if (n->_k == k)
        {
            t = false;
            return;
        }
        else
        {
            if (n->_k > k)
                consulta_clau(n->_esq, k, t);
            else
                consulta_clau(n->_dret, k, t);
        }
    }
}

template <typename Clau>
nat dicc<Clau>::quants() const
{
    return _mida;
}

template <typename Clau>
void dicc<Clau>::print(node *n, bool &t)
{
    if(n != nullptr)
    {
        if(n->_esq != nullptr) print(n->esq, t);
        if(!t) cout << " ";
        t = false;
        cout << n->_k;
        if(n->dret != nullptr) print(n->dret, t);
    }
}

template <typename Clau>
void dicc<Clau>::print() const{
    bool t = true;
    cout << "[";
    print(_arrel, t);
    cout << "]" << endl;
}

