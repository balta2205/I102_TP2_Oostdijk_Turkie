import requests
import random

output_path = "datos_pokemones_151.txt"
datos_finales = []

# Iterar sobre los primeros 151 Pokémon
for numero in range(1, 152):
    try:
        # Datos base del Pokémon
        poke_data = requests.get(f"https://pokeapi.co/api/v2/pokemon/{numero}", timeout=10).json()
        species_data = requests.get(f"https://pokeapi.co/api/v2/pokemon-species/{numero}", timeout=10).json()

        name = poke_data["name"].capitalize()
        types = [t["type"]["name"].capitalize() for t in poke_data["types"]]
        types_str = ",".join(types)

        # Obtener descripción en inglés
        description = next(
            (entry["flavor_text"].replace("\n", " ").replace("\f", " ")
             for entry in species_data["flavor_text_entries"]
             if entry["language"]["name"] == "en"),
            f"{name} Pokémon."
        )

        # Seleccionar hasta 5 movimientos
        move_names = []
        for move in poke_data["moves"]:
            move_name = move["move"]["name"].replace("-", " ").title()
            if move_name not in move_names:
                move_names.append(move_name)
            if len(move_names) == 5:
                break
        while len(move_names) < 5:
            move_names.append("Unknown")

        attacks = [f"{m}:{random.randint(4, 20)}" for m in move_names]

        # Generar experiencia aleatoria redonda y coherente
        exp1 = 0
        exp2 = random.choice([250, 300, 350, 400])
        exp3 = exp2 + random.choice([400, 500, 600])
        experience = f"{exp1},{exp2},{exp3}"

        # Obtener evolución real desde la cadena
        evo_url = species_data["evolution_chain"]["url"]
        evo_chain = requests.get(evo_url, timeout=10).json()["chain"]

        def find_evolution(chain, target):
            if chain["species"]["name"] == target.lower():
                if chain["evolves_to"]:
                    next_name = chain["evolves_to"][0]["species"]["name"].capitalize()
                    next_data = requests.get(f"https://pokeapi.co/api/v2/pokemon/{next_name.lower()}", timeout=10).json()
                    return f"{next_data['id']},{next_name}"
                return "0,"
            for next_stage in chain["evolves_to"]:
                result = find_evolution(next_stage, target)
                if result:
                    return result
            return "0,"

        evolution = find_evolution(evo_chain, name)

        # Armar línea final
        linea = f"{numero};{name};{types_str};{description};{','.join(attacks)};{experience};{evolution}"
        datos_finales.append(linea)

    except Exception as e:
        print(f"Error with Pokémon #{numero}: {e}")

# Guardar el archivo final
with open(output_path, "w", encoding="utf-8") as f:
    for linea in datos_finales:
        f.write(linea + "\n")

print(f"Archivo generado correctamente: {output_path}")
