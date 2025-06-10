ej1:
	@g++ -Wall -Wextra -Wpedantic -std=c++20 -I Ejercicio_1/headers -o ejercicio1 Ejercicio_1/main.cpp Ejercicio_1/sources/*.cpp
	@./ejercicio1
	@rm ejercicio1
	@rm -rf ejercicio1.dSYM/

ej2:
	@g++ -Wall -Wextra -Wpedantic -std=c++17 -I Ejercicio_2/headers -o ejercicio2 Ejercicio_2/main.cpp Ejercicio_2/sources/*.cpp
	@./ejercicio2
	@rm ejercicio2
	@rm -rf ejercicio2.dSYM/

ej3:
	@g++ -Wall -Wextra -Wpedantic -std=c++17 -o ejercicio3 Ejercicio_3/main.cpp
	@./ejercicio3
	@rm ejercicio3
	@rm -rf ejercicio3.dSYM/