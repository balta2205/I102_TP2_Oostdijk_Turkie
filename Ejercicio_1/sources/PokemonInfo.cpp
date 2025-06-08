#include "PokemonInfo.h"

// Constructor
PokemonInfo::PokemonInfo(const std::vector<std::string>& tipos, const std::string& descripcion, const std::unordered_map<std::string, int>& ataquesDisponiblesPorNivel, const std::array<int, 3>& experienciaProximoNivel) :
    tipos(tipos),
    descripcion(descripcion),
    ataquesDisponiblesPorNivel(ataquesDisponiblesPorNivel),
    experienciaProximoNivel(experienciaProximoNivel) {}

PokemonInfo::PokemonInfo(const std::vector<std::string>& tipos, const std::string& descripcion, const std::unordered_map<std::string, int>& ataquesDisponiblesPorNivel, const std::array<int, 3>& experienciaProximoNivel, const std::pair<int, std::string>& evolucion) :
    tipos(tipos),
    descripcion(descripcion),
    ataquesDisponiblesPorNivel(ataquesDisponiblesPorNivel),
    experienciaProximoNivel(experienciaProximoNivel),
    evolucion(evolucion) {}

// Getters
const std::vector<std::string>& PokemonInfo::getTipos() const {return this->tipos;}
const std::string& PokemonInfo::getDescripcion() const {return this->descripcion;}
const std::unordered_map<std::string, int>& PokemonInfo::getAtaquesDisponiblesPorNivel() const {return this->ataquesDisponiblesPorNivel;}
const std::array<int, 3>& PokemonInfo::getExperienciaProximoNivel() const {return this->experienciaProximoNivel;}
const std::pair<int, std::string>& PokemonInfo::getEvolucion() const {return this->evolucion;}