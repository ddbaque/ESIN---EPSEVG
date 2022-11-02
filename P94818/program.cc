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
  void print(int i) const;

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
  /* static void insereix_bst(node *&n, const T &k); */
  static void consulta_bst(node *n, const T &k, bool &t);
  static void mostrar_bst(node *n, int niv);
  static node *insereix_bst(node *n, const T &k);
  static void print(node *n, int &t, const int i);
};

template <typename T>
void Abin<T>::print(node *n, int &t, const int i)
{
    if(n != nullptr)
    {
        if(n->f_esq != nullptr) print(n->f_esq, t, i);
        t++;
        if(t == i)
          cout << n->info;
        if(n->f_dret != nullptr) print(n->f_dret, t, i);
    }
}


template <typename T>
void Abin<T>::print(int i) const{
    int t = 0;
    cout << "[";
    print(_arrel, t, i);
    cout << "]" << endl;
}


template <typename T>
void Abin<T>::mostrar_bst()
{
  int niv = 0;
  mostrar_bst(_arrel, niv);
}

template <typename T>
void Abin<T>::mostrar_bst(node *n, int niv)
{
  if (n == nullptr)
    return;
  else
  {
    mostrar_bst(n->f_dret, niv + 1);
    int spc = 10 + niv * 10;
    cout << setw(spc) << n->info << endl;
    mostrar_bst(n->f_esq, niv + 1);
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
    _arrel = insereix_bst(_arrel, k);
  }
}

/* template <typename T>
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
} */

template <typename T>
void Abin<T>::print_nodes(node *p, ostream &os, string prefix)
{
  if (p == NULL)
    os << ".";
  else
  {
    string prefix2;
    os << "[" << p->info << "]\n"
       << prefix << " \\__";
    prefix2 = prefix + " |  ";
    print_nodes(p->f_dret, os, prefix2);
    os << "\n"
       << prefix << " \\__";
    prefix2 = prefix + "    ";
    print_nodes(p->f_esq, os, prefix2);
  }
}

// operador << d'escriptura
template <class U>
ostream &operator<<(ostream &os, const Abin<U> &a)
{
  a.print_nodes(a._arrel, os, "");
  os << "\n";
  return os;
}

template <typename T>
Abin<T>::Abin(Abin<T> &ae, const T &x, Abin<T> &ad)
{
  /* Pre: cert */
  /* Post: el resultat és un arbre amb x com arrel, ae com a fill
  esquerre i ad com a fill dret. No fa còpia dels arbres ae i ad */
  _arrel = new node;
  try
  {
    _arrel->info = x;
  }
  catch (...)
  {
    delete _arrel;
    throw;
  }
  _arrel->f_esq = ae._arrel;
  ae._arrel = NULL;
  _arrel->f_dret = ad._arrel;
  ad._arrel = NULL;
}

template <typename T>
typename Abin<T>::node *Abin<T>::insereix_bst(node *n, const T &k)
{
  if (n == nullptr)
  {
    n = new (node);
    n->info = k;
    n->f_dret = nullptr;
    n->f_esq = nullptr;
    return n;
  }
  else
  {
    if (n->info > k)
      n->f_esq = insereix_bst(n->f_esq, k);
    else
      n->f_dret = insereix_bst(n->f_dret, k);
    return n;
  }
}

int main(void)
{
  int n;
  Abin<int> bst;
  while (cin >> n)
  {
    bst.insereix_bst(n);
  }
  /*   cout << "salgo" << endl;
    cout << bst << endl; */
  cout << bst << endl;
  bst.mostrar_bst();
  cout << endl;
  bst.print(7);
}