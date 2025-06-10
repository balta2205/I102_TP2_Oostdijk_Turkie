#include "ControlAeronaves.h"	

#include "../utilities.h"

int main() {
    cout << "============================================" << endl;

    ControlAeronaves control;
    auto inicio = chrono::high_resolution_clock::now();
    control.PruebaDeVuelo();
    auto fin = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> duracion = fin - inicio;
    cout << "============================================" << endl;
    cout << "Todos los drones volaron en " << duracion.count() / 1000 << " segundos" << endl;
    cout << "============================================" << endl;
    return 0;
}