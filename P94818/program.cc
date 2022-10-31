#include "Bst.hpp"

int main(void)
{
    int n;
    Abin<int> bst;
    while(cin >> n){
        bst.insereix_bst(n);
    }
  /*   cout << "salgo" << endl;
    cout << bst << endl; */
    bst.mostrar_bst();
}