#include "kmeans.h"

void ejecutar_kmeans_secuencial(float *datos, float *centroides, int *asignaciones, int n, int d, int k) {
    int hubo_cambios = 1;
    int iteracion = 0;
    int max_iter = 200; // Límite de seguridad

    // Arreglos auxiliares para recalcular el promedio de los centroides
    float *nuevas_sumas = (float*)calloc(k * d, sizeof(float));
    int *contadores = (int*)calloc(k, sizeof(int));

    while (hubo_cambios && iteracion < max_iter) {
        hubo_cambios = 0;

        // -------------------------------------------------------------
        // FASE 1: ASIGNACIÓN DE PUNTOS (EL CUELLO DE BOTELLA)
        // -------------------------------------------------------------
        for (int i = 0; i < n; i++) {
            float dist_min = 1e9; // Número muy grande
            int cluster_cercano = -1;

            // Comparar contra todos los centroides
            for (int j = 0; j < k; j++) {
                // Pasamos las direcciones de memoria de la fila exacta a la función utils
                float dist = calcular_distancia_cuadrada(&datos[i * d], &centroides[j * d], d);
                
                if (dist < dist_min) {
                    dist_min = dist;
                    cluster_cercano = j;
                }
            }

            if (asignaciones[i] != cluster_cercano) {
                asignaciones[i] = cluster_cercano;
                hubo_cambios = 1;
            }
        }

        // -------------------------------------------------------------
        // FASE 2: ACTUALIZACIÓN DE CENTROIDES (SECUENCIAL)
        // -------------------------------------------------------------
        // 1. Limpiar los arreglos auxiliares
        for(int j=0; j < k * d; j++) nuevas_sumas[j] = 0.0;
        for(int j=0; j < k; j++) contadores[j] = 0;

        // 2. Sumar las coordenadas de cada clúster
        for (int i = 0; i < n; i++) {
            int grupo = asignaciones[i];
            contadores[grupo]++;
            for (int dim = 0; dim < d; dim++) {
                nuevas_sumas[grupo * d + dim] += datos[i * d + dim];
            }
        }

        // 3. Dividir entre el total para hallar el nuevo centro de gravedad
        for (int j = 0; j < k; j++) {
            if (contadores[j] > 0) {
                for (int dim = 0; dim < d; dim++) {
                    centroides[j * d + dim] = nuevas_sumas[j * d + dim] / contadores[j];
                }
            }
        }
        iteracion++;
    }
    
    printf("   -> Convergio en %d iteraciones.\n", iteracion);
    free(nuevas_sumas);
    free(contadores);
}