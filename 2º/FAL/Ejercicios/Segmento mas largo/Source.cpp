#include <iostream>

using namespace std;

// P = { 0 <= n <= long(v) && n <= 100000 && PARATODO k : 0 <= k <n : v[k] <= 10^9 && v[k] >= -10^9 }
int tamSegmentoMaximo(int v[], int n) {
    int i = 0;
    int j = 0;
    int tAct = 0;
    int tMax = 0;
    // Inv = 
    // Cota: n - j
    while (j < n) { 
        if (v[i] == v[j]) {
            tAct++;
            if (tAct > tMax) tMax = tAct;
            j++;
        }
        else {
            i = j;
            tAct = 0;
        }
    }

    return tMax;
}

// Q = { tMax = MAX a, b : 0 <= a <= b < n && v[a] = v[b] : (b - a + 1) } 

/*
 * Devuelve un valor booleano indicando si se ha detectado el marcador de final de entrada.
 */
bool resuelve() {
    // leer datos
    int n;
    cin >> n;
    if (n == 0)
        return false;  // final de entrada -> terminar

    int v[100000];
    for (int i = 0; i < n; ++i)
        cin >> v[i];

    // calcular solución
    int total = tamSegmentoMaximo(v, n);

    // escribir solución
    cout << total << endl;

    return true; // seguir procesando más casos
}

int main() {
    while (resuelve())
        ;
}
