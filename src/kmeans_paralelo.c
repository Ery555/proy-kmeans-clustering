#include "kmeans.h"

void ejecutar_kmeans_paralelo(float *datos, float *centroides, int *asignaciones, int n, int d, int k) {
    int hubo_cambios = 1;
    int iteracion = 0;
    int max_iter = 200;

    float *nuevas_sumas = (float*)calloc(k * d, sizeof(float));
    int *contadores = (int*)calloc(k, sizeof(int));

    while (hubo_cambios && iteracion < max_iter) {
        hubo_cambios = 0;

        // -------------------------------------------------------------
        // FASE 1: ASIGNACIÓN DE PUNTOS (PARALELIZADA)
        // -------------------------------------------------------------
        // reduction(+:hubo_cambios): Evita condición de carrera al sumar los cambios de cada hilo.
        // schedule(static): Reparte el bucle equitativamente entre los núcleos al compilar.
        #pragma omp parallel for reduction(+:hubo_cambios) schedule(static)
        for (int i = 0; i < n; i++) {
            // NOTA: 'dist_min' y 'cluster_cercano' son privadas para cada hilo automáticamente 
            // porque están declaradas DENTRO de la región paralela.
            float dist_min = 1e9;
            int cluster_cercano = -1;

            for (int j = 0; j < k; j++) {
                float dist = calcular_distancia_cuadrada(&datos[i * d], &centroides[j * d], d);
                
                if (dist < dist_min) {
                    dist_min = dist;
                    cluster_cercano = j;
                }
            }

            if (asignaciones[i] != cluster_cercano) {
                asignaciones[i] = cluster_cercano;
                hubo_cambios = 1; // Cada hilo sumará a su propia copia privada, y luego se juntarán
            }
        }

        // -------------------------------------------------------------
        // FASE 2: ACTUALIZACIÓN DE CENTROIDES (SECUENCIAL Y SEGURA)
        // -------------------------------------------------------------
        for(int j=0; j < k * d; j++) nuevas_sumas[j] = 0.0;
        for(int j=0; j < k; j++) contadores[j] = 0;

        for (int i = 0; i < n; i++) {
            int grupo = asignaciones[i];
            contadores[grupo]++;
            for (int dim = 0; dim < d; dim++) {
                nuevas_sumas[grupo * d + dim] += datos[i * d + dim];
            }
        }

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