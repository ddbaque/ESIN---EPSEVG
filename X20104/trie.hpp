#include <iostream>
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

    // ** Retorna true si la clau k hi és al diccionari
    bool consulta(const string &k);

    // ** Retorna les claus de mayor a menor
    void print_creixent();

    //** Retorna les claus de menor a mayor
    void print_decreixent();

    nat paraules_n_simbols(int n) const;

    vector<nat> freq_longituds() const;

    nat cadena_mas_larga() const;

    // Pre: True
    // Post: Retorna un vector amb les freqüències de les longituds de les claus.
    // La mida del vector és igual a la longitud de la clau més llarga més un.

private:
    struct node
    {
        char _c;   // Símbol posició i-èssima de la clau
        node *_pf; // Primer fill, apunta a símbols de la següent posició
        node *_sg; // Següent germà, apunta a símbols de la mateixa posició
        node(const char &c, node *pf = NULL, node *sg = NULL);
    };
    node *_arrel;

    static void esborra_nodes(node *t);
    static node *insereix(node *t, nat i, const string &k);
    static node *consulta_node(node *n, const string &k, nat i);
    /*     static void dfs(vector<nat> &v, vector<nat> &freq, node *t, int longitud);
     */
    static void dfs_n_simbols(vector<string> &paraules, string &paraula, node *t, int n);
    static void print(node *n, string s, vector<string> &st);
    static void dfs_cadena_mas_larga(string &cadena, nat &longitud, node * t);
    static void dfs_longituds(int &max_longitud, node* t, int longitud);
    static void dfs_count(vector<nat> &freqs, node* t, int longitud);
};

/* vector<nat> dicc::freq_longituds() const
{
    nat l = cadena_mas_larga();
    vector<nat> freqs(l+1, 0);
    if(l == 0) return vector<nat>();
    for(int i = 0; i < l+1; i++){
        freqs[i] = paraules_n_simbols(i);
    }
    return freqs;
}
 */
vector<nat> dicc::freq_longituds() const {
    int max_longitud = 0;
    dfs_longituds(max_longitud, _arrel, 0);
    if(max_longitud == 0) return vector<nat>();
    vector<nat> freqs(max_longitud + 1, 0);
    dfs_count(freqs, _arrel, 0);
    return freqs;
}

//** Retorna en max_longitud la longitud més llarga
void dicc::dfs_longituds(int &max_longitud, node* t, int longitud) {
    if (t == NULL) return;
    if (t->_c == '#') max_longitud = max(max_longitud, longitud);
    dfs_longituds(max_longitud, t->_pf, longitud + 1);
    dfs_longituds(max_longitud, t->_sg, longitud);
}

void dicc::dfs_count(vector<nat> &freqs, node* t, int longitud) {
    if (t == NULL) return;
    if (t->_c == '#') ++freqs[longitud];
    dfs_count(freqs, t->_pf, longitud + 1);
    dfs_count(freqs, t->_sg, longitud);
}

nat dicc::cadena_mas_larga() const {
    string cadena = "";
    nat longitud = 0;
    dfs_cadena_mas_larga(cadena, longitud, _arrel);
    return longitud;
}

void dicc::dfs_cadena_mas_larga(string &cadena, nat &longitud, node* t) {
    if (t == NULL) return;
    if (t->_c != '#') cadena += t->_c;
    if (t->_c == '#' && cadena.size() > longitud) {
        longitud = cadena.size();
    }
    dfs_cadena_mas_larga(cadena, longitud, t->_pf);
    if (t->_c != '#') cadena.pop_back();
    dfs_cadena_mas_larga(cadena, longitud, t->_sg);
}


bool dicc::consulta(const string &k)
{
    node *n = consulta_node(_arrel, k, 0);
    if (n == nullptr)
        return false;
    return true;
}

dicc::node *dicc::consulta_node(node *n, const string &k, nat i)
{
    node *res = nullptr;
    if (n != nullptr)
    {
        if (i == k.length() && n->_c == '#')
            res = n;
        else if (k[i] == n->_c)
            res = consulta_node(n->_pf, k, i + 1);
        else if (k[i] > n->_c)
            res = consulta_node(n->_sg, k, i);
        else
            res = nullptr;
    }
    return res;
}

nat dicc::paraules_n_simbols(int n) const
{
    vector<string> paraules;
    string paraula = "";
    dfs_n_simbols(paraules, paraula, _arrel, n);
    return paraules.size();
}

void dicc::dfs_n_simbols(vector<string> &paraules, string &paraula, node *t, int n)
{
    if (t == NULL)
        return;
    if (t->_c != '#')
        paraula += t->_c;
    if (t->_c == '#' && paraula.size() == n)
        paraules.push_back(paraula);
    dfs_n_simbols(paraules, paraula, t->_pf, n);
    if (t->_c != '#')
        paraula.pop_back();
    dfs_n_simbols(paraules, paraula, t->_sg, n);
}
void dicc::print_decreixent()
{
    string s = "";
    vector<string> st;
    print(_arrel, s, st);
    bool first = true;
    cout << "size -> " << st.size() - 1 << endl;
    for (int i = 0; i < st.size(); i++)
    {
        if (first)
            first = false;
        else
            cout << ", ";
        cout << st[i];
    }
    cout << endl;
}

void dicc::print_creixent()
{
    string s = "";
    vector<string> st;
    print(_arrel, s, st);
    bool first = true;
    for (int i = st.size() - 1; i >= 0; i--)
    {
        if (first)
            first = false;
        else
            cout << ", ";
        cout << st[i];
    }
    cout << endl;
}

void dicc::print(node *n, string s, vector<string> &st)
{
    if (n != nullptr)
    {
        print(n->_pf, s + n->_c, st);
        if (n->_c == '#')
        {
            st.push_back(s);
            if (n->_sg != nullptr)
                print(n->_sg, s, st);
            return;
        }
        print(n->_sg, s, st);
    }
}