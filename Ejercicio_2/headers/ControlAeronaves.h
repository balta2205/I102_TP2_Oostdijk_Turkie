#ifndef CONTROLAERONAVES_H
#define CONTROLAERONAVES_H

#include "../../utilities.h"

using namespace std;

enum class EstadoDron {Preparado, Despegando, Volando};

class ControlAeronaves {
private:
    vector<thread> drones; // Hilos para cada dron	
    array<mutex, 5> areas; // Mutexes para cada área
    mutex log_mutex; // Mutex para el log de mensajes

public:
    // En nuestras pruebas iniciales, se crean los 5 drones y todos despegan en un tiempo de alrededor de 15 segundos
    void PruebaDeVuelo();
    void logMessage(int id, EstadoDron estadoDron); // Método para registrar mensajes de estado de los drones
    void Despegar(int id);
};

#endif // CONTROLAERONAVES_H