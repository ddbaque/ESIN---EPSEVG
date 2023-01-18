#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <string>
using namespace std;
typedef unsigned int nat;

template <typename Elem, typename Prio>
class CuaPrio
{
public:
    // Constructora, crea una cua buida.
    CuaPrio();

    // Tres grans.
    CuaPrio(const CuaPrio &p);
    CuaPrio &operator=(const CuaPrio &p);
    ~CuaPrio() throw();

    // Afegeix l'element x amb prioritat p a la cua de prioritat.
    void insereix(const Elem &x, const Prio &p);

    // Retorna un element de mínima prioritat en la cua de prioritat. Llança un error si la cua és buida.
    Elem min() const;

    // Retorna la mínima prioritat present en la cua de prioritat. Llança un error si la cua és buida.
    Prio prio_min() const;

    // Elimina un element de mínima prioritat de la cua de prioritat. Llança un error si la cua és buida.
    void elim_min();

    // Retorna cert si i només si la cua és buida.
    bool es_buida() const throw();

    // Retorna el número de elements
    nat n_elements();

    // Mostra per consola la cua
    void print();

    static const int CuaPrioBuida = 320;

private:
    nat _nelems;                 // Nombre d'elements en el heap.
    vector<pair<Elem, Prio>> _h; // Vector de pair d'Elem i Prio. La component 0 no s'usa.

    void enfonsar(nat p) throw();
    void surar(nat p) throw();
};

template <typename Elem, typename Prio>
CuaPrio<Elem, Prio>::CuaPrio() : _nelems(0)
{
    Elem x;
    Prio p;
    _h.push_back(make_pair(x, p));
}

template <typename Elem, typename Prio>
CuaPrio<Elem, Prio>::CuaPrio(const CuaPrio &p) : _nelems(p._nelems), _h(p._h)
{
}

template <typename Elem, typename Prio>
CuaPrio<Elem, Prio> &CuaPrio<Elem, Prio>::operator=(const CuaPrio &p)
{
    _nelems = p._nelems;
    _h = p._h;
    return *this;
}

template <typename Elem, typename Prio>
CuaPrio<Elem, Prio>::~CuaPrio() throw()
{
}

template <typename Elem, typename Prio>
void CuaPrio<Elem, Prio>::insereix(const Elem &x, const Prio &p)
{
    _h.push_back(make_pair(x, p));
    ++_nelems;
    surar(_nelems);
}

template <typename Elem, typename Prio>
Elem CuaPrio<Elem, Prio>::min() const
{
    if (_nelems == 0)
        throw CuaPrioBuida;
    return _h[1].first;
}

template <typename Elem, typename Prio>
Prio CuaPrio<Elem, Prio>::prio_min() const
{
    if (_nelems == 0)
        throw CuaPrioBuida;
    return _h[1].second;
}

template <typename Elem, typename Prio>
void CuaPrio<Elem, Prio>::elim_min()
{
    if (_nelems == 0)
        throw CuaPrioBuida;
    swap(_h[1], _h[_nelems]);
    _h.pop_back();
    --_nelems;
    enfonsar(1);
}

template <typename Elem, typename Prio>
bool CuaPrio<Elem, Prio>::es_buida() const throw()
{
    return _nelems == 0;
}

// Enfonsa al node j-èssim fins a restablir l’ordre del monticle a _h; els subarbres del node j són heaps.
template <typename Elem, typename Prio>
void CuaPrio<Elem, Prio>::enfonsar(nat j) throw()
{
    if (j <= _nelems)
    {
        nat i = j;
        while (i+1 <= _nelems-1)
        {
            if (_h[i].second <= _h[i + 1].second)
            {
                swap(_h[i], _h[i + 1]);
                i++;
            }
            else
                break;
        }
    }
}

// Fa surar el node p-èssim fins a restablir l’ordre del monticle; tots els nodes excepte el p-èssim satisfan la propietat 3.
template <typename Elem, typename Prio>
void CuaPrio<Elem, Prio>::surar(nat p) throw()
{
    nat q;
    bool fi = false;
    while (p > 1 and not fi)
    {
        q = p / 2;
        if (_h[q].second < _h[p].second)
        {
            swap(_h[p], _h[q]);
            p = q;
        }
        else
        {
            fi = true;
        }
    }
}

template <typename Elem, typename Prio>
nat CuaPrio<Elem, Prio>::n_elements()
{
    return _nelems;
}

template <typename Elem, typename Prio>
void CuaPrio<Elem, Prio>::print()
{
    bool first = true;
    while (!es_buida())
    {
        cout << " " << min();
        elim_min();
    }
    cout << endl;
}

enum Rango
{
    soldat = 1,
    sergent,
    capita,
    coronel
};

Rango str_to_rang(const string &s)
{
    if (s == "soldat")
        return Rango::soldat;
    else if (s == "sergent")
        return Rango::sergent;
    else if (s == "capita")
        return Rango::capita;
    else
        return Rango::coronel;
}

int main()
{
    int n;
    cin >> n;
    vector<CuaPrio<string, Rango>> v_cues(n);
    queue<string> cua_names;

    for (int i = -1; i < n; i++)
    {
        string line;
        getline(cin, line);
        if (i != -1)
        {
            CuaPrio<string, Rango> cua;
            if (line.empty())
                v_cues[i] = cua;
            else
            {
                string name;
                string rang;
                istringstream iss(line);
                while (iss >> name >> rang)
                {
                    cua.insereix(name, str_to_rang(rang));
                }
                v_cues[i] = cua;
            }
        }
    }
    string line;
    getline(cin, line);
    while (true)
    {
        string line;
        getline(cin, line);
        if (line.empty())
            break;
        string comanda, name;
        string rang;
        int n_cua;
        istringstream iss(line);
        iss >> comanda;
        if (comanda == "SURT")
        {
            iss >> n_cua;
            if (n_cua > 0 && n_cua <= n)
            {
                if (!v_cues[n_cua - 1].es_buida())
                {
                    cua_names.push(v_cues[n_cua - 1].min());
                    v_cues[n_cua - 1].elim_min();
                }
            }
        }
        else if (comanda == "ENTRA")
        {
            iss >> name >> rang >> n_cua;
            if (n_cua > 0 && n_cua <= n)
            {
                v_cues[n_cua - 1].insereix(name, str_to_rang(rang));
            }
        }
    }
    cout << "SORTIDES" << endl;
    cout << "--------" << endl;
    while (!cua_names.empty())
    {
        cout << cua_names.front() << endl;
        cua_names.pop();
    }
    cout << endl;
    cout << "CONTINGUTS FINALS" << endl;
    cout << "-----------------" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "cua " << i + 1 << ":";
        v_cues[i].print();
    }
}
