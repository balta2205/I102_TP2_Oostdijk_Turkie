#include "Pokedex.h"
#include "../utilities.h"

enum class Partes {PRIMERA, SEGUNDA, TERCERA, CUARTA};

void ImprimirConsignas(Partes parte) { // Imprime las consignas del ejercicio dependiendo de la parte seleccionada
    switch (parte) {
        case Partes::PRIMERA:
            std::cout << "============================================================================================================================" << std::endl;
            std::cout << "EJERCICIO 1: POKEDEX" << std::endl;
            std::cout << "============================================================================================================================" << std::endl;
            std::cout << "PARTE BASICA: CREAR UNA POKEDEX, INSERTAR 3 POKEMONES, BUSCARLOS E IMPRIMIRLOS EN PANTALLA." << std::endl;
            std::cout << "============================================================================================================================" << std::endl;
            std::cout << "Esta resolucion consta de varias partes:" << std::endl;
            std::cout << "1. La primera parte es la resolucion basica del ejercicio 1, donde se crea una Pokedex con 3 Pokemon y se muestran sus datos." << std::endl;
            std::cout << "   La misma se ejecutara automaticamente al iniciar el programa." << std::endl;
            std::cout << "============================================================================================================================" << std::endl;
            break;
        case Partes::SEGUNDA:
            std::cout << "============================================================================================================================" << std::endl;
            std::cout << "EJERCICIO 1: POKEDEX" << std::endl;
            std::cout << "============================================================================================================================" << std::endl;
            std::cout << "PARTE ADICIONAL 1: MOSTRAR CUALQUIER POKEMON DE LA PRIMERA GENERACION (1:151)" << std::endl; 
            std::cout << "============================================================================================================================" << std::endl;
            std::cout << "Esta parte del ejercicio permite buscar cualquier Pokemon de la primera generacion (1-151) por su nombre o numero de Pokedex." << std::endl;
            std::cout << "El programa cargara los datos de un archivo de texto llamado pokemon_data.txt." << std::endl;
            std::cout << "============================================================================================================================" << std::endl;
            break;
        case Partes::TERCERA:
            std::cout << "Parte 3: Buscar Pokemon por nombre o numero de Pokedex." << std::endl;
            break;
        case Partes::CUARTA:
            std::cout << "============================================================================================================================" << std::endl;
            std::cout << "EJERCICIO 1: POKEDEX" << std::endl;
            std::cout << "============================================================================================================================" << std::endl;
            std::cout << "PARTE ADICIONAL 3: CREAR UN EQUIPO POKEMON, EL USUARIO INGRESA POKEMONES, Y PUEDE EVOLUCIONARLOS." << std::endl;
            std::cout << "============================================================================================================================" << std::endl;
            std::cout << "Esta parte del ejercicio permite al usuario crear su propio equipo de 6 pokemones y, una vez ingresados, evolucionarlos." << std::endl;
            std::cout << "============================================================================================================================" << std::endl;
            break;
    }
}

