#include <cstdlib>
#include <iostream>
#include <iomanip>
using namespace std;
typedef unsigned int nat;

template <typename T>
class Abin
{
public:
    Abin() : _arrel(NULL){};
    Abin(Abin<T> &ae, const T &x, Abin<T> &ad);
    // Pre: cert
    // Post: el resultat és un arbre amb un element i dos subarbres
    /* 
    // Pre: cert
    // Post: el resultat és un arbre sense cap element

    // Les tres grans
    Abin(const Abin<T> &a);
    ~Abin();
    Abin<T> &operator=(const Abin<T> &a);
*/
    // operador << d’escriptura
    template <class U>
    friend std::ostream &operator<<(std::ostream &, const Abin<U> &a);

    // operador >> de lectura
    template <class U>
    friend std::istream &operator>>(std::istream &, Abin<U> &a); 
    void insereix_bst(const T &k);
    bool consulta_bst(const T &k);
    void mostrar_bst();

private:
    struct node
    {
        node *f_esq;
        node *f_dret;
        T info;
    };
    node *_arrel;
    /* static node *copia_nodes(node *m);
    static void esborra_nodes(node *m);*/
    static void print_nodes(node *m, ostream &os, string d1); 
    static void insereix_bst(node *&n, const T &k);
    static void consulta_bst(node *n, const T &k, bool &t);
    static void mostrar_bst(node *n, int niv);
};

template <typename T>
void Abin<T>::mostrar_bst(){
    int niv = 0;
    mostrar_bst(_arrel, niv);
}

template <typename T>
void Abin<T>::mostrar_bst(node *n, int niv){
    if(n == nullptr) return;
    else{
        mostrar_bst(n->f_dret, niv+1);
        int spc = 10 + niv*10;
        cout << setw(spc) << n->info << endl;
        mostrar_bst(n->f_esq, niv+1);
    }
}

template <typename T>
bool Abin<T>::consulta_bst(const T &k)
{
    bool t = false;
    consulta_bst(_arrel, k, t);
    return t;
}

template <typename T>
void Abin<T>::consulta_bst(node *n, const T &k, bool &t)
{
    if (n != nullptr)
    {
        if (n->info == k)
        {
            t = true;
            return;
        }
        else if (n->info > k)
            consulta_bst(n->f_esq, k, t);
        else
            consulta_bst(n->f_dret, k, t);
    }
}

template <typename T>
void Abin<T>::insereix_bst(const T &k)
{
    bool hi_es_k = consulta_bst(k);
    if (!hi_es_k)
    {
        insereix_bst(_arrel, k);
    }
}

template <typename T>
void Abin<T>::insereix_bst(node *&n, const T &k)
{
    if (n == nullptr)
    {
        n = new (node);
        n->info = k;
        n->f_esq = nullptr;
        n->f_dret = nullptr;
    }
    else if (n->info > k)
    {
        insereix_bst(n->f_esq, k);
    }
    else
    {
        insereix_bst(n->f_dret, k);
    }
}

template <typename T>
void Abin<T>::print_nodes(node* p, ostream &os, string prefix) {
  if (p == NULL) 
    os << ".";
  else {
    string prefix2;
    os << "["<<p->info << "]\n" << prefix << " \\__";
    prefix2 = prefix + " |  ";
    print_nodes(p->f_dret, os, prefix2);
    os << "\n" << prefix << " \\__";
    prefix2 = prefix + "    ";
    print_nodes(p->f_esq, os, prefix2);
  }
}

// operador << d'escriptura
template <class U>
ostream& operator<<(ostream &os, const Abin<U> &a) {
  a.print_nodes(a._arrel, os, "");
  os << "\n";
  return os;
}

template <typename T>
Abin<T>::Abin(Abin<T>& ae, const T& x, Abin<T>& ad) {
/* Pre: cert */
/* Post: el resultat és un arbre amb x com arrel, ae com a fill
esquerre i ad com a fill dret. No fa còpia dels arbres ae i ad */
  _arrel = new node;
  try {
    _arrel->info = x;
  }
  catch (...) {
    delete _arrel;
    throw;
  }
  _arrel->f_esq = ae._arrel;
  ae._arrel = NULL;
  _arrel->f_dret = ad._arrel;
  ad._arrel = NULL;
}