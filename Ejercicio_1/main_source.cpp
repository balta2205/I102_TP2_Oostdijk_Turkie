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
            std::cout << "PARTE ADICIONAL 3: CREAR UNA POKEDEX, EL USUARIO INGRESA POKEMONES, Y SERIALIZA LOS DATOS." << std::endl;
            std::cout << "============================================================================================================================" << std::endl;
            std::cout << "Esta parte del ejercicio permite al programa cargar/serializar los datos a un archivo .bin llamado pokedex_serializada.bin." << std::endl;
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
        if (linea.empty()) continue; // Si la línea está vacía, saltarla
        std::istringstream iss(linea);
        std::string campo;
        std::vector<std::string> campos;

        while (std::getline(iss, campo, ';')) {campos.push_back(campo);} // Separar los campos por ';'
        
        int poke_num = std::stoi(campos[0]); // Número de Pokedex
        std::string nombre = campos[1]; // Nombre del Pokemon

        // Separar los tipos por ','
        std::vector<std::string> tipos; // Vector para almacenar los tipos
        std::istringstream tiposStream(campos[2]);
        std::string tipo;
        while (std::getline(tiposStream, tipo, ',')) {tipos.push_back(tipo);}

        std::string descripcion = campos[3]; // Descripción del Pokemon
        
        std::unordered_map<std::string, int> ataques; // Mapa para almacenar los ataques y su daño
        std::istringstream todos_ataquesStream(campos[4]);
        std::string ataque;
        while (std::getline(todos_ataquesStream, ataque, ',')) { // Separar los ataques por ','
            if (ataque.empty()) continue; // Si el ataque está vacío, saltarlo
            std::istringstream ataqueStream(ataque);
            std::string nombreAtaque;
            int fuerza;
            std::getline(ataqueStream, nombreAtaque, ':'); // Nombre del ataque
            ataqueStream >> fuerza; // Daño del ataque
            ataques[nombreAtaque] = fuerza; // Agregar al mapa
        }

        std::array<int, 3> experienciaProximoNivel; // Array para almacenar la experiencia necesaria por nivel
        std::istringstream experienciaStream(campos[5]);
        std::string experienciaNivel;
        int i = 0;
        while (std::getline(experienciaStream, experienciaNivel, ',')) {
            experienciaProximoNivel[i++] = std::stoi(experienciaNivel); // Convertir a entero y almacenar en el array
        }

        std::pair<int, std::string> evolucion; // Par para almacenar la evolución del Pokemon
        std::istringstream evolucionStream(campos[6]);
        std::string evolucionNumero, evolucionNombre;
        std::getline(evolucionStream, evolucionNumero, ','); // Número de evolución
        std::getline(evolucionStream, evolucionNombre); // Nombre de evolución
        evolucion = std::make_pair(std::stoi(evolucionNumero), evolucionNombre);

        // Generar un número aleatorio entre los límites de experiencia por nivel
        int experiencia = generarDesdeExperiencia(experienciaProximoNivel);

        std::pair<std::string, int> par_Datos = std::make_pair(nombre, experiencia);

        // Agregar el nombre del Pokemon al mapa de números y nombres
        numerosNombres[poke_num] = par_Datos;

        // Crear el Pokemon y su información
        Pokemon nuevoPokemon(nombre, experiencia, poke_num);
        // Crear la información del Pokemon
        PokemonInfo nuevaInfo(tipos, descripcion, ataques, experienciaProximoNivel, evolucion);
        // Agregar el Pokemon y su información a la Pokedex
        pokedex.agregarPokemon(nuevoPokemon, nuevaInfo);
    }

    std::cout << "Pokedex creada con exito! Ahora puede buscar cualquier Pokemon de la primera generacion (1-151)." << std::endl;
    std::cout << "============================================================================================================================" << std::endl;

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
                return;
            }
            std::cout << "Pokemon encontrado: " << resultado.first.getNombre() << std::endl; // Muestra el nombre del Pokemon encontrado
        }

        std::cout << "============================================================================" << std::endl;
        std::cout << "Desea seguir agregando pokemones? (y/n): ";
        std::cin >> response;
        if (response != 'y' && response != 'Y'){
            std::cout << "Saliendo del programa..." << std::endl; // Si el usuario no desea seguir agregando Pokemon, se sale del programa
            return;
        }
    }
}

template<typename T>
concept EntradaValida = std::same_as<T, int> || std::same_as<T, std::string>;

template<EntradaValida T>
// Función para leer datos del usuario, puede ser un número entero o una cadena de texto
T leerDato(const std::string& mensaje, bool pide_tipos_ataques = false, int min = std::numeric_limits<int>::min(), int max = std::numeric_limits<int>::max()) {
    std::string input;

    while (true) {
        std::cout << mensaje;
        std::getline(std::cin, input);

        if constexpr (std::same_as<T, int>) {
            try {
                int valor = std::stoi(input);
                if (valor < min || valor > max) {
                    std::cout << "El número debe estar entre " << min << " y " << max << ".\n";
                    continue;
                }
                return valor;
            } catch (const std::invalid_argument&) {
                std::cout << "Entrada inválida. Ingrese un número entero.\n";
            } catch (const std::out_of_range&) {
                std::cout << "Número fuera de rango.\n";
            }
        } else {
            if(pide_tipos_ataques && input.empty()) {
                return ""; // Si se pide un ataque y el input está vacío, se retorna una cadena vacía
            }
            if (input.empty()) {
                std::cout << "El texto no puede estar vacío.\n";
            } else {
                return input;
            }
        }
    }
}

