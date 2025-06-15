#include "Pokemon.h"

// Constructor con nombre y experiencia
Pokemon::Pokemon(const std::string& nombre, int experiencia) : nombre(nombre), experiencia(experiencia) {}

// Constructor con nombre, experiencia y número de Pokedex
Pokemon::Pokemon(const std::string& nombre, int experiencia, const int poke_num) 
    : nombre(nombre), experiencia(experiencia), poke_num(poke_num) {}

// Setters
void Pokemon::setExperiencia(int experiencia) {this->experiencia = experiencia;}

// Getters
const std::string& Pokemon::getNombre() const {return this->nombre;}
int Pokemon::getExperiencia() const {return this->experiencia;}
int Pokemon::getPokeNum() const {return this->poke_num;}

// Serialización del Pokémon
void Pokemon::serializar(std::ofstream& out) const {
    size_t tam_nombre = nombre.size();
    out.write(reinterpret_cast<const char*>(&tam_nombre), sizeof(tam_nombre));
    out.write(nombre.c_str(), tam_nombre);
    out.write(reinterpret_cast<const char*>(&poke_num), sizeof(poke_num));
    out.write(reinterpret_cast<const char*>(&experiencia), sizeof(experiencia));
}

// Deserialización del Pokémon
void Pokemon::deserializar(std::ifstream& in) {
    size_t tam_nombre = 0;
    in.read(reinterpret_cast<char*>(&tam_nombre), sizeof(tam_nombre));
    std::string temp_nombre(tam_nombre, '\0');
    in.read(&temp_nombre[0], tam_nombre);
    const_cast<std::string&>(nombre) = temp_nombre; // Const hack
    in.read(reinterpret_cast<char*>(const_cast<int*>(&poke_num)), sizeof(poke_num));
    in.read(reinterpret_cast<char*>(&experiencia), sizeof(experiencia));
}
