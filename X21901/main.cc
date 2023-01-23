#include <iostream>
#include "expressio.hpp"

typename expressio::node *expressio::copia_nodes(node *m)
{
  /* Pre: cert */
  /* Post: si m és nullptr, el resultat és nullptr; sinó,
     el resultat apunta al primer node d'un arbre binari
     de nodes que són còpia de l'arbre apuntat per m */
  node *n;
  if (m == nullptr)
    n = nullptr;
  else
  {
    n = new node;
    try
    {
      n->token = m->token;
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

void expressio::esborra_nodes(node *m)
{
  /* Pre: cert */
  /* Post: no fa res si m és nullptr, sinó allibera
     espai dels nodes de l'arbre binari apuntat per m */
  if (m != nullptr)
  {
    esborra_nodes(m->f_esq);
    esborra_nodes(m->f_dret);
    delete m;
  }
};

expressio::expressio(expressio &ae, const string &x, expressio &ad)
{
  /* Pre: cert */
  /* Post: el resultat és un arbre amb x com arrel, ae com a fill
  esquerre i ad com a fill dret. No fa còpia dels arbres ae i ad */
  _arrel = new node;
  try
  {
    _arrel->token = x;
  }
  catch (...)
  {
    delete _arrel;
    throw;
  }
  _arrel->f_esq = ae._arrel;
  ae._arrel = nullptr;
  _arrel->f_dret = ad._arrel;
  ad._arrel = nullptr;
}

expressio::expressio(const expressio &a)
{
  _arrel = copia_nodes(a._arrel);
};

expressio::~expressio()
{
  esborra_nodes(_arrel);
};

expressio &expressio::operator=(const expressio &a)
{
  if (this != &a)
  {
    node *aux;
    aux = copia_nodes(a._arrel);
    esborra_nodes(_arrel);
    _arrel = aux;
  }
  return (*this);
};

void expressio::print_nodes(node *p, ostream &os, string prefix)
{
  if (p == nullptr)
    os << "#";
  else
  {
    string prefix2;
    os << "[" << p->token << "]\n"
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
ostream &operator<<(ostream &os, const expressio &a)
{
  a.print_nodes(a._arrel, os, "");
  os << "\n";
  return os;
}

// operador >> de lectura
istream &operator>>(istream &is, expressio &a)
{
  string token;
  cin >> token;
  if (token != "#")
  {
    expressio ae;
    is >> ae;
    expressio ad;
    is >> ad;
    a = expressio(ae, token, ad);
  }
  return is;
}

int main()
{
  expressio e;
  cin >> e;
  cout << e << endl;
  string s(e.llista_tokens_parentitzada());
  cout << s << endl;
  return 0;
}
