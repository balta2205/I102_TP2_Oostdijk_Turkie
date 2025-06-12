#include "ControlAeronaves.h"	

#include "../utilities.h"

int main() {
    cout << "============================================" << endl;

    ControlAeronaves control;
    auto inicio = chrono::high_resolution_clock::now(); // Inicio del cronómetro
    control.PruebaDeVuelo(); // Llamada al método que controla el vuelo de los drones
    auto fin = chrono::high_resolution_clock::now(); // Fin del cronómetro

    chrono::duration<double, milli> duracion = fin - inicio; // Calcula la duración en milisegundos
    cout << "============================================" << endl;
    cout << "Todos los drones volaron en " << duracion.count() / 1000 << " segundos" << endl;
    cout << "============================================" << endl;
    return 0;
}