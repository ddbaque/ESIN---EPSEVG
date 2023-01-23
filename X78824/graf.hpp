#include <vector>
#include <iostream>

using namespace std;
typedef unsigned int nat;

class graf
{
    //! Graf dirigit i no etiquetat (Matriu d'adjacència)
    // Les arestes es guarden en una matriu d’adjacència.
public:
    // Constructora per defecte. Crea un graf buit.
    graf();

    // Destructora
    ~graf();

    // Llegeix les dades del graf del canal d’entrada
    void llegeix();

    bool hi_ha_cami(nat ini, nat fi) const;
    // Pre: ini i fi són vèrtexs del graf (són menors que n)
    // Post: Retorna un booleà indicant si hi ha camí per anar d’ini a fi

private:
    nat n;                  // Nombre de vèrtexs
    nat m;                  // Nombre d’arestes
    vector<vector<bool>> a; // Matriu d’adjacència

    // Aquí va l’especificació dels mètodes privats addicionals
};

bool graf::hi_ha_cami(nat ini, nat fi) const
{
    if((ini == fi) && (ini < n) && fi < n) return true;
    else if(ini >= n || fi >= n) return false;
    return a[ini][fi];
}