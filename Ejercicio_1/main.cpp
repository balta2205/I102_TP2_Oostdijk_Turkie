#include "Pokedex.h"

int main() {
    Pokemon squirtle("Squirtle", 100);
    PokemonInfo squirtleInfo({"Agua", "Oscuro"}, "Una tortuga pequeña que lanza chorros de agua.",
        {{"Pistola Agua", 4}, {"Hidrobomba", 6}, {"Danza Lluvia", 5}},
        {0, 400, 1000});

    Pokemon bulbasaur("Bulbasaur", 270);
    PokemonInfo bulbasaurInfo({"Planta"}, "Tiene una semilla en su lomo que crece con el tiempo",
        {{"Latigazo", 4}, {"Hoja Afilada", 6}, {"Rayo Solar", 5}},
        {0, 300, 1100});

    Pokemon charmander("Charmander", 633);
    PokemonInfo charmanderInfo({"Fuego"}, "Una lagartija con una llama en su cola.",
        {{"Ascuas", 4}, {"Lanzallamas", 6}, {"Giro Fuego", 5}},
        {0, 250, 1300});

    Pokedex pokedex;
    pokedex.agregarPokemon(squirtle, squirtleInfo);
    pokedex.agregarPokemon(bulbasaur, bulbasaurInfo);
    pokedex.agregarPokemon(charmander, charmanderInfo);

    pokedex.mostrar(squirtle); // Encontrado
    pokedex.mostrar(Pokemon("Pikachu", 390)); // No encontrado

    return 0;
}
