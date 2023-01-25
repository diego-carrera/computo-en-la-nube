#include <iostream>
#include <omp.h>

int main() {
  std::cout << "Verificando la ejecución de OpenMP!" << std::endl;

  #ifdef _OPENMP
    std::cout << "OpenMP está disponible!" << std::endl;
  #else
    std::cout << "OpenMP no está disponible!" << std::endl;
  #endif
}
