#include <iostream>
#include <omp.h>


#define N 1000
#define chunk 100
#define mostrar 10

void imprimeArreglo(float *d);

int main() {
  std::cout << "Sumando Arreglos en Paralelo!" << std::endl;
  float a[N], b[N], c[N];
  int i;

  for( i = 0; i < N; i++ )
  {
    a[i] = i * 10.0;
    b[i] = (i + 3) * 3.7;
  }
  int pedazos = chunk;

  #pragma omp parallel for \
  shared ( a, b, c, pedazos ) private (i) \
  schedule (static, pedazos)
  for ( i = 0; i < N; i++ )
    c[i] = a[i] + b[i];

  std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << std::endl;
  imprimeArreglo(a);

  std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << std::endl;
  imprimeArreglo(b);

  std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << std::endl;
  imprimeArreglo(c);

  return 0;
}

void imprimeArreglo(float *d) {
  for (int i = 0; i < mostrar; i++)
    std::cout << d[i] << " - ";

  std::cout << std::endl;
}
