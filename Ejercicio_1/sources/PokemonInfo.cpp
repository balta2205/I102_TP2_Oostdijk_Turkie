#include "PokemonInfo.h"

// Constructor
PokemonInfo::PokemonInfo(const std::string& tipo, const std::string& descripcion, const std::unordered_map<std::string, int>& ataquesDisponiblesPorNivel, const std::array<int, 3>& experienciaProximoNivel) :
    tipo(tipo),
    descripcion(descripcion),
    ataquesDisponiblesPorNivel(ataquesDisponiblesPorNivel),
    experienciaProximoNivel(experienciaProximoNivel) {}

// Getters
    const std::string& PokemonInfo::getTipo() const {return this->tipo;}
    const std::string& PokemonInfo::getDescripcion() const {return this->descripcion;}
    const std::unordered_map<std::string, int>& PokemonInfo::getAtaquesDisponiblesPorNivel() const {return this->ataquesDisponiblesPorNivel;}
    const std::array<int, 3>& PokemonInfo::getExperienciaProximoNivel() const {return this->experienciaProximoNivel;}