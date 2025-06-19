#ifndef UTILITIES_H
#define UTILITIES_H

#include <algorithm>
#include <array>
#include <chrono>
#include <condition_variable>
#include <concepts>       // Para std::same_as (C++20)
#include <cstdlib>        // Para std::rand, std::srand
#include <ctime>          // Para std::time
#include <fstream>
#include <functional>     // Para std::hash
#include <iostream>
#include <mutex>
#include <queue>
#include <sstream>
#include <string>
#include <thread>         // Incluye sleep_for
#include <unordered_map>
#include <utility>        // Para std::pair
#include <vector>

enum class Partes {PRIMERA, SEGUNDA, TERCERA, CUARTA, QUINTA};

#endif // UTILITIES_H