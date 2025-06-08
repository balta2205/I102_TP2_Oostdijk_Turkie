#include "Pokemon.h"

// Constructor
Pokemon::Pokemon(const std::string& nombre, int experiencia) : nombre(nombre), experiencia(experiencia) {}
Pokemon::Pokemon(const std::string& nombre, int experiencia, const int poke_num) 
    : nombre(nombre), experiencia(experiencia), poke_num(poke_num) {}

// Setters
void Pokemon::setExperiencia(int experiencia) {this->experiencia = experiencia;}

// Getters
const std::string& Pokemon::getNombre() const {return this->nombre;}
int Pokemon::getExperiencia() const {return this->experiencia;}
int Pokemon::getPokeNum() const {return this->poke_num;}