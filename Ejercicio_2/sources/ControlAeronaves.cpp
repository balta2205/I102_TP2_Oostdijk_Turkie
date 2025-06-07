#include "ControlAeronaves.h"

void ControlAeronaves::PruebaDeVuelo(){
    for(int i = 0; i < 5; i++) // Crea 5 drones
        drones.emplace_back(thread(&ControlAeronaves::Despegar, this, i));

    for (auto& drone : drones) // Espera a que todos los drones terminen
        if (drone.joinable()) drone.join(); // Se usa joinable para evitar errores si el hilo ya ha terminado o si intenta hacer join en un hilo que no existe
}

void ControlAeronaves::logMessage(int id, EstadoDron estadoDron) {
        lock_guard<mutex> lock(log_mutex); // Bloquea el mutex para evitar condiciones de carrera, se desbloquea automáticamente al salir del scope
        switch (estadoDron) {
            case EstadoDron::Preparado: {
                cout << "Dron " << id << " esperando para despegar..." << endl;
                break; 
            }
            case EstadoDron::Despegando: {
                cout << "Dron " << id << " despegando..." << endl;
                break; 
            }
            case EstadoDron::Volando: {
                cout << "Dron " << id << " alcanzó altura de 10m" << endl;
                break;
            }
        }    
    } 

void ControlAeronaves::Despegar(int id){
        logMessage(id, EstadoDron::Preparado); // Log de que el dron está preparado para despegar

        while(true) {
            unique_lock<mutex> lock1(areas[id], defer_lock); // Evita el bloqueo inmediato
            unique_lock<mutex> lock2(areas[(id + 1) % 5], defer_lock); // Modulo 5 para el caso borde del ultimo dron

            if(try_lock(lock1, lock2) == -1) {
                logMessage(id, EstadoDron::Despegando); // Log de que el dron está despegando
                this_thread::sleep_for(chrono::seconds(5)); // Simula el tiempo que demora el dron en llegar a 10 metros
                break;
            } 
            else {this_thread::sleep_for(chrono::milliseconds(50));} // Espera antes de intentar nuevamente
        } 

        logMessage(id, EstadoDron::Volando); // Log de que el dron ha alcanzado la altura de 10 metros
    }