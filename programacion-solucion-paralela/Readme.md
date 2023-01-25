# TC4031.10 - Computo en la nube

## Tarea 1. Programación de una solución paralela

**Diego Carrera Nicholls a00464290@tec.mx**


Requerimientos:

homebrew, xcode-command-line-tools, make, libomp (openmp)
o
homebrew, make, gcc, g++, libomp (openmp)

### Instalación de homebrew
[Homebrew](https://brew.sh/)

### Xcode command line tools
[Command Line Tools](https://developer.apple.com/download/more/)

```
xcode-select --install
```

### Instalación de libomp
```
brew install libomp
```

### Compilación
```
make -j
```

### Ejecución
```
./suma_arreglos
```


### Salida
```
Sumando arreglos en Paralelo!
Nota: Utiliza usleep para demostrar la utilidad de los hilos
Elige tu semilla para generar los numeros aleatorios: 42
Elige el tamaño del arreglo: 123456
Elige la cantidad de hilos que quieres usar (12) cores: 8

Imprimiendo los primeros 10 valores de 123456 del arreglo a:
8168.09 8016.44 5012.05 5132.78 2285.66 1507.65 9446.04 9928.91 6504.27 1207.54

Imprimiendo los primeros 10 valores de 123456 del arreglo b:
2650.73 6371.05 1899.67 4003.04 6857.35 7497.27 1007.01 6556.72 1063.59 5722.45

Imprimiendo los primeros 10 valores de 123456 del arreglo c:
10818.8 14387.5 6911.72 9135.82 9143 9004.92 10453 16485.6 7567.86 6929.99

Suma de los valores del arreglo c: 1.35886e+09

Tiempo de ejecucion: 201 ms
```

