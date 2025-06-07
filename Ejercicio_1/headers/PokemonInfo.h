#ifndef POKEMONINFO_H
#define POKEMONINFO_H

#include <string>
#include <unordered_map>
#include <array>

class PokemonInfo {
private:
    const std::string tipo;
    const std::string descripcion;
    const std::unordered_map<std::string, int> ataquesDisponiblesPorNivel; // Unordered_map para almacenar ataques con key y value, ventaja para buscar rapido el ataque por key, no me interesa que los ataques esten ordenados. Pero si me interesa que cuando se busque un ataque por key saber si el pokemon conoce el ataque o no.
    const std::array<int, 3> experienciaProximoNivel = {0, 0, 0}; // Array para almacenar la experiencia necesaria para subir de nivel, en el orden: [nivel 1, nivel 2, nivel 3]

public:
    // Constructor y Destructor
    PokemonInfo() = default;
    PokemonInfo(const std::string& tipo, const std::string& descripcion, const std::unordered_map<std::string, int>& ataquesDisponiblesPorNivel, const std::array<int, 3>& experienciaProximoNivel);
    
    ~PokemonInfo() = default;

    // Getters
    const std::string& getTipo() const;
    const std::string& getDescripcion() const;
    const std::unordered_map<std::string, int>& getAtaquesDisponiblesPorNivel() const;
    const std::array<int, 3>& getExperienciaProximoNivel() const;
};

#endif // POKEMONINFO_H