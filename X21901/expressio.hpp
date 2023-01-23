#include <cstdlib>
#include <iostream>
using namespace std;
typedef unsigned int nat;

class expressio
{
    // Guarda una expressio en un arbre binari.
    // Els operadors i operands es guarden en l’string token de cada node.
    // Els operadors unaris (+ - sqrt log exp) tenen el fill dret buit.
public:
    expressio() : _arrel(nullptr){};
    // Pre: cert
    // Post: el resultat és un arbre sense cap element
    expressio(expressio &ae, const string &x, expressio &ad);
    // Pre: cert
    // Post: el resultat és un arbre amb un element i dos subarbres

    // Les tres grans
    expressio(const expressio &a);
    ~expressio();
    expressio &operator=(const expressio &a);

    // operador << d’escriptura
    friend std::ostream &operator<<(std::ostream &, const expressio &a);

    // operador >> de lectura
    friend std::istream &operator>>(std::istream &, expressio &a);

    string llista_tokens_parentitzada() const;
    // Pre: Cert
    // Post: Retorna string amb la representació infixa de l’expressió amb tots els parèntesis possibles,
    // excepte quan són operands (constants o variables) que mai fan falta.

private:
    struct node
    {
        node *f_esq;
        node *f_dret;
        string token;
    };
    node *_arrel;
    static node *copia_nodes(node *m);
    static void esborra_nodes(node *m);
    static void print_nodes(node *m, ostream &os, string d1);
    static void r_llista_tokens_parentitzada(node *n, string &s);
};

void expressio::r_llista_tokens_parentitzada(node *n, string &s)
{
    if (n != nullptr)
    {
        if (n->f_dret != nullptr && n->f_esq != nullptr)
        {
            s += "(";
            r_llista_tokens_parentitzada(n->f_esq, s);
            s += n->token;
            r_llista_tokens_parentitzada(n->f_dret, s);
            s += ")";
        }
        else if (n->f_dret == nullptr && n->f_esq != nullptr)
        {
            s += n->token + "(";
            r_llista_tokens_parentitzada(n->f_esq, s);
            s += ")";
        }
        else
        {
            s += n->token;
        }
    }
}

string expressio::llista_tokens_parentitzada() const
{
    string s;
    r_llista_tokens_parentitzada(_arrel, s);
    return s;
}
