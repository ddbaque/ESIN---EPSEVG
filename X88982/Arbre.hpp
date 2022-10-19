#include <cstdlib>
#include <string>
using namespace std;
typedef unsigned int nat;

template <typename T>
class Arbre
{

public:
    // Construeix un Arbre format per un únic node que conté a x.
    Arbre(const T &x);

/*     void preordre() const;
 */

    // Tres grans.
    Arbre(const Arbre<T> &a);
    Arbre &operator=(const Arbre<T> &a);
    ~Arbre() throw();

    // Col·loca l’Arbre donat com a primer fill de l’arrel de l’arbre sobre el que s’aplica el mètode i l’arbre a queda invalidat; després de fer b.afegir_fill(a), a no és un arbre vàlid.
    void afegir_fill(Arbre<T> &a);

    static const int ArbreInvalid = 400;

    // Comprova que el contingut de cada node coincideix amb la suma dels nodes
    // dels seus fills, exceptuant les fulles (els de grau 0).
    bool es_arbre_suma();

private:
    Arbre() : _arrel(NULL){};
    struct node
    {
        T info;
        node *primf;
        node *seggerm;
    };
    node *_arrel;
    static node *copia_arbre(node *p);
    static void destrueix_arbre(node *p) throw();
    static void es_arbre_suma(node *p, bool &t);
/*     static void preordre(node *p, string pre);
 */

    // Aquí va l’especificació dels mètodes privats addicionals
};

// Aquí va la implementació del mètode es_arbre_suma

template <typename T> 
bool Arbre<T>::es_arbre_suma(){
    bool t = true;
    es_arbre_suma(_arrel, t);
    return t;
}

template <typename T>
void Arbre<T>::es_arbre_suma(node *p, bool &t){
    
    if(p->primf == nullptr) return;

    int sum = 0;
    bool tr = false;

    es_arbre_suma(p->primf, t);
    
    node *paux = p->primf;

    while (paux != nullptr)
    {
        sum += paux->info;
        tr = true;
        paux = paux->seggerm;

        if(paux != nullptr){
            if(paux->primf != nullptr){
                es_arbre_suma(paux->primf, t);
            }
        }
    }
    
    if(sum != p->info and tr){
        t = false;
    }
    
}

/* template <typename T>
void Arbre<T>::preordre(node *p, string pre)
{
  if (p != NULL)
  {
    cout << pre << p->info << endl;
    preordre(p->primf, pre + "  ");
    preordre(p->seggerm, pre);
  }
}

template <typename T>
void Arbre<T>::preordre() const
{
  preordre(_arrel, "");
} */