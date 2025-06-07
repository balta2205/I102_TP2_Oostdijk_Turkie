#ifndef POKEMON_H
#define POKEMON_H

#include <string>

class Pokemon {
private: 
    const std::string nombre;
    int experiencia;

public:
    // Constructor y destructor
    Pokemon() = default; // Constructor por defecto
    Pokemon(const std::string& nombre, int experiencia); // Constructor con parámetros

    ~Pokemon() = default; // Destructor por defecto
    
    // Sobrecarga del operador == para poder usar los objetos pokemones como key del unordered_map de la pokedex
    bool operator==(const Pokemon& other) const {return this->nombre == other.nombre && this->experiencia == other.experiencia;}

    // Setters.
    void setExperiencia(int experiencia);

    // Getters.
    const std::string& getNombre() const;
    int getExperiencia() const;
};

#endif // POKEMON_H