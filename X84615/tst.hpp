#include <iostream>
#include <list>
#include <vector>
using namespace std;
typedef unsigned int nat;

class dicc
{
public:
    // Constructora per defecte. Crea un diccionari buit.
    dicc();

    // Destructora
    ~dicc();

    // Insereix la clau k en el diccionari. Si ja hi era, no fa res.
    void insereix(const string &k);

    // ** Retorna un vector amb totes les claus
    void claus();
    list<string> llista_ordenada_dec() const;

    /*     vector<nat> freq_longituds() const;
     */
    // Pre: True
    // Post: Retorna un vector amb les freqüències de les longituds de les claus.
    // La mida del vector és igual a la longitud de la clau més llarga més un.

private:
    struct node
    {
        char _c;    // Símbol posició i-èssima de la clau
        node *_esq; // Fill esquerra, apunta a símbols mateixa posició formant un BST
        node *_cen; // Fill central, apunta a símbols següent posició
        node *_dre; // Fill dret, apunta a símbols mateixa posició formant un BST
        node(const char &c, node *esq = NULL, node *cen = NULL, node *dre = NULL);
    };
    node *_arrel;

    static void esborra_nodes(node *t);
    static node *insereix(node *t, nat i, const string &k);
    static void print(node *n, string s, list<string> &vs);

    // Aquí va l’especificació dels mètodes privats addicionals
};

void dicc::claus()
{
    list<string> s;
    print(_arrel, "", s);
}

void dicc::print(node *n, string s, list<string> &vs)
{
    if (n != nullptr)
    {
        if (n->_dre != nullptr)
            print(n->_dre, s, vs);
        print(n->_cen, s + n->_c, vs);
        if (n->_c == '#')
        {
            vs.push_back(s);
            if (n->_esq != nullptr)
                print(n->_esq, s, vs);
            return;
        }
        if (n->_esq != nullptr)
            print(n->_esq, s, vs);
    }
}

list<string> dicc::llista_ordenada_dec() const {
    list<string> s;
    print(_arrel, "", s);
    return s;
}