void SystemClear() { // Limpia la consola dependiendo del sistema operativo
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void mostrarBarraDeCargaConPorcentaje(int pasos = 50, int tiempo = 100) { // Muestra una barra de carga con porcentaje
    std::cout << "Cargando Pokedex:\n";
    std::cout << "[";

    for (int i = 0; i <= pasos; ++i) {
        int porcentaje = (i * 100) / pasos;

        // Mostrar barra parcial
        std::cout << "#";
        std::cout.flush(); // Evita el salto de línea

        // Mostrar porcentaje al lado (solo al final de línea)
        std::cout << "\r[" << std::string(i, '#') << std::string(pasos - i, ' ') << "] "; // Muestra la barra de carga
        std::cout << porcentaje << "%";
        std::cout.flush(); // Evita el salto de línea

        std::this_thread::sleep_for(std::chrono::milliseconds(tiempo)); // Espera un tiempo determinado antes de continuar
    }
    std::cout << "\n" << std::endl;
}

int generarDesdeExperiencia(const std::array<int, 3>& niveles) { // Genera un número aleatorio de experiencia desde los niveles dados
    // Inicializar la semilla de aleatoriedad una sola vez
    static bool inicializado = false;
    if (!inicializado) {
        std::srand(std::time(nullptr));
        inicializado = true;
    }

    // Elegir índice aleatorio entre 0 y 2
    int indice = std::rand() % 3;

    // Valor aleatorio entre 0 y el número en ese índice
    int tope = niveles[indice];
    int valor = std::rand() % (tope + 1); // +1 para incluir el tope

    return valor;
}

std::pair<Pokemon, PokemonInfo> leerLinea(const std::string& linea) { // Leer una línea del archivo txt
    std::istringstream iss(linea);
    std::string campo;
    std::vector<std::string> campos;

    // Separar los campos por ';'
    while (std::getline(iss, campo, ';')) {campos.push_back(campo);}

    // Verificar que la línea tenga al menos 7 campos
    if (campos.size() < 7) {throw std::runtime_error("Línea malformada en el archivo CSV.");}

    // Número de Pokedex y nombre
    int poke_num = std::stoi(campos[0]);
    std::string nombre = campos[1];

    // Tipos
    std::vector<std::string> tipos;
    std::istringstream tiposStream(campos[2]);
    std::string tipo;
    while (std::getline(tiposStream, tipo, ',')) {
        tipos.push_back(tipo);
    }

    // Descripción
    std::string descripcion = campos[3];

    // Ataques
    std::unordered_map<std::string, int> ataques;
    std::istringstream todos_ataquesStream(campos[4]);
    std::string ataque;
    while (std::getline(todos_ataquesStream, ataque, ',')) {
        if (ataque.empty()) continue;
        std::istringstream ataqueStream(ataque);
        std::string nombreAtaque;
        int fuerza;
        std::getline(ataqueStream, nombreAtaque, ':');
        ataqueStream >> fuerza;
        ataques[nombreAtaque] = fuerza;
    }

    // Experiencia por nivel
    std::array<int, 3> experienciaProximoNivel;
    std::istringstream experienciaStream(campos[5]);
    std::string experienciaNivel;
    int i = 0;
    while (std::getline(experienciaStream, experienciaNivel, ',')) {
        experienciaProximoNivel[i++] = std::stoi(experienciaNivel);
    }

    // Evolución
    std::pair<int, std::string> evolucion;
    std::istringstream evolucionStream(campos[6]);
    std::string evolucionNumero, evolucionNombre;
    std::getline(evolucionStream, evolucionNumero, ',');
    std::getline(evolucionStream, evolucionNombre);
    evolucion = std::make_pair(std::stoi(evolucionNumero), evolucionNombre);

    // Generar experiencia aleatoria
    int experiencia = generarDesdeExperiencia(experienciaProximoNivel);

    // Crear el Pokemon y su información
    Pokemon pokemon(nombre, experiencia, poke_num);
    PokemonInfo info(tipos, descripcion, ataques, experienciaProximoNivel, evolucion);

    return std::make_pair(pokemon, info);
}

// Lee un archivo de texto con datos de Pokemon y los agrega a la Pokedex
void leerArchivo(const std::string& rutaArchivo, Pokedex& pokedex, std::unordered_map<int, std::pair<std::string, int>>& numerosNombres) {
    // Abrir el archivo
    std::ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) { // Si no se puede abrir el archivo, mostrar un mensaje de error
        SystemClear();
        std::cerr << "Error al abrir el archivo: " << rutaArchivo << std::endl;
        return;
    }

    std::string linea;
    while (std::getline(archivo, linea)) { // Leer cada línea del archivo
        auto [pokemon, info] = leerLinea(linea);
        pokedex.agregarPokemon(pokemon, info);
        numerosNombres[pokemon.getPokeNum()] = {pokemon.getNombre(), pokemon.getExperiencia()};
    }

    archivo.close();
    return;
}

template<typename T>
concept PokemonBuscable = std::same_as<T, std::string> || std::same_as<T, int>;

