#ifndef CONTROLAERONAVES_H
#define CONTROLAERONAVES_H

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <fstream>
#include <array>
#include <chrono>

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
    void logMessage(int id, EstadoDron estadoDron);
    void Despegar(int id);
};

#endif // CONTROLAERONAVES_H