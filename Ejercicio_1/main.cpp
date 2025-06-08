#include "Pokedex.h"
#include "main_source.cpp"

// Librerías estándar
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include <utility>         // Para std::pair
#include <cstdlib>         // Para std::rand, std::srand
#include <ctime>           // Para std::time
#include <algorithm>       // Para std::all_of
#include <concepts>        // Para std::same_as (C++20)
#include <functional>      // Para std::hash
#include <thread>     // std::this_thread::sleep_for
#include <chrono>     // std::chrono::milliseconds

int main() {
    SystemClear();
    ImprimirConsignas(Partes::PRIMERA);

    // Ejercicio 1 Basico -> Cumple con la consigna del PDF de crear una Pokedex con 3 Pokemon y mostrar sus datos y buscar un pokemon que no esta.
    ////////////////////////////////////////////////////////////////////////////////
    Pokemon squirtle("Squirtle", 100);
    PokemonInfo squirtleInfo({"Agua", "Oscuro"}, "Una tortuga pequeña que lanza chorros de agua.",
        {{"Pistola Agua", 4}, {"Hidrobomba", 6}, {"Danza Lluvia", 5}},
        {0, 400, 1000});
    ////////////////////////////////////////////////////////////////////////////////
    Pokemon bulbasaur("Bulbasaur", 270);
    PokemonInfo bulbasaurInfo({"Planta"}, "Tiene una semilla en su lomo que crece con el tiempo",
        {{"Latigazo", 4}, {"Hoja Afilada", 6}, {"Rayo Solar", 5}},
        {0, 300, 1100});
    ////////////////////////////////////////////////////////////////////////////////
    Pokemon charmander("Charmander", 633);
    PokemonInfo charmanderInfo({"Fuego"}, "Una lagartija con una llama en su cola.",
        {{"Ascuas", 4}, {"Lanzallamas", 6}, {"Giro Fuego", 5}},
        {0, 250, 1300});
    ////////////////////////////////////////////////////////////////////////////////

    // Crear la Pokedex y agregar los Pokemon
    std::cout << "\nCreando Pokedex y agregando Pokemon..." << std::endl;
    Pokedex pokedex;
    pokedex.agregarPokemon(squirtle, squirtleInfo);
    std::cout << "Pokemon Squirtle agregado a la Pokedex." << std::endl;
    pokedex.agregarPokemon(bulbasaur, bulbasaurInfo);
    std::cout << "Pokemon Bulbasaur agregado a la Pokedex." << std::endl;
    pokedex.agregarPokemon(charmander, charmanderInfo);
    std::cout << "Pokemon Charmander agregado a la Pokedex.\n" << std::endl;

    pokedex.mostrar(squirtle); // Encontrado
    pokedex.mostrar(bulbasaur); // Encontrado
    pokedex.mostrar(charmander); // Encontrado
    pokedex.mostrar(Pokemon("Pikachu", 390)); // No encontrado

    std::cout << "\nDesea continuar con las partes adicionales? (y/n): ";
    char respuesta;
    std::cin >> respuesta;
    if (respuesta != 'y' && respuesta != 'Y') {
        std::cout << "Saliendo del programa..." << std::endl;
        return 0;
    }

    SystemClear(); // Limpia la consola antes de continuar con la parte adicional
    std::cout << "En este momento se encuentran disponibles 3 partes adicioneles de este ejercicio." << std::endl;
    std::cout << "Adicional 1: Buscar Pokemon por nombre o numero de Pokedex." << std::endl;
    std::cout << "Adicional 2: Crear tu propio equipo pokemon (6 pokemones)." << std::endl;
    std::cout << "Adicional 3: Serializar pokedex." << std::endl;

    std::cout << "Seleccione una parte adicional para continuar (1-3): ";
    int parteSeleccionada;
    std::cin >> parteSeleccionada;
    if (parteSeleccionada < 1 || parteSeleccionada > 3) {
        std::cout << "Parte seleccionada invalida. Saliendo del programa..." << std::endl;
        return 0;
    }

    switch (parteSeleccionada) {
        case 1:
            primerAdicional();
            break;
        case 2:
            ImprimirConsignas(Partes::TERCERA);
            break;
        case 3:
            ImprimirConsignas(Partes::CUARTA);
            break;
    }

    return 0;
}
