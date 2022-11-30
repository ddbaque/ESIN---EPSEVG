#include <iostream>
using namespace std;
typedef unsigned int nat;

class dicc
{
    // Taula de dispersió sinònims encadenats indirectes
    // Les llistes de sinònims estan ordenades per clau
public:
    // Constructora per defecte. Crea un diccionari buit.
    dicc();

    // Destructora
    ~dicc();

    // Retorna quants elements (claus) té el diccionari.
    nat quants() const;

    // Impressió per cout de totes les claus del diccionari segons l’ordre
    // en que estan a cadascuna de les llistes encadenades indirectes
    void print() const;

    // Pre: Cert
    // Post: Insereix la clau k en el diccionari. Si ja hi era, no fa res.
    void insereix(const int &k);

    // Pre: El diccionari res està buit
    // Post: Omple res amb la intersecció entre el p.i. i d2
/*     void interseccio(const dicc &d2, dicc &res) const;
 */
private:
    struct node_hash
    {
        int _k; // Clau
        node_hash *_seg;
    };
    node_hash **_taula; // Taula amb punters a les llistes de sinònims
    nat _M;             // Mida de la taula
    nat _quants;        // Nº d’elements guardats al diccionari

    static long const MULT = 31415926;

    // Calcula un valor de dispersió entre 0 i LONG_MAX a partir de k
    static long h(int k);

    // Destrueix la llista de nodes apuntats per p
    static void esborra_nodes(node_hash *p);

    // consulta si la clau k hi es, retorna false si no hi es
    void consulta(const int k, bool &t);
};

void dicc::consulta(const int k, bool &t)
{
    int i = h(k);

    node_hash *p = _taula[i];
    t = false;

    while (p != nullptr && !t)
    {
        if (p->_k == k)
        {
            t = true;
        }
        else
        {
            p = p->_seg;
        }
    }
}

void dicc::insereix(const int &k)
{
    cout << "flag 1" << endl;
    int i = h(k);
    i = 12;
    cout << "h -> " << i << endl;
    node_hash *p = _taula[i];
    bool t = false;
    while (p != nullptr && !t)
    {
        cout << "flag 3" << endl;
        if (p->_k == k)
            t = true;
        else
            p = p->_seg;
    }
    cout << "flag 2" << endl;   
    if (!t)
    {
        if (_taula[i] == nullptr)
        {
            p = new (node_hash);
            p->_k = k;
            p->_seg = nullptr;
            _taula[i] = p;
        }
        else
        {
            node_hash *q = _taula[i];
            node_hash *ant = nullptr;
            p = new (node_hash);
            p->_k = k;
            t = false;
            while (q != nullptr && !t)
            {
             
                if (q->_k < k)
                {
                    t = true;
                    p->_seg = q;
                    if(ant != nullptr){
                        ant->_seg = p;
                    }else{
                        _taula[i] = p;
                    }
                }
                ant = q;
                q = q->_seg;
            }
            if (!t){
                ant->_seg = p;
                p->_seg = nullptr;

            }
        }
        ++_quants;
    }
}

/* void dicc::interseccio(const dicc &d3, dicc &res) const {} */