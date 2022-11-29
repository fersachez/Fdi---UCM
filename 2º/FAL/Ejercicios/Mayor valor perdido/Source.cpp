#include<iostream>

using namespace std;

int mayor_perdido(int v[], int a, int b) {
    int r;

    if(a + 1 == b) r = v[b] - 1;
    else {
        int m = (a + b) / 2;

        if (v[b] - v[m] > b - m) {
            r = mayor_perdido(v, m, b);
        }
        else {
            r = mayor_perdido(v, a, m);
        }
    }

    return r;
}

bool resuelve() {
    // leer datos
    int n;
    cin >> n;
    if (n == 0)
        return false;  // final de entrada -> terminar

    int v[1000];
    for (int i = 0; i < n; ++i)
        cin >> v[i];

    // calcular solución
    int total = mayor_perdido(v, 0, n - 1);

    // escribir solución
    cout << total << endl;

    return true; // seguir procesando más casos
}

int main() {
    while (resuelve())
        ;
}