template<PokemonBuscable T>
// Busca un Pokemon en la Pokedex por nombre o número de Pokedex
std::pair<Pokemon, PokemonInfo> buscarEnPokedex(const T& pokemonBuscado, const Pokedex& pokedex_completa, const std::unordered_map<int, std::pair<std::string, int>>& numerosNombres) { 
    if constexpr (std::is_same_v<T, std::string>){ // Si el tipo es string, se busca por nombre
        for (const auto& [key, value] : numerosNombres){
            if (pokemonBuscado == value.first) {
                Pokemon pokemonEncontrado(value.first, value.second, key); // Crea un Pokemon con el nombre, experiencia y número de Pokedex
                pokedex_completa.mostrar(pokemonEncontrado); // Muestra el Pokemon encontrado
                return std::make_pair(pokemonEncontrado, pokedex_completa.getPokemonInfo(pokemonEncontrado)); // Retorna el Pokemon encontrado y su información
            }
        }
    }
    else if constexpr (std::is_same_v<T, int>) { // Si el tipo es int, se busca por número de Pokedex
        numerosNombres.find(pokemonBuscado); // Verifica si el número de Pokedex existe en el mapa
        // Si el número de Pokedex existe, se crea un Pokemon con el nombre, experiencia y número de Pokedex y se retorna junto con su información
        if (numerosNombres.find(pokemonBuscado) != numerosNombres.end()) {
            const auto& [nombre, experiencia] = numerosNombres.at(pokemonBuscado); 
            Pokemon pokemonEncontrado(nombre, experiencia, pokemonBuscado); // Crea un Pokemon con el nombre, experiencia y número de Pokedex
            pokedex_completa.mostrar(pokemonEncontrado); // Muestra el Pokemon encontrado
            return std::make_pair(pokemonEncontrado, pokedex_completa.getPokemonInfo(pokemonEncontrado)); // Retorna el Pokemon encontrado y su información
        }
    }
    return std::make_pair(Pokemon("", 0), PokemonInfo()); // Retorna un Pokemon vacío si no se encuentra
}

std::pair<Pokemon, PokemonInfo> buscarEnPokedex(Pokemon& pokemonBuscado){ // Buscar la evolucion de un Pokemon en el txt
    std::ifstream archivo("datos_pokemones.txt");

    if (!archivo.is_open()) { // Si no se puede abrir el archivo, mostrar un mensaje de error
        SystemClear();
        std::cerr << "Error al abrir el archivo: datos_pokemones.txt" << std::endl;
        return std::make_pair(Pokemon("", 0), PokemonInfo());
    }

    std::string linea;
    while (std::getline(archivo, linea)){
        if (linea.empty()) continue; // Si la línea está vacía, saltarla
        std::istringstream iss(linea);
        std::string campo;
        std::vector<std::string> campos;

        while (std::getline(iss, campo, ';')) {campos.push_back(campo);} // Separar los campos por ';'

        // Evolución
        std::pair<int, std::string> evolucion;
        std::istringstream evolucionStream(campos[6]);
        std::string evolucionNumero, evolucionNombre;
        std::getline(evolucionStream, evolucionNumero, ',');
        std::getline(evolucionStream, evolucionNombre);
        evolucion = std::make_pair(std::stoi(evolucionNumero), evolucionNombre);

        // Si el pokemon no tiene evolucion, se descarta la posibilidad de evolucionar
        if((pokemonBuscado.getNombre() == campos[1]) && (std::stoi(evolucionNumero) == 0)){
            archivo.close();
            return std::make_pair(Pokemon("", 0), PokemonInfo());
        }

        // Si el numero de pokedex de la evolucion del Pokemon no coincide con el numero de pokedex del pokemon actual aumentado en 1, continuar con la siguiente línea
        if (std::stoi(campos[0]) != (pokemonBuscado.getPokeNum() + 1)) {continue;} 

        auto [pokemon_evolucion, info_evolucion] = leerLinea(linea); // Leer la línea y obtener el Pokemon y su información

        archivo.close();
        return std::make_pair(pokemon_evolucion, info_evolucion);
    }
    archivo.close();
    return std::make_pair(Pokemon("", 0), PokemonInfo()); // Retorna un Pokemon vacío si no se encuentra
}

// Concepto que restringe el tipo T a que sea int o std::string
template<typename T>
concept EntradaValida = std::same_as<T, int> || std::same_as<T, std::string>;

