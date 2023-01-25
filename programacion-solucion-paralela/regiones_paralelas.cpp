#include <iostream>
#include <omp.h>

int main()
{

  std::cout << "Regiones paralelas" << std::endl;

  int hilos, tid;

  #pragma omp parallel private(tid)
  {
    tid = omp_get_thread_num();
    std::cout << "Trabajando en el thread" << tid << "\n" << std::endl;
    if ( tid == 0 )
    {
      hilos = omp_get_num_threads();
      std::cout << "Número de threads es: " << hilos << std::endl;
    }
  }

}
