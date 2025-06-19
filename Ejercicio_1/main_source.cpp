#include "Pokedex.h"
#include "../utilities.h"
#include "funciones.cpp"

// Función para la primer parte adicional del ejercicio (mostrar cualquier Pokémon de la primera generación)
void primerAdicional(){ 

    SystemClear(); // Limpia la consola antes de continuar con la parte adicional
    ImprimirConsignas(Partes::SEGUNDA); // Imprime las consignas de la parte adicional
    
    if (!confirmarAccion("\nDesea crear la Pokedex Maestra (contiene los 151 Pokemones)")) {
        std::cout << "Saliendo del programa..." << std::endl; // Si el usuario no desea crear la Pokedex Maestra, se sale del programa
        return;
    }

    std::cout << "\n============================================================================================================================" << std::endl;
    std::cout << "Creando Pokedex y cargando datos de todos los Pokemon..." << std::endl;

    Pokedex pokedexCompleta; // Crear una Pokedex para almacenar todos los Pokemon
    std::unordered_map<int, std::pair<std::string, int>> numerosNombres; // Mapa para almacenar los números y nombres de los Pokemon
    mostrarBarraDeCargaConPorcentaje(); // Mostrar barra de carga con 50 pasos y 50 ms por paso
    
    leerArchivo("datos_pokemones.txt", pokedexCompleta, numerosNombres); // Leer el archivo de datos de los Pokemon y cargar los datos en la Pokedex

    std::cout << "Pokedex creada con exito! Ahora puede buscar cualquier Pokemon de la primera generacion (1-151)." << std::endl;
    std::cout << "============================================================================================================================" << std::endl;

    std::string informacion;
    while(true){
        // Solicitar al usuario que ingrese el nombre del Pokemon o su número de Pokedex
        std::cout << "Ingresar el nombre del Pokemon o su numero de Pokedex (1-151): ";
        std::cin >> informacion;
        bool esNumero = !informacion.empty() && std::all_of(informacion.begin(), informacion.end(), ::isdigit);
        if (esNumero){ // Si la información ingresada es un número, se convierte a entero
            // Validar que el número esté dentro del rango de la primera generación (1-151)
            int poke_num = std::stoi(informacion);
            if (poke_num < 1 || poke_num > 151) {
                std::cout << "Numero de Pokedex invalido. Debe estar entre 1 y 151." << std::endl;
                continue;
            }
            std::pair<Pokemon, PokemonInfo> resultado = buscarEnPokedex(poke_num, pokedexCompleta, numerosNombres);
            std::cout << "Pokemon encontrado: " << resultado.first.getNombre() << std::endl;
        }
        else{ // Si la información ingresada es un nombre, se busca por nombre
            std::pair<Pokemon, PokemonInfo> resultado = buscarEnPokedex(informacion, pokedexCompleta, numerosNombres);
            if (resultado.first.getNombre().empty()) {
                std::cout << "Pokemon no encontrado." << std::endl;
                continue;
            }
            std::cout << "Pokemon encontrado: " << resultado.first.getNombre() << std::endl; // Muestra el nombre del Pokemon encontrado
        }

        std::cout << "============================================================================================================================\n" << std::endl;
        
        if (!confirmarAccion("Desea seguir buscando pokemones?")){
            std::cout << "Saliendo del programa..." << std::endl; // Si el usuario no desea seguir agregando Pokemon, se sale del programa
            return;
        }
        SystemClear();
    }
}

// Función para evolucionar Pokémon
std::unordered_map<Pokemon, PokemonInfo, PokemonHash> evolucion(Pokedex& pokedex) { 
    SystemClear();
    std::cout << "===========================================================================================================================================================" << std::endl;
    std::cout << "DESCUBRIMIENTO DE ULTIMO MINUTO: LOS CIENTIFICOS HAN DESCUBIERTO UNA POCION QUE LE OTORGA EXPERIENCIA A LOS POKEMONES RESULTANDO EN EVOLUCIONES ESPONTANEAS"  << std::endl;
    std::cout << "===========================================================================================================================================================" << std::endl;

    auto mapa = pokedex.getPokedex();

    while(true){

        if (!confirmarAccion("Desea utilizar la pocion para evolucionar a sus Pokemon?")) {
            std::cout << "Terminando evoluciones..." << std::endl; // Si el usuario no desea utilizar la poción, se sale del bucle
            break;
        }

        std::cout << "============================================================================================================================" << std::endl;
        std::cout << "Sus pokemones disponibles son:\n";
        int contador = 1;
        for(const auto& [pokemon, informacion] : mapa) { // Muestra todos los Pokémon disponibles en la Pokedex
            std::cout << "    " << contador++ << ". " << pokemon.getNombre() << " (Nro. Pokedex: " << pokemon.getPokeNum() << ", Experiencia: " << pokemon.getExperiencia() << ")" << std::endl;
        }
        std::cout << "============================================================================================================================" << std::endl;

        int numeroPokemon = leerDato<int>("Ingrese el numero del Pokemon que desea evolucionar, solo se puede usar la pocion un pokemon a la vez: ", false, 1, contador - 1);

        auto it = mapa.begin();
        std::advance(it, numeroPokemon - 1); // Avanzar el iterador hasta el Pokémon seleccionado
        Pokemon pokemonSeleccionado = it->first; // Obtener el Pokémon seleccionado
        std::cout << "Pokemon seleccionado: " << pokemonSeleccionado.getNombre() << std::endl;
        auto [pokemonEvolucion, infoEvolucion] = buscarEnPokedexEvolucion(pokemonSeleccionado);

        if (pokemonEvolucion.getNombre().empty()) {
            std::cout << "El Pokemon seleccionado ya se encuentra en su forma final o simplemente no tiene evolucion. Si desea puede volver a elegir." << std::endl;
            continue;
        }

        SystemClear();
        mapa.erase(it->first); // Eliminar el Pokémon seleccionado del mapa
        mapa[pokemonEvolucion] = infoEvolucion; // Agregar la evolución al mapa 

        std::cout << "El Pokemon " << pokemonSeleccionado.getNombre() << " esta EVOLUCIONANDO a " << pokemonEvolucion.getNombre() << "!\n" << std::endl;
    }
    return mapa;
}

