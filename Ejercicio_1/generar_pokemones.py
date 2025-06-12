import requests  # Para hacer solicitudes HTTP a la API
import random    # Para generar valores aleatorios

# Ruta donde se va a guardar el archivo con la información
output_path = "datos_pokemones_151.txt"
datos_finales = []  # Lista donde se guardarán todas las líneas finales del archivo

# Iterar sobre los primeros 151 Pokémon (1 a 151 inclusive)
for numero in range(1, 152):
    try:
        # Obtener información básica del Pokémon desde la PokeAPI
        poke_data = requests.get(f"https://pokeapi.co/api/v2/pokemon/{numero}", timeout=10).json()
        # Obtener información de especie (incluye descripción y cadena evolutiva)
        species_data = requests.get(f"https://pokeapi.co/api/v2/pokemon-species/{numero}", timeout=10).json()

        # Nombre del Pokémon, capitalizado (primera letra en mayúscula)
        name = poke_data["name"].capitalize()

        # Obtener los tipos (puede tener uno o dos)
        types = [t["type"]["name"].capitalize() for t in poke_data["types"]]
        types_str = ",".join(types)  # Convertir la lista en un string separado por comas

        # Obtener la primera descripción en inglés disponible
        description = next(
            (entry["flavor_text"].replace("\n", " ").replace("\f", " ")
             for entry in species_data["flavor_text_entries"]
             if entry["language"]["name"] == "en"),
            f"{name} Pokémon."  # Valor por defecto si no encuentra ninguna descripción en inglés
        )

        # Elegir hasta 5 movimientos distintos del Pokémon
        move_names = []
        for move in poke_data["moves"]:
            move_name = move["move"]["name"].replace("-", " ").title()  # Formatear nombre del movimiento
            if move_name not in move_names:
                move_names.append(move_name)
            if len(move_names) == 5:
                break  # Cortar cuando ya tenemos 5
        # Rellenar con "Unknown" si tiene menos de 5 movimientos
        while len(move_names) < 5:
            move_names.append("Unknown")

        # Asignar un daño aleatorio entre 4 y 20 a cada ataque
        attacks = [f"{m}:{random.randint(4, 20)}" for m in move_names]

        # Generar experiencia para niveles: nivel 1 (0), nivel 2 (250–400), nivel 3 (sumando 400–600 al nivel 2)
        exp1 = 0
        exp2 = random.choice([250, 300, 350, 400])
        exp3 = exp2 + random.choice([400, 500, 600])
        experience = f"{exp1},{exp2},{exp3}"

        # Obtener URL de la cadena evolutiva
        evo_url = species_data["evolution_chain"]["url"]
        evo_chain = requests.get(evo_url, timeout=10).json()["chain"]

        # Función recursiva para encontrar la evolución del Pokémon actual en la cadena
        def find_evolution(chain, target):
            if chain["species"]["name"] == target.lower():
                if chain["evolves_to"]:
                    # Si tiene evolución, obtener el siguiente nombre e ID
                    next_name = chain["evolves_to"][0]["species"]["name"].capitalize()
                    next_data = requests.get(f"https://pokeapi.co/api/v2/pokemon/{next_name.lower()}", timeout=10).json()
                    return f"{next_data['id']},{next_name}"
                return "0,"  # Si no tiene evolución
            for next_stage in chain["evolves_to"]:
                result = find_evolution(next_stage, target)
                if result:
                    return result
            return "0,"  # Si no encuentra el Pokémon en la cadena

        # Llamar a la función de evolución
        evolution = find_evolution(evo_chain, name)

        # Formar la línea final con toda la información separada por ;
        linea = f"{numero};{name};{types_str};{description};{','.join(attacks)};{experience};{evolution}"
        datos_finales.append(linea)

    except Exception as e:
        # Si hubo algún error, mostrar cuál fue el Pokémon afectado
        print(f"Error with Pokémon #{numero}: {e}")

# Escribir todas las líneas en el archivo final
with open(output_path, "w", encoding="utf-8") as f:
    for linea in datos_finales:
        f.write(linea + "\n")

print(f"Archivo generado correctamente: {output_path}")
