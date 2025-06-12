#ifndef POKEMONINFO_H
#define POKEMONINFO_H

#include "../../utilities.h"

class PokemonInfo {
private:
    std::vector<std::string> tipos; // Decidimos usar un vector porque pueden tener dos tipos diferentes
    std::string descripcion; // Descripción del Pokémon
    std::unordered_map<std::string, int> ataquesDisponiblesPorNivel; // Almacena ataques por nombre y daño
    std::array<int, 3> experienciaProximoNivel = {0, 0, 0}; // Experiencia necesaria por nivel: [nivel 1, 2, 3]
    std::pair<int, std::string> evolucion = {0, ""}; // Par que almacena el número de evolución y el nombre del Pokémon al que evoluciona

public:
    // Constructor
    PokemonInfo() = default;
    // Constructor con parametros
    PokemonInfo(const std::vector<std::string>& tipos, const std::string& descripcion, const std::unordered_map<std::string, int>& ataquesDisponiblesPorNivel, const std::array<int, 3>& experienciaProximoNivel);
    // Contructor parametros y con evolución
    PokemonInfo(const std::vector<std::string>& tipos, const std::string& descripcion, const std::unordered_map<std::string, int>& ataquesDisponiblesPorNivel, const std::array<int, 3>& experienciaProximoNivel, const std::pair<int, std::string>& evolucion);

    ~PokemonInfo() = default; // Destructor

    // Getters
    const std::vector<std::string>& getTipos() const ;
    const std::string& getDescripcion() const ;
    const std::unordered_map<std::string, int>& getAtaquesDisponiblesPorNivel() const ;
    const std::array<int, 3>& getExperienciaProximoNivel() const ;
    const std::pair<int, std::string>& getEvolucion() const ;
};

#endif // POKEMONINFO_H
