#include "../utilities.h"

using namespace std;

// Genera un número aleatorio entre min y max
int getRandom(int min, int max) {
    return min + rand() % (max - min + 1);
}

struct Tarea {
    int idSensor;               // Identificador del sensor que generó la tarea
    int idTarea;                // Identificador único de la tarea
    std::string descripcionTarea; // Descripción de la tarea
};

// Variables compartidas entre hilos
queue<Tarea> tareas;                  // Cola centralizada de tareas
mutex tareas_mtx;                     // Mutex para sincronizar el acceso a la cola
condition_variable tareas_cv;        // Variable de condición para que los robots esperen hasta que haya tareas
int num_serie = 0;                    // Contador global de IDs de tarea
int cant_sensores_terminados = 0;     // Contador de sensores que ya terminaron su trabajo
const int TOTAL_SENSORES = 3;         // Cantidad total de sensores (constante para control)

// Función que representa a un sensor
void sensor(int idSensor) {
    int cant_tareas = getRandom(1, 10); // Decide aleatoriamente cuántas tareas va a generar este sensor

    for (int i = 0; i < cant_tareas; i++) {
        this_thread::sleep_for(chrono::milliseconds(175)); // Espera 175 ms antes de generar una nueva tarea
        unique_lock<mutex> lock(tareas_mtx); 

        int idTarea = num_serie++;
        std::string descripcionTarea = "Tarea generada por sensor " + to_string(idSensor) + " con id " + to_string(idTarea);
        tareas.push(Tarea{idSensor, idTarea, descripcionTarea}); // Encola la nueva tarea
        cout << "[SENSOR " << idSensor << "] Generó tarea " << idTarea << endl;

        tareas_cv.notify_one(); // Notifica a un robot que hay una nueva tarea disponible
    }

    // Una vez que el sensor termina de generar tareas, informa que terminó    
    unique_lock<mutex> lock(tareas_mtx); // Protección para modificar el contador
    cant_sensores_terminados++;          // Aumenta el contador de sensores finalizados
    if(cant_sensores_terminados == TOTAL_SENSORES){
        tareas_cv.notify_all();          // Notifica a todos los robots por si están esperando y deben terminar
    }
    cout << "[SENSOR " << idSensor << "] Ha terminado de generar tareas. Total tareas generadas: " << cant_tareas << endl;
}

// Función que representa a un robot
void robot(int idRobot) {
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(250)); // Simula el procesamiento de la tarea
        unique_lock<mutex> lock(tareas_mtx); 

        // Espera hasta que haya una tarea o todos los sensores hayan terminado
        tareas_cv.wait(lock, [] {return !tareas.empty() || cant_sensores_terminados == TOTAL_SENSORES;});

        // Si la cola está vacía y ya no hay sensores activos, el robot puede terminar
        if (tareas.empty() && cant_sensores_terminados == TOTAL_SENSORES) {
            cout << "[ROBOT " << idRobot << "] No hay más tareas ni sensores activos. Finaliza.\n";
            break; 
        }

        if (!tareas.empty()) {
            Tarea actual = tareas.front(); 
            tareas.pop(); // Elimina la tarea de la cola                   
            cout << "[ROBOT " << idRobot << "] Procesando tarea " << actual.idTarea << " del sensor " << actual.idSensor << endl;

            lock.unlock(); // Libera el mutex antes de dormir para no bloquear a otros hilos            
        }
    }
}

// === Función principal ===
int main() {
    srand(time(NULL)); // Inicializa la semilla para números aleatorios

    vector<thread> sensores; // Vector para almacenar los threads de los sensores
    vector<thread> robots; // Vector para almacenar los threads de los robots

    for (int i = 0; i < TOTAL_SENSORES; i++) {sensores.push_back(thread(sensor, i));}

    for (int i = 0; i < 3; i++) {robots.push_back(thread(robot, i));}

    // Espera que finalicen todos los threads
    for (auto& t : sensores) t.join();
    for (auto& t : robots) t.join();

    cout << "Todos los sensores y robots finalizaron correctamente." << endl;
    return 0;
}
