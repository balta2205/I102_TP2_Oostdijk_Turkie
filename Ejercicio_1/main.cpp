#include "Pokedex.h"
#include "../utilities.h"
#include "main_source.cpp"



int main() {
    SystemClear(); // Limpia la terminal
    ImprimirConsignas(Partes::PRIMERA); // Imprime la consigna basica del ejercicio

    // Ejercicio 1: Basico -> Cumple con la consigna del PDF de crear una Pokedex con 3 Pokemon y mostrar sus datos y buscar un pokemon que no esta.
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

    // Preguntar al usuario si desea continuar con las partes adicionales
    std::cout << "\nDesea continuar con las partes adicionales? (y/n): ";
    char respuesta;
    std::cin >> respuesta;
    if (respuesta != 'y' && respuesta != 'Y') {
        std::cout << "Saliendo del programa..." << std::endl; // Si el usuario no desea continuar, se sale del programa
        return 0;
    }

    SystemClear(); // Limpia la consola antes de continuar con la parte adicional
    std::cout << "En este momento se encuentran disponibles 3 partes adicionales de este ejercicio." << std::endl;
    std::cout << "      Adicional 1: Buscar Pokemon por nombre o numero de Pokedex en la POKEDEX MAESTRA." << std::endl;
    std::cout << "      Adicional 2: Serializar pokedex (Serializa la Pokedex basica del la Parte Basica)." << std::endl;
    std::cout << "      Adicional 3: Crear tu propio equipo pokemon (6 pokemones), luego los serializa." << std::endl;

    // Seleccionar una parte adicional para continuar
    std::cout << "\nSeleccione una parte adicional para continuar (1-3): ";
    int parteSeleccionada;
    std::cin >> parteSeleccionada;
    if (parteSeleccionada < 1 || parteSeleccionada > 3) {
        std::cout << "Parte seleccionada invalida. Saliendo del programa..." << std::endl; // Si la parte seleccionada no es valida, se sale del programa
        return 0;
    }

    // Switch para ejecutar la parte adicional seleccionada
    switch (parteSeleccionada) {
        case 1:
            primerAdicional(); // Llama a la funcion del primer adicional de Pokedex Maestra
            break;
        case 2:
            ImprimirConsignas(Partes::TERCERA);
            break;
        case 3:
            tercerAdicional(); // Llama a la funcion del tercer adicional donde el usuario agrega Pokemons manualmente
            break;
    }

    return 0;
}
