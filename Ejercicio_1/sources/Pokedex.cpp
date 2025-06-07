#include "Pokedex.h"

Pokedex::Pokedex(const std::unordered_map<Pokemon, PokemonInfo, PokemonHash>& informacion)
    : informacion(informacion) {}

void Pokedex::agregarPokemon(const Pokemon& pokemon, const PokemonInfo& info) {
    informacion[pokemon] = info;
}

void Pokedex::mostrar(const Pokemon& pokemon) const {
    auto it = informacion.find(pokemon);
    if (it != informacion.end()) {
        std::string nombre = it->first.getNombre();
        int experiencia = it->first.getExperiencia();
        const PokemonInfo& info = it->second;

        std::cout << "Nombre: " << nombre << std::endl;
        std::cout << "Experiencia: " << experiencia << std::endl;
        std::cout << "Tipo: " << info.getTipo() << std::endl;
        std::cout << "Descripcion: " << info.getDescripcion() << std::endl;

        std::cout << "Ataques disponibles por nivel:" << std::endl;
        const auto& ataquesDisponibles = info.getAtaquesDisponiblesPorNivel();
        for (const auto& ataque : ataquesDisponibles) {
            std::cout << "  " << ataque.first << ": " << ataque.second << " de daño" << std::endl;
        }

        std::array<int, 3> experienciaProximoNivel = info.getExperienciaProximoNivel();
        int nivel_pokemon = 1;
        if (experiencia > experienciaProximoNivel[1]) {
            nivel_pokemon = 2;
        }
        if (experiencia > experienciaProximoNivel[2]) {
            nivel_pokemon = 3;
        }

        std::cout << "Nivel:" << nivel_pokemon << std::endl;
    } else {
        std::cout << "¡Pokemon desconocido!" << std::endl;
    }
}

size_t PokemonHash::operator()(const Pokemon& pokemon) const {
    return std::hash<std::string>()(pokemon.getNombre());
}

void Pokedex::mostrarTodos() const {
    for (const auto& par : informacion) {
        mostrar(par.first);
        std::cout << "-----------------------------" << std::endl;
    }
}