// Función genérica que lee un dato desde la entrada estándar.
// Puede usarse para leer enteros o cadenas de texto.
// Parámetros:
// - mensaje: texto que se muestra al usuario como prompt
// - pide_tipos_ataques: si es true y el tipo es string, permite aceptar cadenas vacías
// - min, max: límites para validación de números enteros
template<EntradaValida T>
T leerDato(const std::string& mensaje, bool pide_tipos_ataques = false, int min = std::numeric_limits<int>::min(), int max = std::numeric_limits<int>::max()) {
    std::string input;

    while (true) {
        std::cout << mensaje;
        std::getline(std::cin, input);

        if constexpr (std::same_as<T, int>) { // Si el tipo T es int, se intenta convertir la entrada a entero
            try {
                int valor = std::stoi(input);

                if (valor < min || valor > max) { // Verifica que el número esté dentro del rango permitido
                    std::cout << "El número debe estar entre " << min << " y " << max << ".\n";
                    continue;
                }

                return valor; // Si es válido, lo retorna
            } 
            catch (const std::invalid_argument&) {std::cout << "Entrada inválida. Ingrese un número entero.\n";} 
            catch (const std::out_of_range&) {std::cout << "Número fuera de rango.\n";}
        } 
        else { // Si el tipo T es string
            if (pide_tipos_ataques && input.empty()) {return "";} // Permite string vacío solo si se está pidiendo un tipo o ataque opcional

            if (input.empty()) {std::cout << "El texto no puede estar vacío.\n";} 

            else {return input;}
        }
    }
}


