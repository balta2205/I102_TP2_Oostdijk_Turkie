#ifndef POKEMONINFO_H
#define POKEMONINFO_H

#include <string>
#include <unordered_map>
#include <array>

class PokemonInfo {
private:
    std::string tipo;
    std::string descripcion;
    std::unordered_map<std::string, int> ataquesDisponiblesPorNivel; // Almacena ataques por nombre y daño
    std::array<int, 3> experienciaProximoNivel = {0, 0, 0}; // Experiencia necesaria por nivel: [nivel 1, 2, 3]

public:
    // Constructor y Destructor
    PokemonInfo() = default;
    PokemonInfo(const std::string& tipo, const std::string& descripcion, const std::unordered_map<std::string, int>& ataquesDisponiblesPorNivel, const std::array<int, 3>& experienciaProximoNivel);

    ~PokemonInfo() = default;

    // Getters
    const std::string& getTipo() const ;
    const std::string& getDescripcion() const ;
    const std::unordered_map<std::string, int>& getAtaquesDisponiblesPorNivel() const ;
    const std::array<int, 3>& getExperienciaProximoNivel() const ;
};

#endif // POKEMONINFO_H
