#ifndef POKEMON_H
#define POKEMON_H

#include "../../utilities.h"

class Pokemon {
private: 
    const std::string nombre; // Nombre del Pokémon, se define como constante para que no pueda ser modificado una vez creado
    int experiencia; // Experiencia del Pokémon, se puede modificar a través de un setter, sirve para evolucionar o subir de nivel
    const int poke_num = 0; // Número de Pokedex del Pokémon, se define como constante para que no pueda ser modificado una vez creado
public:
    // Constructor y destructor
    Pokemon() = default; // Constructor por defecto
    Pokemon(const std::string& nombre, int experiencia); // Constructor con nombre y experiencia
    Pokemon(const std::string& nombre, int experiencia, const int poke_num); // Constructor con parámetros

    ~Pokemon() = default; // Destructor por defecto
    
    // Sobrecarga del operador == para poder usar los objetos pokemones como key del unordered_map de la pokedex
    bool operator==(const Pokemon& other) const {return this->nombre == other.nombre && this->experiencia == other.experiencia;}

    // Setters.
    void setExperiencia(int experiencia);

    // Getters.
    const std::string& getNombre() const;
    int getExperiencia() const;
    int getPokeNum() const; 
};

#endif // POKEMON_H