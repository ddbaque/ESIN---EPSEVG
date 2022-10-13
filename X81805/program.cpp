#include "arbreBin.hpp"

using namespace std;

arbreBin<int> add(const arbreBin<int> &a)
{
    if (a.es_buit())
        return arbreBin<int>();

    int sum = a.arrel();
    arbreBin<int> a1 = add(a.fe());
    arbreBin<int> a2 = add(a.fd());
    sum += (!a1.es_buit() ? a1.arrel() : 0) + (!a2.es_buit() ? a2.arrel() : 0);

    return arbreBin<int>(sum, a1, a2);
}

int main()
{
    arbreBin<int> a;
    cin >> a;

/*     arbreBin<int> b = add(a); */

    cout << a << endl;
    if(a.es_buit()) cout << "vacio" << endl;
    return 0;
}