void evolucion(Pokedex& pokedex) { // Función para evolucionar Pokémon
    SystemClear();
    std::cout << "===========================================================================================================================================================" << std::endl;
    std::cout << "DESCUBRIMIENTO DE ULTIMO MINUTO: LOS CIENTIFICOS HAN DESCUBIERTO UNA POCION QUE LE OTORGA EXPERIENCIA A LOS POKEMONES RESULTANDO EN EVOLUCIONES ESPONTANEAS"  << std::endl;
    std::cout << "===========================================================================================================================================================" << std::endl;

    auto mapa = pokedex.getPokedex();

    while(true){
    
        std::cout << "Desea utilizar la pocion para evolucionar a sus Pokemon? (y/n): ";
        char respuesta;
        std::cin >> respuesta;
        if (respuesta != 'y' && respuesta != 'Y') {
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

        std::cout << "Ingrese el numero del Pokemon que desea evolucionar, solo se puede usar la pocion un pokemon a la vez: ";
        int numeroPokemon;
        std::cin >> numeroPokemon;

        // Validar la entrada del usuario
        if (numeroPokemon < 1 || numeroPokemon > contador - 1) { // Si el número ingresado no es válido, se sale del programa
            std::cout << "Numero de Pokemon invalido. Saliendo del programa..." << std::endl;
            return;
        }

        auto it = mapa.begin();
        std::advance(it, numeroPokemon - 1); // Avanzar el iterador hasta el Pokémon seleccionado
        Pokemon pokemonSeleccionado = it->first; // Obtener el Pokémon seleccionado
        std::cout << "Pokemon seleccionado: " << pokemonSeleccionado.getNombre() << std::endl;
        auto [pokemonEvolucion, infoEvolucion] = buscarEnPokedex(pokemonSeleccionado);
        if (pokemonEvolucion.getNombre().empty()) {
            std::cout << "El Pokemon seleccionado ya se encuentra en su forma final o simplemente no tiene evolucion. Si desea puede volver a elegir." << std::endl;
            continue;
        }
        SystemClear();
        mapa.erase(it->first); // Eliminar el Pokémon seleccionado del mapa
        mapa[pokemonEvolucion] = infoEvolucion; // Agregar la evolución al mapa 

        std::cout << "El Pokemon " << pokemonSeleccionado.getNombre() << " esta EVOLUCIONANDO a " << pokemonEvolucion.getNombre() << "!\n" << std::endl;
    }
}

void primerAdicional(){ // Función para la primera parte adicional del ejercicio

    SystemClear(); // Limpia la consola antes de continuar con la parte adicional
    ImprimirConsignas(Partes::SEGUNDA); // Imprime las consignas de la parte adicional
    
    std::cout << "\nDesea crear la Pokedex Maestra (contiene los 151 Pokemones)? (y/n): ";
    char respuesta;
    std::cin >> respuesta;
    if (respuesta != 'y' && respuesta != 'Y') {
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

    char response;
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
        std::cout << "Desea seguir agregando pokemones? (y/n): ";
        std::cin >> response;
        std::cout << std::endl;
        if (response != 'y' && response != 'Y'){
            std::cout << "Saliendo del programa..." << std::endl; // Si el usuario no desea seguir agregando Pokemon, se sale del programa
            return;
        }
        SystemClear();
    }
}

void tercerAdicional() { // Función para la tercera parte adicional del ejercicio
    SystemClear();    

    Pokedex pokedexCompleta;
    std::unordered_map<int, std::pair<std::string, int>> numerosNombres; // Mapa para almacenar los números y nombres de los Pokemon
    leerArchivo("datos_pokemones.txt", pokedexCompleta, numerosNombres); // Leer el archivo de datos de los Pokemon y cargar los datos en la Pokedex

    Pokedex pokedexUsuario; // Crear una Pokedex para el usuario

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorar el salto de línea previo
    std::string continuar = leerDato<std::string>("¿Desea agregar un Pokémon a su equipo? (y/n): ");
    if (continuar != "y" && continuar != "Y") {
        std::cout << "Saliendo del programa..." << std::endl; // Si el usuario no desea agregar Pokémon, se sale del programa
        return;
    }

    int contador = 6;
    char response;
    std::string informacion;
    while(contador > 0) { // Permite agregar hasta 6 Pokémon
        SystemClear();
        std::cout << "============================================================================================================================" << std::endl;
        std::cout << "Espacios disponibles en el equipo: " << contador << std::endl;
        std::cout << "============================================================================================================================\n" << std::endl;

        // Solicitar al usuario que ingrese el nombre del Pokemon o su número de Pokedex
        std::cout << "Ingresar el nombre del Pokemon o su numero de Pokedex (1-151): ";
        std::cin >> informacion;
        std::cout << std::endl;
        bool esNumero = !informacion.empty() && std::all_of(informacion.begin(), informacion.end(), ::isdigit);

        if(esNumero){// Si la información ingresada es un número, se convierte a entero
            // Validar que el número esté dentro del rango de la primera generación (1-151)
            int poke_num = std::stoi(informacion);
            if (poke_num < 1 || poke_num > 151) {
                std::cout << "Numero de Pokedex invalido. Debe estar entre 1 y 151." << std::endl;
                continue;
            }

            std::pair<Pokemon, PokemonInfo> resultado = buscarEnPokedex(poke_num, pokedexCompleta, numerosNombres);
            std::cout << "Pokemon encontrado: " << resultado.first.getNombre() << std::endl;
            pokedexUsuario.agregarPokemon(resultado.first, resultado.second);
        }
        else{ // Si la información ingresada es un nombre, se busca por nombre
            std::pair<Pokemon, PokemonInfo> resultado = buscarEnPokedex(informacion, pokedexCompleta, numerosNombres);
            if (resultado.first.getNombre().empty()) {
                std::cout << "Pokemon no encontrado." << std::endl;
                continue;
            }
            std::cout << "Pokemon encontrado: " << resultado.first.getNombre() << std::endl; // Muestra el nombre del Pokemon encontrado
            pokedexUsuario.agregarPokemon(resultado.first, resultado.second);
        }

        contador--;
        std::cout << "============================================================================================================================\n" << std::endl;
        std::cout << "Desea seguir agregando pokemones? (y/n): ";
        std::cin >> response;
        std::cout << std::endl;
        if (response != 'y' && response != 'Y'){break;}
    }
    SystemClear();
    std::cout << "============================================================================================================================" << std::endl;
    std::cout << "Equipo Final Elegido" << std::endl;
    std::cout << "============================================================================================================================" << std::endl;
    pokedexUsuario.mostrarTodos();

    std::cout << "\n\n============================================================================================================================" << std::endl;
    std::cout << "Los cientificos han hecho un avance tecnologico. (EVOLUCIONES)" << std::endl;
    std::cout << "============================================================================================================================" << std::endl;

    std::cout << "Desea evolucionar algun pokemon? (y/n): ";
    std::cin >> response;
    std::cout << std::endl;
    if (response != 'y' && response != 'Y'){
        std::cout << "Saliendo del programa..." << std::endl; // Si el usuario no desea evolucionar ningun Pokemon, se sale del programa
        return;
    }

    evolucion(pokedexUsuario);

    std::cout << "Estas listo para admirar tu equipo final evolucionado? (Ingresar cualquier tecla para continuar): ";
    std::cin >> response;
    std::cout << std::endl;

    SystemClear();
    std::cout << "============================================================================================================================" << std::endl;
    std::cout << "Equipo Final Evolucionado" << std::endl;
    std::cout << "============================================================================================================================" << std::endl;
    pokedexUsuario.mostrarTodos(); // Muestra el equipo final evolucionado
    return;
}