void tercerAdicional() { // Función para la tercera parte adicional del ejercicio
    SystemClear();    

    Pokedex pokedexUsuario; // Crear una Pokedex para el usuario

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorar el salto de línea previo
    std::string continuar = leerDato<std::string>("¿Desea agregar un Pokémon a su Pokedex? (y/n): ");
    if (continuar != "y" && continuar != "Y") {
        std::cout << "Saliendo del programa..." << std::endl; // Si el usuario no desea agregar Pokémon, se sale del programa
        return;
    }

    for(int i = 0; i < 6; ++i) { // Permite agregar hasta 6 Pokémon
        SystemClear();
        std::string nombre = leerDato<std::string>("Ingrese el nombre del Pokémon: ", false); // Leer el nombre del Pokémon
        int experiencia = leerDato<int>("Ingrese la experiencia del Pokémon: ", false, 0, 1000000); // Leer la experiencia del Pokémon, con un rango de 0 a 1,000,000
        int poke_num = leerDato<int>("Ingrese el número de Pokédex (1-151): ", false, 1, 151); // Leer el número de Pokédex del Pokémon, con un rango de 1 a 151

        Pokemon nuevoPokemon(nombre, experiencia, poke_num); // Crear un nuevo Pokémon con el nombre, experiencia y número de Pokédex

        std::string tipo1 = leerDato<std::string>("Ingrese el primer tipo del Pokémon: ", false); // Leer el primer tipo del Pokémon
        std::string tipo2 = leerDato<std::string>("Ingrese el segundo tipo (o deje en blanco): ", true); // Leer el segundo tipo del Pokémon, puede dejarse en blanco
        std::vector<std::string> tipos = {tipo1, tipo2}; // Crear un vector de tipos, puede contener uno o dos tipos

        std::string descripcion = leerDato<std::string>("Ingrese una descripción del Pokémon: ", false); // Leer la descripción del Pokémon

        std::unordered_map<std::string, int> ataques; // Mapa para almacenar los ataques y su daño
        for (int i = 0; i < 5; ++i) {
            std::string nombreAtaque = leerDato<std::string>("Ingrese el nombre del ataque (o deje en blanco para terminar): ", true); // Leer el nombre del ataque, puede dejarse en blanco para terminar
            if (nombreAtaque.empty()) break;
            int dano = leerDato<int>("Ingrese el daño del ataque: ", false, 1, 1000); // Leer el daño del ataque, con un rango de 1 a 1000
            ataques[nombreAtaque] = dano;
        }

        std::array<int, 3> experienciaProximoNivel; // Array para almacenar la experiencia necesaria por nivel
        std::cout << "Ingrese los niveles de experiencia necesarios para el próximo nivel (3 valores):\n";

        // Leer los niveles de experiencia necesarios para el próximo nivel, con un rango de 1 a 100,000
        for (int i = 0; i < 3; ++i) {experienciaProximoNivel[i] = leerDato<int>("  Nivel " + std::to_string(i + 1) + ": ", false, 1, 100000);}

        int nro_pokedex_evolucion = leerDato<int>("Ingrese el número de Pokédex de la evolución (o 0 si no tiene): ", false, 0, 151); // Leer el número de Pokédex de la evolución del Pokémon, con un rango de 0 a 151 (0 si no tiene evolución)
        std::string nombre_evolucion = "";
        // Si el número de Pokédex de la evolución es diferente de 0, se pide el nombre de la evolución
        if (nro_pokedex_evolucion != 0) {nombre_evolucion = leerDato<std::string>("Ingrese el nombre de la evolución: ", false);}

        // Crear la información del Pokémon y agregarlo a la Pokedex del usuario
        PokemonInfo nuevoPokemonInfo(tipos, descripcion, ataques, experienciaProximoNivel, std::make_pair(nro_pokedex_evolucion, nombre_evolucion));
        pokedexUsuario.agregarPokemon(nuevoPokemon, nuevoPokemonInfo);
        std::cout << "¡Pokémon agregado con éxito!\n";

        // Preguntar al usuario si desea agregar otro Pokémon
        std::cout << "¿Desea agregar otro Pokémon? (y/n): ";
        char finalizar;
        std::cin >> finalizar;
        if (finalizar != 'y' && finalizar != 'Y') {
            std::cout << "Saliendo del programa..." << std::endl; // Si el usuario no desea agregar más Pokémon, se sale del programa
            break;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Mostrar cada Pokemon agregado.
    SystemClear();
    std::cout << "============================================================================================================================\n";
    std::cout << "Pokédex del usuario:\n";
    pokedexUsuario.mostrarTodos(); // Muestra todos los Pokémon agregados por el usuario

    return;
}
