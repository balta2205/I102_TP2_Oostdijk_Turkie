#include "Pokedex.h"
#include "../utilities.h"

// Concepto que restringe el tipo T a que sea int o std::string
template<typename T>
concept EntradaValida = std::same_as<T, int> || std::same_as<T, std::string>;

// Concepto que restringe el tipo T a que sea un Pokemon buscable
template<typename T>
concept PokemonBuscable = std::same_as<T, std::string> || std::same_as<T, int>;

// Limpia la consola dependiendo del sistema operativo
void SystemClear() { 
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Muestra una barra de carga con porcentaje
void mostrarBarraDeCargaConPorcentaje(int pasos = 50, int tiempo = 100) { 
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

// Función que confirma una acción con el usuario
bool confirmarAccion(const std::string& mensaje) {
    char respuesta;
    std::cout << mensaje << " (y/n): ";
    std::cin >> respuesta;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar buffer

    return (respuesta == 'y' || respuesta == 'Y');
}

// Funcion que lee un dato desde la entrada estándar.
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

// Imprime las consignas del ejercicio dependiendo de la parte seleccionada
void ImprimirConsignas(Partes parte) { 
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
            std::cout << "============================================================================================================================" << std::endl;
            std::cout << "EJERCICIO 1: POKEDEX" << std::endl;
            std::cout << "============================================================================================================================" << std::endl;
            std::cout << "PARTE ADICIONAL 2: CREAR UN EQUIPO POKEMON, EL USUARIO INGRESA POKEMONES, Y PUEDE EVOLUCIONARLOS." << std::endl;
            std::cout << "============================================================================================================================" << std::endl;
            std::cout << "Esta parte del ejercicio permite al usuario crear su propio equipo de 6 pokemones y, una vez ingresados, evolucionarlos." << std::endl;
            std::cout << "============================================================================================================================" << std::endl;
            break;
        case Partes::CUARTA:
            std::cout << "============================================================================================================================" << std::endl;
            std::cout << "EJERCICIO 1: POKEDEX" << std::endl;
            std::cout << "============================================================================================================================" << std::endl;
            std::cout << "ADICIONAL 3: CARGAR EQUIPO DESDE ARCHIVO BINARIO Y AGREGAR POKEMONES AL MISMO" << std::endl;
            std::cout << "============================================================================================================================" << std::endl;
            std::cout << "Esta parte del ejercicio permite cargar un equipo de pokemones desde un archivo binario llamado 'equipo_final.dat'." << std::endl;
            std::cout << "El usuario puede agregar más pokemones a su equipo." << std::endl;
            std::cout << "============================================================================================================================" << std::endl; 
            break;
        case Partes::QUINTA:
            std::cout << "============================================================================================================================" << std::endl;
            std::cout << "EJERCICIO 1: POKEDEX" << std::endl;
            std::cout << "============================================================================================================================" << std::endl;
            std::cout << "ADICIONAL 4: CARGAR POKEDEX BASICA DESDE ARCHIVO BINARIO" << std::endl;
            std::cout << "============================================================================================================================" << std::endl;
            std::cout << "Esta parte del ejercicio permite cargar una Pokedex básica desde un archivo binario llamado 'pokedex_basica.dat'." << std::endl;
            std::cout << "El usuario puede ver los pokemones cargados." << std::endl;
            std::cout << "============================================================================================================================" << std::endl; 
            break;

    }
}

// Genera un número aleatorio de experiencia desde los niveles dados
int generarDesdeExperiencia(const std::array<int, 3>& niveles) {
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

// Leer una línea del archivo txt
std::pair<Pokemon, PokemonInfo> leerLinea(const std::string& linea) { 
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

// Busca un Pokemon en la Pokedex por nombre o número de Pokedex
template<PokemonBuscable T>
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

// Buscar la evolucion de un Pokemon en el txt
std::pair<Pokemon, PokemonInfo> buscarEnPokedex(Pokemon& pokemonBuscado){ 
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

// Función que permite al usuario armar su equipo de Pokémon
void armarEquipoPokemon(Pokedex& pokedex, Pokedex& pokedexCompleta, std::unordered_map<int, std::pair<std::string, int>>& numerosNombres, int contador) {
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
            pokedex.agregarPokemon(resultado.first, resultado.second);
        }
        else{ // Si la información ingresada es un nombre, se busca por nombre
            std::pair<Pokemon, PokemonInfo> resultado = buscarEnPokedex(informacion, pokedexCompleta, numerosNombres);
            if (resultado.first.getNombre().empty()) {
                std::cout << "Pokemon no encontrado." << std::endl;
                continue;
            }
            std::cout << "Pokemon encontrado: " << resultado.first.getNombre() << std::endl; // Muestra el nombre del Pokemon encontrado
            pokedex.agregarPokemon(resultado.first, resultado.second);
        }

        contador--;
        std::cout << "============================================================================================================================\n" << std::endl;
        if (!confirmarAccion("Desea seguir agregando pokemones?")){break;}
    }


}