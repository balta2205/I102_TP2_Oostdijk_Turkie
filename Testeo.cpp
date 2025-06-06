#include <iostream>
#include <unordered_map>
#include <set>
#include <string>


/////////////////////////////////////////////////////////////////////////

class Pokemon {
private: 
    std::string nombre;
    int experiencia;

public:
    Pokemon(const std::string& nombre, int experiencia)
        : nombre(nombre), experiencia(experiencia) {}

    bool operator==(const Pokemon& other) const { //Sobrecarga del operador == para poder usar los objetos pokemones como key del unordered_map de la pokedex
        return this->nombre == other.nombre && 
               this->experiencia == other.experiencia;
    }

    const std::string& getNombre() const {
        return nombre;
    }

    int getExperiencia() const {
        return experiencia;
    }
};

/////////////////////////////////////////////////////////////////////////

class PokemonInfo {
private:
    const std::string tipo;
    const std::string descripcion;
    const std::unordered_map<std::string, int> ataquesDisponiblesPorNivel; // Unordered_map para almacenar ataques con key y value, ventaja para buscar rapido el ataque por key, no me interesa que los ataques esten ordenados. Pero si me interesa que cuando se busque un ataque por key saber si el pokemon conoce el ataque o no.
    const std::set<int, std::greater<int>> experienciaProximoNivel;
    // REVISAR SI CONVIENE USAR SET O NO PORQUE YA SE SABE QUE SON 3 Y LOS INGRESAMOS YA ORDENADOS CREO.

public:
    PokemonInfo(const std::string& tipo, const std::string& descripcion,
                const std::unordered_map<std::string, int>& ataquesDisponiblesPorNivel,
                const std::set<int>& experienciaProximoNivel) :
        tipo(tipo), descripcion(descripcion),
        ataquesDisponiblesPorNivel(ataquesDisponiblesPorNivel),
        experienciaProximoNivel(experienciaProximoNivel) {}
};

/////////////////////////////////////////////////////////////////////////

class Pokedex{
private:
    std::unordered_map<Pokemon, PokemonInfo> informacion;
    // Unordered_map porque no quiero que hayan repetidos pero no me interesa que esten en orden, prefiero tener mas velocidad para chequear si un pokemon esta registrado o no.
public:
    
    void imprimirInformacion(const Pokemon& pokemon) const {
        auto it = informacion.find(pokemon); // Bucamos si el pokemon esta registrado en la Pokedex.
        // Si el pokemon esta registrado, it no sera igual a informacion.end(), si no esta registrado, it sera igual a informacion.end(). Eso por como funciona el container unordered_map.
        if (it != informacion.end()){
            std::string nombre = it->first.getNombre(); 
            int experiencia = it->first.getExperiencia();
            const PokemonInfo& info = it->second;

            std::cout << "Nombre: " << nombre << std::endl;
            std::cout << "Experiencia: " << experiencia << std::endl;
            std::cout << "Tipo: " << info.tipo << std::endl;
            std::cout << "Descripcion: " << info.descripcion << std::endl;
            std::cout << "Ataques disponibles por nivel:" << std::endl;
            for (const auto& ataque : info.ataquesDisponiblesPorNivel) {
                std::string ataqueNombre = ataque.first;
                int cant_ataque = ataque.second;

                std::cout << "  " << ataqueNombre << ": " << cant_ataque << " ataques" << std::endl;
            }

            int nivel_pokemon = 1;
            for (int indice = 1; indice < 3; ++indice) {
                if(experiencia > info.experienciaProximoNivel[indice])  nivel_pokemon = nivel_pokemon + 1;
            }
            // Asumimos que el pokemon es nivel 1, si la experiencia es mayor al segundo int del set eso quiere decir que en realidad el pokemon es nivel 2, y si la experiencia es mayor al tercer int del set eso quiere decir que el pokemon es nivel 3.

            std::cout << "Nivel:" << nivel_pokemon << std::endl;

        }
        else {
            std::cout << "Pokemon no encontrado en la Pokedex." << std::endl;
        }
    }
};

/////////////////////////////////////////////////////////////////////////

// Functor para hashing personalizado

// Sobrecarga del operador () para poder usar el Pokemon como key en el unordered_map de la Pokedex.
class PokemonHash {
public:
    size_t operator()(const Pokemon& pokemon) const {
        return std::hash<std::string>()(pokemon.getNombre()) ^
               (std::hash<int>()(pokemon.getExperiencia()) << 1);
    }
};

/////////////////////////////////////////////////////////////////////////


int main(){


    Pokemon squirtle("Squirtle", 100);
    PokemonInfo squirtleInfo("Agua", "Una tortuga pequeña que lanza chorros de agua.",
 {{"Pistola Agua", 4}, {"Hidrobomba", 6}, {"Danza Lluvia", 5}},
 {0, 400, 1000});

    Pokemon bulbasaur("Bulbasaur", 270);
    PokemonInfo bulbasaurInfo("Planta", "Tiene una semilla en su lomo que crece con el tiempo",
 {{"Latigazo", 4}, {"Hoja Afilada", 6}, {"Rayo Solar", 5}},
 {0, 300, 1100});

    Pokemon charmander("Charmander", 633);
    PokemonInfo charmanderInfo("Fuego", "Una lagartija con una llama en su cola.",
 {{"Ascuas", 4}, {"Llamarada", 6}, {"Giro Fuego", 5}},
 {0, 250, 1300});

    return 0;
}