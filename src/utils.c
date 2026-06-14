#include "kmeans.h"

// Calcula la distancia euclidiana al cuadrado (sin raíz) para optimizar rendimiento
float calcular_distancia_cuadrada(float *p1, float *p2, int d) {
    float suma_cuadrados = 0.0;
    for (int i = 0; i < d; i++) {
        float diff = p1[i] - p2[i];
        suma_cuadrados += diff * diff;
    }
    return suma_cuadrados;
}