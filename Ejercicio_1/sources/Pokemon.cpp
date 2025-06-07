#include "Pokemon.h"

// Constructor.
Pokemon::Pokemon(const std::string& nombre, int experiencia) : nombre(nombre), experiencia(experiencia) {}

// Setters.
void Pokemon::setExperiencia(int experiencia) {this->experiencia = experiencia;}

// Getters.
const std::string& Pokemon::getNombre() const {return this->nombre;}
int Pokemon::getExperiencia() const {return this->experiencia;}