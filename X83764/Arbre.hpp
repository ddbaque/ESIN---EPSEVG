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

    // Tres grans.
    Arbre(const Arbre<T> &a);
    Arbre &operator=(const Arbre<T> &a);
    ~Arbre() throw();

    // Col·loca l’Arbre donat com a primer fill de l’arrel de l’arbre sobre el que s’aplica el mètode i l’arbre a queda invalidat; després de fer b.afegir_fill(a), a no és un arbre vàlid.
    void afegir_fill(Arbre<T> &a);

    // Imprimeix la informació dels nodes en preodre, cada element en una nova línia i
    // precedit per espais segons el nivell on està situat.
    void preordre() const;

    static const int ArbreInvalid = 400;

    // Elimina tots els nodes de grau 0 de l’arbre.
    void elimina_grau0();

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
    static void preordre(node *p, string pre);
    static node *elimina_grau0(node *p);

    // Aquí va l’especificació dels mètodes privats addicionals
};

// Aquí va la implementació del mètode elimina_grau0

template <typename T>
void Arbre<T>::elimina_grau0(){
    _arrel = elimina_grau0(_arrel);
}

template <typename T>
typename Arbre<T>::node* Arbre<T>::elimina_grau0(node *p){
    if(p == nullptr) return nullptr;
    if(p->primf == nullptr){
        node *paux = p;
        delete paux;
        p = elimina_grau0(p->seggerm);
        return p;
    }else{
        p->primf = elimina_grau0(p->primf);
        p->seggerm = elimina_grau0(p->seggerm);
        return p;
    }
} 
