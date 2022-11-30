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
        nat _n_subs;
    };
    nat _mida;
    node *_arrel;
    static void print_nodes(node *m, string d1);
    static node *copia_nodes(node *m);
    static void esborra_nodes(node *n);
    static node *insereix(node *n, const Clau &k);
    static void consulta_clau(node *n, const Clau &k, bool &t);
    static void print(node *n, bool &t);
    static void print_interval(node *n, const Clau &k1, const Clau &k2, bool &t);
    static void iessim(node *n, const nat i, Clau &k);
    node *elimina_bst(node *n, const Clau &k);
    static node *ajunta(node *t1, node *t2) throw();
    static node *elimina_maxim(node *p) throw();
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
        esborra_nodes(n->_esq);
        esborra_nodes(n->_dret);
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
            n->_n_subs = m->_n_subs;
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
        n->_n_subs = 1;
        return n;
    }
    else
    {
        if (n->_k > k)
        {
            n->_n_subs++;
            n->_esq = insereix(n->_esq, k);
        }
        else
        {
            n->_n_subs++;
            n->_dret = insereix(n->_dret, k);
        }
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
            t = true;
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
    if (n != nullptr)
    {
        if (n->_esq != nullptr)
            print(n->_esq, t);
        if (!t)
            cout << " ";
        t = false;
        cout << n->_k;
        if (n->_dret != nullptr)
            print(n->_dret, t);
    }
}

template <typename Clau>
void dicc<Clau>::print() const
{
    bool t = true;
    cout << "[";
    print(_arrel, t);
    cout << "]";
}

template <typename Clau>
void dicc<Clau>::print_interval(const Clau &k1, const Clau &k2) const
{
    bool t = true;
    cout << "[";
    print_interval(_arrel, k1, k2, t);
    cout << "]";
}

template <typename Clau>
void dicc<Clau>::print_interval(node *n, const Clau &k1, const Clau &k2, bool &t)
{
    if (n != nullptr)
    {
        if (k1 <= n->_k)
            print_interval(n->_esq, k1, k2, t);
        if (n->_k >= k1 && n->_k <= k2)
        {
            if (!t)
                cout << " ";
            t = false;
            cout << n->_k;
        }
        if (k2 >= n->_k)
            print_interval(n->_dret, k1, k2, t);
    }
}

template <typename Clau>
Clau dicc<Clau>::min() const
{
    node *it = _arrel;
    while (it->_esq != nullptr)
    {
        it = it->_esq;
    }
    return it->_k;
}

template <typename Clau>
Clau dicc<Clau>::max() const
{
    node *it = _arrel;
    while (it->_dret != nullptr)
    {
        it = it->_dret;
    }
    return it->_k;
}

template <typename Clau>
Clau dicc<Clau>::iessim(nat i) const
{
    int cnt = 0;
    Clau k;
    cout << endl;
    print_nodes(_arrel, "");
    if (i <= _mida && i >= 1)
    {
        iessim(_arrel, i, k);
        cout << "flag 1" << endl;
    }
    return k;
}

template <typename T>
void dicc<T>::print_nodes(node *p, string prefix)
{
    if (p == NULL)
        cout << ".";
    else
    {
        string prefix2;
        cout << "[" << p->_k << ", " << p->_n_subs << "]\n"
           << prefix << " \\__";
        prefix2 = prefix + " |  ";
        print_nodes(p->_dret, prefix2);
        cout << "\n"
           << prefix << " \\__";
        prefix2 = prefix + "    ";
        print_nodes(p->_esq, prefix2);
    }
}

template <typename Clau>
void dicc<Clau>::iessim(node *n, const nat i, Clau &k)
{
    node *n_esq = n->_esq;
    if (n_esq == nullptr)
    {
        if (i == n->_n_subs)
        {
            cout << "flag 3" << endl;
            k = n->_k;
            return;
        }
    }
    else
    {
        if (i == n_esq->_n_subs + 1)
        {
            cout << "entro" << endl;
            k = n_esq->_k;
            return;
        }
        else if (i < n_esq->_n_subs + 1)
        {
            cout << "flag 2" << endl;
            iessim(n->_esq, i, k);
        }
        else
        {
            const int pos = i - n_esq->_n_subs - 1;
            iessim(n, pos, k);
        }
    }

    /* if (n != nullptr)
    {
        if (n->_esq != nullptr)
            iessim(n->_esq, cnt, i, k);
        cnt++;
        if (cnt == i)
            k = n->_k;
        if (n->_dret != nullptr)
            iessim(n->_dret, cnt, i, k);
    } */
}

template <typename Clau>
void dicc<Clau>::elimina(const Clau &k)
{
    if (consulta(k))
        _arrel = elimina_bst(_arrel, k);
}

template <typename Clau>
typename dicc<Clau>::node *dicc<Clau>::elimina_bst(node *n, const Clau &k)
{
    node *p = n;
    if (n != nullptr)
    {
        if (k < n->_k)
        {
            n->_n_subs--;
            n->_esq = elimina_bst(n->_esq, k);
        }
        else if (k > n->_k)
        {
            n->_n_subs--;
            n->_dret = elimina_bst(n->_dret, k);
        }
        else
        {
            int aux = n->_n_subs;
            n = ajunta(n->_esq, n->_dret);
            delete (p);
            if (n != nullptr)
                n->_n_subs = aux - 1;
            _mida--;
        }
    }
    return n;
}

template <typename Clau>
typename dicc<Clau>::node *dicc<Clau>::ajunta(node *t1, node *t2) throw()
{
    if (t1 == NULL)
    {
        return t2;
    }
    if (t2 == NULL)
    {
        return t1;
    }
    node *p = elimina_maxim(t1);
    p->_dret = t2;
    return p;
}

template <typename Clau>
typename dicc<Clau>::node *dicc<Clau>::elimina_maxim(node *p) throw()
{
    node *p_orig = p, *pare = NULL;
    while (p->_dret != NULL)
    {
        p->_n_subs--;
        pare = p;
        p = p->_dret;
    }
    if (pare != NULL)
    {
        pare->_dret = p->_esq; // p és fill dret de pare
        p->_esq = p_orig;
    }
    return p;
}