// Función para la segunda parte adicional del ejercicio (Crear un equipo de Pokémon, evolucionarlos y guardarlos en un archivo binario)
void segundoAdicional() {
    SystemClear();
    ImprimirConsignas(Partes::TERCERA); // Imprime las consignas de la parte adicional
    Pokedex pokedexCompleta;
    std::unordered_map<int, std::pair<std::string, int>> numerosNombres; // Mapa para almacenar los números y nombres de los Pokemon
    leerArchivo("datos_pokemones.txt", pokedexCompleta, numerosNombres); // Leer el archivo de datos de los Pokemon y cargar los datos en la Pokedex

    Pokedex pokedexUsuario; // Crear una Pokedex para el usuario

    if (!confirmarAccion("¿Desea agregar un Pokémon a su equipo?")) {
        std::cout << "Saliendo del programa..." << std::endl; // Si el usuario no desea agregar Pokémon, se sale del programa
        return;
    }

    armarEquipoPokemon(pokedexUsuario, pokedexCompleta, numerosNombres, 6); // Permite al usuario armar un equipo de Pokémon
    
    SystemClear();
    std::cout << "============================================================================================================================" << std::endl;
    std::cout << "Equipo Final Elegido" << std::endl;
    std::cout << "============================================================================================================================" << std::endl;
    pokedexUsuario.mostrarTodos();

    if (pokedexUsuario.getPokedex().size() == 6) {
        std::cout << "\nNo quedan espacios disponibles en el equipo." << std::endl;
    }

    std::cout << "\n============================================================================================================================" << std::endl;
    std::cout << "Los cientificos han hecho un avance tecnologico. (EVOLUCIONES)" << std::endl;
    std::cout << "============================================================================================================================" << std::endl;

    if (!confirmarAccion("Desea evolucionar algun pokemon?")) {
        pokedexUsuario.serializar("equipo_final.dat"); // Serializa el equipo final del usuario
        std::cout << "Saliendo del programa..." << std::endl; // Si el usuario no desea evolucionar ningun Pokemon, se sale del programa
        return;
    }

    std::unordered_map<Pokemon, PokemonInfo, PokemonHash> mapa = evolucion(pokedexUsuario);
    Pokedex pokedex_terminada(mapa);

    confirmarAccion("Estas listo para admirar tu equipo final evolucionado? (Ingresar cualquier tecla para continuar)");

    SystemClear();
    std::cout << "============================================================================================================================" << std::endl;
    std::cout << "Equipo Final Evolucionado" << std::endl;
    std::cout << "============================================================================================================================" << std::endl;
    pokedex_terminada.mostrarTodos(); // Muestra el equipo final evolucionado
    pokedex_terminada.serializar("equipo_final.dat"); // Serializa el equipo final evolucionado

    return;
}

// Función para la tercera parte adicional del ejercicio (cargar equipo desde un archivo binario y agregar pokemones)
void tercerAdicional() {
    SystemClear();
    ImprimirConsignas(Partes::CUARTA); // Imprime las consignas de la parte adicional
    std::string archivo = "equipo_final.dat";

    Pokedex pokedexCompleta;
    std::unordered_map<int, std::pair<std::string, int>> numerosNombres; // Mapa para almacenar los números y nombres de los Pokemon
    leerArchivo("datos_pokemones.txt", pokedexCompleta, numerosNombres); // Leer el archivo de datos de los Pokemon y cargar los datos en la Pokedex

    Pokedex pokedex(archivo);
    pokedex.deserializar(archivo);

    std::cout << "\nMostrando el equipo cargado desde '" << archivo << "':\n" << std::endl;
    pokedex.mostrarTodos();

    if (pokedex.getPokedex().size() == 6) {
        std::cout << "============================================================================================================================" << std::endl;
        std::cout << "No quedan espacios disponibles en el equipo." << std::endl;
        std::cout << "Saliendo del programa..." << std::endl; // Si ya no queda espacio en el equipo, se sale del programa
        return;
    }

    if (!confirmarAccion("¿Desea agregar un Pokémon a su equipo?")) {
        std::cout << "Saliendo del programa..." << std::endl; // Si el usuario no desea agregar Pokémon, se sale del programa
        return;
    }
    armarEquipoPokemon(pokedex, pokedexCompleta, numerosNombres, 6-pokedex.getPokedex().size()); // Permite al usuario continuar agregando pokemones a su equipo
}

// Función para la cuarta parte adicional del ejercicio (cargar Pokedex básica desde un archivo binario)
void cuartoAdicional() {
    SystemClear();
    ImprimirConsignas(Partes::QUINTA); // Imprime las consignas de la parte adicional
    std::string archivo = "pokedex_basica.dat";

    Pokedex pokedex;
    std::cout << "\nMostrando la Pokedex básica cargada desde '" << archivo << "':\n" << std::endl;
    pokedex.deserializar(archivo);


    pokedex.mostrarTodos();
}
