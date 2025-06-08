#include "Pokedex.h"

// Constructor
Pokedex::Pokedex(const std::unordered_map<Pokemon, PokemonInfo, PokemonHash>& informacion)
    : informacion(informacion) {}

// Método para agregar un Pokemon y su información a la Pokedex
void Pokedex::agregarPokemon(const Pokemon& pokemon, const PokemonInfo& info) {
    informacion[pokemon] = info;
}

void Pokedex::mostrar(const Pokemon& pokemon) const {
    auto it = informacion.find(pokemon); // Instanciacion de un iterador para buscar el pokemon en la Pokedex
    // Si el pokemon no se encuentra en la Pokedex, el iterador apuntará al final del mapa.
    // Si se encuentra, it apuntará al elemento correspondiente.
    if (it != informacion.end()) {
        std::string nombre = it->first.getNombre(); // Obtengo el nombre del pokemon
        int experiencia = it->first.getExperiencia(); // Obtengo la experiencia del pokemon
        const PokemonInfo& info = it->second; // Obtengo la informacion del pokemon
        std::cout << "============================================================================================================================" << std::endl;

        // Printeo del nombre del pokemon
        std::cout << "Nombre: " << nombre << std::endl;

        // Printeo de la experiencia del pokemon
        std::array<int, 3> experienciaProximoNivel = info.getExperienciaProximoNivel();

        // Calculo del nivel del pokemon basado en la experiencia
        int nivel_pokemon = 1; // Inicializo el nivel del pokemon en 1, si sobrepasa los limites de experiencia, se incrementará el nivel
        if (experiencia > experienciaProximoNivel[1]) nivel_pokemon = 2;
        if (experiencia > experienciaProximoNivel[2]) nivel_pokemon = 3;

        // Printeo del nivel del pokemon
        std::cout << "Nivel: " << nivel_pokemon << std::endl;

        // Printeo de la experiencia del pokemon
        std::cout << "Experiencia: " << experiencia << std::endl;
        
        // Printeo de la descripcion del pokemon
        std::cout << "Descripcion: " << info.getDescripcion() << std::endl;

        // Printeo de los tipos del pokemon
        std::cout << "Tipos: ";
        const auto& tipos = info.getTipos();
        for (const auto& tipo : tipos) { 
            if (tipo == tipos.back()) {
                std::cout << tipo; // Evita la coma al final del último tipo
                continue;
            }
            std::cout << tipo << ", ";
        }
        std::cout << std::endl;

        // Printeo de ataques disponibles
        std::cout << "Ataques disponibles:" << std::endl;
        // Itero sobre el mapa de ataques disponibles por nivel, donde el iterador es un par de clave-valor con el nombre del ataque y su daño.
        const auto& ataquesDisponibles = info.getAtaquesDisponiblesPorNivel();
        for (const auto& ataque : ataquesDisponibles) std::cout << "    " << ataque.first << ": " << ataque.second << " de daño" << std::endl;

        std::cout << "Experiencia para cada Nivel: " << std::endl;
        // Printeo de la experiencia necesaria para cada nivel
        std::cout << "    Nivel 1: " << experienciaProximoNivel[0] << " de experiencia" << std::endl;
        std::cout << "    Nivel 2: " << experienciaProximoNivel[1] << " de experiencia" << std::endl;
        std::cout << "    Nivel 3: " << experienciaProximoNivel[2] << " de experiencia" << std::endl;
        std::cout << "============================================================================================================================" << std::endl;

    } else {
        // Si el pokemon no se encuentra en la Pokedex (el iterador apunta al final del mapa), se imprime un mensaje de error.
        std::cout << "============================================================================================================================" << std::endl;
        std::cout << "¡Pokemon desconocido! El pokemon " << pokemon.getNombre() << " no se encuentra en la Pokedex." << std::endl;
        std::cout << "============================================================================================================================" << std::endl; 
    }
}

size_t PokemonHash::operator()(const Pokemon& pokemon) const {
    return std::hash<std::string>()(pokemon.getNombre()); // Utiliza el nombre del Pokemon como base para el hash
}

void Pokedex::mostrarTodos() const {
    for (const auto& par : informacion) { // Itero sobre el mapa de informacion, donde el iterador es un par de clave-valor con el Pokemon y su informacion.
        std::cout << "============================================================================================================================" << std::endl;
        mostrar(par.first);
        std::cout << "============================================================================================================================" << std::endl;
    }
}

PokemonInfo Pokedex::getPokemonInfo(const Pokemon& pokemon) const {
        auto it = informacion.find(pokemon);
        if (it != informacion.end()) {
            return it->second; // Retorna la información del Pokémon si se encuentra
        }
        throw std::runtime_error("Pokemon no encontrado en la Pokedex."); // Lanza una excepción si el Pokémon no se encuentra
    }