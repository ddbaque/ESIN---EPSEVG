#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

void ordena_per_fusio(vector<double>& v);
void sort(vector<double>&left, vector<double>& right, vector<double>& bars);

int main()
{
    cout << fixed << setprecision(1);
    int n;
    while (cin >> n) {
        vector<double> v(n);
        for (int i = 0; i < n; ++i) {
            cin >> v[i];
        }
        ordena_per_fusio(v);
        for (int i = 0; i < n; ++i) {
            cout << " " << v[i];
        }
        cout << endl;
    }
    return 0;
}

void ordena_per_fusio(vector<double> & bar) {
    if (bar.size() <= 1) return;

    int mid = bar.size() / 2;
    vector<double> left;
    vector<double> right;

    for (size_t j = 0; j < mid;j++)
        left.push_back(bar[j]);
    for (size_t j = 0; j < (bar.size()) - mid; j++)
        right.push_back(bar[mid + j]);

    ordena_per_fusio(left);
    ordena_per_fusio(right);
    sort(left, right, bar);
}
void sort(vector<double>&left, vector<double>& right, vector<double>& bars)
{
    int nL = left.size();
    int nR = right.size();
    int i = 0, j = 0, k = 0;

    while (j < nL && k < nR) 
    {
        if (left[j] < right[k]) {
            bars[i] = left[j];
            j++;
        }
        else {
            bars[i] = right[k];
            k++;
        }
        i++;
    }
    while (j < nL) {
        bars[i] = left[j];
        j++; i++;
    }
    while (k < nR) {
        bars[i] = right[k];
        k++; i++;
    }
}