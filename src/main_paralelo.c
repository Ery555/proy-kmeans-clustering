#include "kmeans.h"
#include <omp.h>

#define N 2000000 //Cantidad de datos (filas)
#define D 25 //Numero de Dimensiones de los Datos (columnas)
#define K 8 //Numero de Centroides Asignado

int main() {
    printf("--- K-MEANS CLUSTERING PARALELO (OPENMP) ---\n");
    float *datos = (float*)malloc((long long)N * D * sizeof(float));
    float *centroides = (float*)malloc(K * D * sizeof(float));
    int *asignaciones = (int*)malloc(N * sizeof(int));

    FILE *archivo = fopen("dataset_electoral_5M.bin", "rb");
    if (!archivo) {
        printf("Error: No se encontro el dataset binario.\n");
        return 1;
    }
    fread(datos, sizeof(float), (long long)N * D, archivo);
    fclose(archivo);

    srand(42); 
    long long salto = N / K; //Salto entre los datos para mayor precision
    
    for (int i = 0; i < K; i++) {
        long long aleatorio_gigante = (long long)rand() * RAND_MAX + rand(); //CALCULO PARA SOBRE PASAR RAND_MAX debido a la cantidad de datos
        long long offset = aleatorio_gigante % salto;
        long long indice_aleatorio = (long long)i * salto + offset;
        
        for (int dim = 0; dim < D; dim++) {
            centroides[i * D + dim] = datos[indice_aleatorio * D + dim];
        }
    }

    // Ejecución y medición
    double inicio = omp_get_wtime();
    ejecutar_kmeans_paralelo(datos, centroides, asignaciones, N, D, K);
    double fin = omp_get_wtime();

    printf("Tiempo de ejecucion Paralelo: %f segundos\n", fin - inicio);

    // Imprimir los resultados de los Centroides
    printf("\n=== CENTROIDES FINALES ===\n");
    for (int i = 0; i < K; i++) {
        printf("Perfil %d: ", i);
        // Imprime las 20 dimensiones
        for (int dim = 0; dim < 20; dim++) { 
            printf("%.4f ", centroides[i * D + dim]);
        }
        printf(".\n");
    }

    free(datos); free(centroides); free(asignaciones);
    return 0;
}