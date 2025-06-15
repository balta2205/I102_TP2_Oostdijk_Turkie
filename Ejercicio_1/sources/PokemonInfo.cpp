#include "PokemonInfo.h"

// Constructor con parametros
PokemonInfo::PokemonInfo(const std::vector<std::string>& tipos, const std::string& descripcion, const std::unordered_map<std::string, int>& ataquesDisponiblesPorNivel, const std::array<int, 3>& experienciaProximoNivel) :
    tipos(tipos),
    descripcion(descripcion),
    ataquesDisponiblesPorNivel(ataquesDisponiblesPorNivel),
    experienciaProximoNivel(experienciaProximoNivel) {}

// Constructor con parametros ycon evolución
PokemonInfo::PokemonInfo(const std::vector<std::string>& tipos, const std::string& descripcion, const std::unordered_map<std::string, int>& ataquesDisponiblesPorNivel, const std::array<int, 3>& experienciaProximoNivel, const std::pair<int, std::string>& evolucion) :
    tipos(tipos),
    descripcion(descripcion),
    ataquesDisponiblesPorNivel(ataquesDisponiblesPorNivel),
    experienciaProximoNivel(experienciaProximoNivel),
    evolucion(evolucion) {}

// Getters
const std::vector<std::string>& PokemonInfo::getTipos() const {return this->tipos;}
const std::string& PokemonInfo::getDescripcion() const {return this->descripcion;}
const std::unordered_map<std::string, int>& PokemonInfo::getAtaquesDisponiblesPorNivel() const {return this->ataquesDisponiblesPorNivel;}
const std::array<int, 3>& PokemonInfo::getExperienciaProximoNivel() const {return this->experienciaProximoNivel;}
const std::pair<int, std::string>& PokemonInfo::getEvolucion() const {return this->evolucion;}

// Serialización del Pokémon
void PokemonInfo::serializar(std::ofstream& out) const {
    // Tipos
    size_t tam_tipos = tipos.size();
    out.write(reinterpret_cast<const char*>(&tam_tipos), sizeof(tam_tipos));
    for (const auto& tipo : tipos) {
        size_t tam = tipo.size();
        out.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
        out.write(tipo.c_str(), tam);
    }

    // Descripción
    size_t tam_desc = descripcion.size();
    out.write(reinterpret_cast<const char*>(&tam_desc), sizeof(tam_desc));
    out.write(descripcion.c_str(), tam_desc);

    // Ataques
    size_t tam_ataques = ataquesDisponiblesPorNivel.size();
    out.write(reinterpret_cast<const char*>(&tam_ataques), sizeof(tam_ataques));
    for (const auto& [nombre, fuerza] : ataquesDisponiblesPorNivel) {
        size_t tam = nombre.size();
        out.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
        out.write(nombre.c_str(), tam);
        out.write(reinterpret_cast<const char*>(&fuerza), sizeof(fuerza));
    }

    // Experiencia niveles
    out.write(reinterpret_cast<const char*>(experienciaProximoNivel.data()), sizeof(int) * 3);

    // Evolución
    out.write(reinterpret_cast<const char*>(&evolucion.first), sizeof(evolucion.first));
    size_t tam_nombre = evolucion.second.size();
    out.write(reinterpret_cast<const char*>(&tam_nombre), sizeof(tam_nombre));
    out.write(evolucion.second.c_str(), tam_nombre);
}

// Deserialización del Pokémon
void PokemonInfo::deserializar(std::ifstream& in) {
    // Tipos
    size_t tam_tipos = 0;
    in.read(reinterpret_cast<char*>(&tam_tipos), sizeof(tam_tipos));
    tipos.clear();
    for (size_t i = 0; i < tam_tipos; ++i) {
        size_t tam = 0;
        in.read(reinterpret_cast<char*>(&tam), sizeof(tam));
        std::string tipo(tam, '\0');
        in.read(&tipo[0], tam);
        tipos.push_back(tipo);
    }

    // Descripción
    size_t tam_desc = 0;
    in.read(reinterpret_cast<char*>(&tam_desc), sizeof(tam_desc));
    descripcion = std::string(tam_desc, '\0');
    in.read(&descripcion[0], tam_desc);

    // Ataques
    size_t tam_ataques = 0;
    in.read(reinterpret_cast<char*>(&tam_ataques), sizeof(tam_ataques));
    ataquesDisponiblesPorNivel.clear();
    for (size_t i = 0; i < tam_ataques; ++i) {
        size_t tam = 0;
        in.read(reinterpret_cast<char*>(&tam), sizeof(tam));
        std::string nombre(tam, '\0');
        in.read(&nombre[0], tam);
        int fuerza;
        in.read(reinterpret_cast<char*>(&fuerza), sizeof(fuerza));
        ataquesDisponiblesPorNivel[nombre] = fuerza;
    }

    // Experiencia niveles
    in.read(reinterpret_cast<char*>(experienciaProximoNivel.data()), sizeof(int) * 3);

    // Evolución
    int num_evo = 0;
    size_t tam_nom_evo = 0;
    in.read(reinterpret_cast<char*>(&num_evo), sizeof(num_evo));
    in.read(reinterpret_cast<char*>(&tam_nom_evo), sizeof(tam_nom_evo));
    std::string nom_evo(tam_nom_evo, '\0');
    in.read(&nom_evo[0], tam_nom_evo);
    evolucion = {num_evo, nom_evo};
}
