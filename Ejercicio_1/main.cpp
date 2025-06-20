#include "Pokedex.h"
#include "../utilities.h"
#include "main_source.cpp"



int main() {
    SystemClear(); // Limpia la terminal
    
    if ( confirmarAccion("Desea cargar los ultimos datos de la pokedex basica? (si es que se encuentran)") ) {
        cuartoAdicional(); // Si el usuario no desea cargar los datos, se llama a la funcion del cuarto adicional 
    }
    else {
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
        Pokedex pokedex("pokedex_basica.dat");
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
    }
    // Preguntar al usuario si desea continuar con las partes adicionales
    if (!confirmarAccion("\nDesea continuar con las partes adicionales?")) {
        std::cout << "Saliendo del programa..." << std::endl; // Si el usuario no desea continuar, se sale del programa
        return 0;
    }

    SystemClear(); // Limpia la consola antes de continuar con la parte adicional
    std::cout << "En este momento se encuentran disponibles 3 partes adicionales de este ejercicio." << std::endl;
    std::cout << "      Adicional 1: Buscar Pokemon por nombre o numero de Pokedex en la POKEDEX MAESTRA." << std::endl;
    std::cout << "      Adicional 2: Crear tu propio equipo pokemon (6 pokemones), luego los serializa." << std::endl;
    std::cout << "==(ADICIONALES DE DESERIALIZAR)=======================================================================================================" << std::endl;
    std::cout << "      Adicional 3: Cargar equipo previamente guardado desde archivo binario 'equipo_final.dat', y opcion de agregar pokemones al mismo" << std::endl;
    
    // Seleccionar una parte adicional para continuar
    int parteSeleccionada = leerDato<int>("\nSeleccione una parte adicional para continuar (1-3): ", false, 1, 5);

    // Switch para ejecutar la parte adicional seleccionada
    switch (parteSeleccionada) {
        case 1:
            primerAdicional(); // Llama a la funcion del primer adicional 
            break;
        case 2:
            segundoAdicional(); // Llama a la funcion del segundo adicional 
            break;
        case 3:
            tercerAdicional(); // Llama a la funcion del tercer adicional
            break;
    }

    return 0;
}
