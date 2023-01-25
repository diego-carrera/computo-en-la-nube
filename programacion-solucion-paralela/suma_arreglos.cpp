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
  std::string seed_input;
  std::getline(std::cin, seed_input);
  if (!seed_input.empty())
  {
    SEED = std::stoi(seed_input);
  }

  cout << "Elige el tamaño del arreglo: ";
  std::string n_input;
  std::getline(std::cin, n_input);
  if (!n_input.empty())
  {
    N = std::stoi(n_input);
  }
  if (N > 257400)
  {
    cout << "El tamaño del arreglo es muy grande, se usara el valor por defecto: 257400" << endl;
    N = 257400;
  }

  int cores = omp_get_num_procs();
  cout << "Elige la cantidad de hilos que quieres usar (" << cores << ") cores: ";
  std::string threads_input;
  std::getline(std::cin, threads_input);
  if (!threads_input.empty())
  {
    USE_THREADS = std::stoi(threads_input);
  }

  std::mt19937 engine(SEED);
  std::uniform_real_distribution<double> dist(LO, HI);

  float a[N], b[N], c[N];
  int i;

  for (i = 0; i < N; i++)
  {
    a[i] = dist(engine);
    b[i] = dist(engine);
  }

  if (USE_THREADS > 0)
  {
    omp_set_num_threads(USE_THREADS);
  }

  int pedazos = chunk;
  auto start = std::chrono::high_resolution_clock::now();

  #pragma omp parallel for \
  shared(a, b, c, pedazos) private(i) \
  schedule(static, pedazos)
  for (i = 0; i < N; i++)
  {
    c[i] = a[i] + b[i];
    if (i % 100 == 0)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
  }

  double suma = 0.0;

  for (i = 0; i < N; i++)
  {
    suma += c[i];
  }

  auto end = std::chrono::high_resolution_clock::now();
  auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

  cout << endl;
  cout << "Imprimiendo los primeros " << mostrar << " valores de " << (sizeof(a) / sizeof(*a)) << " del arreglo a:" << endl;
  imprimeArreglo(a);
  cout << endl;

  cout << "Imprimiendo los primeros " << mostrar << " valores de " << (sizeof(b) / sizeof(*b)) << " del arreglo b:" << endl;
  imprimeArreglo(b);
  cout << endl;

  cout << "Imprimiendo los primeros " << mostrar << " valores de " << (sizeof(c) / sizeof(*c)) << " del arreglo c:" << endl;
  imprimeArreglo(c);
  cout << endl;

  cout << "Suma de los valores del arreglo c: " << suma << endl;

  cout << endl;
  cout << "Tiempo de ejecucion: " << time.count() << " ms" << endl;

  return 0;
}

void imprimeArreglo(float *d)
{
  for (int i = 0; i < mostrar; i++)
  {
    cout << d[i] << " ";
  }
  cout << endl;
}
