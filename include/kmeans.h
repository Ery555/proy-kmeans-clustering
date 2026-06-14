#ifndef KMEANS_H
#define KMEANS_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

// Prototipos de utilidades
float calcular_distancia_cuadrada(float *p1, float *p2, int d);

// Prototipos de los algoritmos K-Means
void ejecutar_kmeans_secuencial(float *datos, float *centroides, int *asignaciones, int n, int d, int k);
void ejecutar_kmeans_paralelo(float *datos, float *centroides, int *asignaciones, int n, int d, int k);

#endif