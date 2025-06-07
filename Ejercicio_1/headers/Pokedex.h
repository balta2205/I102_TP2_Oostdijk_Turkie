#ifndef POKEDEX_H
#define POKEDEX_H

#include <unordered_map>
#include <iostream>
#include "Pokemon.h"
#include "PokemonInfo.h"

class Pokedex {
private:
    std::unordered_map<Pokemon, PokemonInfo> informacion;

public:
    // Constructor y Destructor
    Pokedex();
    Pokedex(const std::unordered_map<Pokemon, PokemonInfo>& informacion);
    ~Pokedex() = default;

    // Métodos
    void agregarPokemon(const Pokemon& pokemon, const PokemonInfo& info);
    void imprimirInformacion(const Pokemon& pokemon) const;
};

class PokemonHash {
public:
    size_t operator()(const Pokemon& pokemon) const;
};

#endif // POKEDEX_H
