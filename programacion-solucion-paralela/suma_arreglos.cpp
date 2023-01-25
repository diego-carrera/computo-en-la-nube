#include <iostream>
#include <random>
#include <chrono>
#include <thread>

#include <omp.h>

using namespace std;

#define chunk 1000
#define mostrar 10
#define LO 1000.00
#define HI 9999.00

void imprimeArreglo(float *d);

int main()
{
  int N = 257400;
  int SEED = 42;
  int USE_THREADS = 4;

  cout << "Sumando arreglos en Paralelo!" << endl;
  cout << "Nota: Utiliza usleep para demostrar la utilidad de los hilos" << endl;

  cout << "Elige tu semilla para generar los numeros aleatorios: ";
  cin >> SEED;

  int cores = omp_get_num_procs();
  cout << "Elige la cantidad de hilos que quieres usar (" << cores << ") cores: ";
  cin >> USE_THREADS;


  std::mt19937 engine(SEED);
  std::uniform_real_distribution<double> dist(LO, HI);

  float a[N], b[N], c[N];
  int i;

  for ( i=0; i<N; i++) {
    a[i] = dist(engine);
    b[i] = dist(engine);

  }

  if ( USE_THREADS > 0 ) {
    omp_set_num_threads(USE_THREADS);
  }


  int pedazos = chunk;
  auto start = std::chrono::high_resolution_clock::now();

  #pragma omp parallel for \
  shared ( a, b, c, pedazos ) private (i) \
  schedule (static, pedazos)

  for ( i = 0; i < N; i++ ) {
    c[i] = a[i] + b[i];
    if ( i % 100 == 0 ) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
  }
  auto end = std::chrono::high_resolution_clock::now();
  auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

  cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << endl;
  imprimeArreglo(a);

  cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << endl;
  imprimeArreglo(b);

  cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << endl;
  imprimeArreglo(c);

  cout << "Tiempo de ejecucion: " << time.count() << " ms" << endl;

  return 0;
}

void imprimeArreglo(float *d) {
  for (int i = 0; i < mostrar; i++) {
    cout << d[i] << " ";
  }
  cout << endl;
}
