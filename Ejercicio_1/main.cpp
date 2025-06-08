#include "Pokedex.h"

#include <functional>

struct PairHash {
    std::size_t operator()(const std::pair<int, std::string>& p) const {
        std::hash<int> hashInt;
        std::hash<std::string> hashStr;
        return hashInt(p.first) ^ (hashStr(p.second) << 1); // combinación simple
    }
};

int generarDesdeExperiencia(const std::array<int, 3>& niveles) {
    // Inicializar la semilla de aleatoriedad una sola vez
    static bool inicializado = false;
    if (!inicializado) {
        std::srand(std::time(nullptr));
        inicializado = true;
    }

    // Elegir índice aleatorio entre 0 y 2
    int indice = std::rand() % 3;

    // Valor aleatorio entre 0 y el número en ese índice
    int tope = niveles[indice];
    int valor = std::rand() % (tope + 1); // +1 para incluir el tope

    return valor;
}

void leerArchivo(const std::string& rutaArchivo, Pokedex& pokedex, std::unordered_map<int, std::string>& numerosNombres) {
    // Abrir el archivo
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo: " << rutaArchivo << std::endl;
        return;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {

        std::istringstream iss(linea);
        std::string campo;
        std::vector<std::string> campos;

        while (std::getline(iss, campo, ';')) {campos.push_back(campo);}
        
        int poke_num = std::stoi(campos[0]); // Número de Pokedex
        std::string nombre = campos[1]; // Nombre del Pokemon

        // Separar los tipos por ','
        std::vector<std::string> tipos; // Vector para almacenar los tipos
        std::istringstream tiposStream(campos[2]);
        std::string tipo;
        while (std::getline(tiposStream, tipo, ',')) {tipos.push_back(tipo);}

        std::string descripcion = campos[3]; // Descripción del Pokemon
        
        std::unordered_map<std::string, int> ataques; // Mapa para almacenar los ataques y su daño
        std::istringstream todos_ataquesStream(campos[4]);
        std::string ataque;
        while (std::getline(todos_ataquesStream, ataque, ',')) {
            std::istringstream ataqueStream(ataque);
            std::string nombreAtaque;
            int fuerza;
            std::getline(ataqueStream, nombreAtaque, ':'); // Nombre del ataque
            ataqueStream >> fuerza; // Daño del ataque
            ataques[nombreAtaque] = fuerza; // Agregar al mapa
        }

        std::array<int, 3> experienciaProximoNivel; // Array para almacenar la experiencia necesaria por nivel
        std::istringstream experienciaStream(campos[5]);
        std::string experienciaNivel;
        int i = 0;
        while (std::getline(experienciaStream, experienciaNivel, ',')) {
            experienciaProximoNivel[i++] = std::stoi(experienciaNivel); // Convertir a entero y almacenar en el array
        }

        std::pair<int, std::string> evolucion; // Par para almacenar la evolución del Pokemon
        std::istringstream evolucionStream(campos[6]);
        std::string evolucionNumero, evolucionNombre;
        std::getline(evolucionStream, evolucionNumero, ','); // Número de evolución
        std::getline(evolucionStream, evolucionNombre); // Nombre de evolución
        evolucion = std::make_pair(std::stoi(evolucionNumero), evolucionNombre);

        // Generar un número aleatorio entre los límites de experiencia por nivel
        int experiencia = generarDesdeExperiencia(experienciaProximoNivel);

        // Agregar el nombre del Pokemon al mapa de números y nombres
        numerosNombres[poke_num] = nombre;

        // Crear el Pokemon y su información
        Pokemon nuevoPokemon(nombre, experiencia, poke_num);
        // Crear la información del Pokemon
        PokemonInfo nuevaInfo(tipos, descripcion, ataques, experienciaProximoNivel, evolucion);
        // Agregar el Pokemon y su información a la Pokedex
        pokedex.agregarPokemon(nuevoPokemon, nuevaInfo);
    }

    archivo.close();
}


template<typename T>
concept PokemonBuscable = std::same_as<T, std::string> || std::same_as<T, int>;

template<PokemonBuscable T>
pair<Pokemon, PokemonInfo> buscarEnPokedex(const T& pokemonBuscado){

    static Pokedex pokedex;
    static std::unordered_map<int, std::string> numerosNombres;
    static bool inicializado = false;
    if (!inicializado) {
        leerArchivo("pokemon_data.txt", pokedex, numerosNombres);
        inicializado = true;
    }

    if constexpr (std::same_as<T, int>) {
        if(pokemonBuscado < 1 || pokemonBuscado > 151) {
            std::cout << "Numero de Pokedex invalido. Debe estar entre 1 y 151." << std::endl;
            return {};
        }
        auto it = numerosNombres.find(pokemonBuscado);
        if (it == numerosNombres.end()) {
            std::cout << "Pokemon no encontrado." << std::endl;
            return {};
        }
        
    }
    else if constexpr (std::same_as<T, std::string>){

    }
}







int main() {
    Pokemon squirtle("Squirtle", 100);
    PokemonInfo squirtleInfo({"Agua", "Oscuro"}, "Una tortuga pequeña que lanza chorros de agua.",
        {{"Pistola Agua", 4}, {"Hidrobomba", 6}, {"Danza Lluvia", 5}},
        {0, 400, 1000});

    Pokemon bulbasaur("Bulbasaur", 270);
    PokemonInfo bulbasaurInfo({"Planta"}, "Tiene una semilla en su lomo que crece con el tiempo",
        {{"Latigazo", 4}, {"Hoja Afilada", 6}, {"Rayo Solar", 5}},
        {0, 300, 1100});

    Pokemon charmander("Charmander", 633);
    PokemonInfo charmanderInfo({"Fuego"}, "Una lagartija con una llama en su cola.",
        {{"Ascuas", 4}, {"Lanzallamas", 6}, {"Giro Fuego", 5}},
        {0, 250, 1300});

    Pokedex pokedex;
    pokedex.agregarPokemon(squirtle, squirtleInfo);
    pokedex.agregarPokemon(bulbasaur, bulbasaurInfo);
    pokedex.agregarPokemon(charmander, charmanderInfo);

    pokedex.mostrar(squirtle); // Encontrado
    pokedex.mostrar(Pokemon("Pikachu", 390)); // No encontrado

    std::cout << "\n\n\n\n\n==================================================================================" << std::endl;
    std::cout << "PARTE ADICIONAL: AGREGAR Y MOSTRAR CUALQUIER POKEMON DE LA PRIMERA GENERACION (1:151)" << std::endl; 
    std::cout << "==================================================================================\n\n" << std::endl;

    std::string informacion;
    // Solicitar al usuario que ingrese el nombre del Pokemon o su número de Pokedex
    std::cout << "Ingresar el nombre del Pokemon o su numero de Pokedex (1-151): " << std::endl;
    std::cin >> informacion;
    bool esNumero = !informacion.empty() && std::all_of(informacion.begin(), informacion.end(), ::isdigit);
    if (esNumero) {
        std::istringstream iss(informacion);
        int numero;
        iss >> numero;
        buscarEnPokedex(numero);
    } else {
        buscarEnPokedex(informacion);
    }

    return 0;
}
