CC = g++
CFLAGS = -Wall -Werror -Xpreprocessor -fopenmp -std=c++17 -I/usr/local/opt/libomp/include -L/usr/local/opt/libomp/lib -lomp

all: prueba_openmp suma_arreglos regiones_paralelas creacion_n_threads guia_profesor

prueba_openmp: prueba_openmp.cpp
	$(CC) $(CFLAGS) prueba_openmp.cpp -o prueba_openmp

suma_arreglos: suma_arreglos.cpp
	$(CC) $(CFLAGS) suma_arreglos.cpp -o suma_arreglos

regiones_paralelas: regiones_paralelas.cpp
	$(CC) $(CFLAGS) regiones_paralelas.cpp -o regiones_paralelas

creacion_n_threads: creacion_n_threads.cpp
	$(CC) $(CFLAGS) creacion_n_threads.cpp -o creacion_n_threads

guia_profesor: guia_profesor.cpp
	$(CC) $(CFLAGS) guia_profesor.cpp -o guia_profesor

clean:
	rm -f prueba_openmp suma_arreglos regiones_paralelas creacion_n_threads guia_profesor
