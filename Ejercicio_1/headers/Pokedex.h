#ifndef POKEDEX_H
#define POKEDEX_H

#include <unordered_map>
#include <iostream>
#include "Pokemon.h"
#include "PokemonInfo.h"

class PokemonHash {
public:
    size_t operator()(const Pokemon& pokemon) const;
};

class Pokedex {
private:
    std::unordered_map<Pokemon, PokemonInfo, PokemonHash> informacion;

public:
    // Constructor y Destructor
    Pokedex() = default; // Constructor por defecto
    Pokedex(const std::unordered_map<Pokemon, PokemonInfo, PokemonHash>& informacion);
    ~Pokedex() = default;

    // Métodos
    void agregarPokemon(const Pokemon& pokemon, const PokemonInfo& info);
    void mostrar(const Pokemon& pokemon) const;
    void mostrarTodos() const;
};


#endif // POKEDEX_H
