/**
 * TC4031.10 Cómputo en la nube
 * Tarea 1 - Suma de arreglos en paralelo
 * Profesor: Dr. Eduardo Antonio Cendejas Castro <eduardo.cendejas@tec.mx>
 * Autor: Dr. Eduardo Antonio Cendejas Castro <eduardo.cendejas@tec.mx>
 * Autor: Diego Carrera Nicholls <a00464290@tec.mx>
 */

#include <iostream>
#include <random>
#include <chrono>
#include <thread>

#include <omp.h>

using namespace std;

// define el numero de elementos a procesar en cada hilo
#define chunk 1000
// define el numero de elementos a mostrar de cada arreglo
#define mostrar 10

// define el rango de los numeros aleatorios para llenar los arreglos
#define LO 1000.00
#define HI 9999.00


// definición de la funcion que imprime los primeros 10 elementos de un arreglo
void imprimeArreglo(float *d);

int main()
{
  // valores por defecto
  int N = 257400;
  int SEED = 42;
  int USE_THREADS = 4;

  // pedir al usuario los valores de N, SEED y USE_THREADS
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

  // inicializa el generador de numeros aleatorios con una semilla
  std::mt19937 engine(SEED);
  // genera numeros aleatorios entre LO y HI
  std::uniform_real_distribution<double> dist(LO, HI);


  // inicializa los arreglos
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


  // utilización de los pragmas de OpenMP para paralelizar el codigo en los hilos
  // se utiliza la directiva omp parallel for para indicar que se va a paralelizar el ciclo for
  // se utiliza la directiva shared para indicar que los arreglos a, b y c son compartidos entre los hilos
  // se utiliza la directiva private para indicar que la variable i es privada para cada hilo
  // se utiliza la directiva schedule para indicar que se va a usar el algoritmo de particion estatica en bloques de tamaño chunk

  // cada 100 iteraciones se usa usleep para simular un proceso pesado y demostrar la utilidad de los hilos
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

  // calcula la suma de los valores del arreglo c
  double suma = 0.0;
  for (i = 0; i < N; i++)
  {
    suma += c[i];
  }

  // calcula el tiempo de ejecucion
  auto end = std::chrono::high_resolution_clock::now();
  auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);


  // impresion de resultados
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
