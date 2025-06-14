#ifndef POKEDEX_H
#define POKEDEX_H

#include "Pokemon.h"
#include "PokemonInfo.h"
#include "../../utilities.h"

class PokemonHash {
public:
    // Utiliza el nombre del Pokemon como base para el hash
    size_t operator()(const Pokemon& pokemon) const {return std::hash<std::string>()(pokemon.getNombre());}
};

class Pokedex {
private:
    // Mapa que almacena la información de los Pokémon, donde la clave es el Pokémon y el valor es su información
    // Utilizamos un unordered_map para un acceso rápido a la información de los Pokémon a traves de un hasheo que usa el nombre del Pokémon como base.
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
    PokemonInfo getPokemonInfo(const Pokemon& pokemon) const;
    std::unordered_map<Pokemon, PokemonInfo, PokemonHash> getPokedex() const;
};


#endif // POKEDEX_H
