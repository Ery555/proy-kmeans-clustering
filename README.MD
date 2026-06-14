# Proyecto de K-Means Clustering para la Materia de Programacion Paralela y Distribuida
Este proyecto busca aplicar la paralelización en la fase de asignación de puntos 
en el algoritmo de K-Means Clustering a traves de la librería OpenMP
en lenguaje C y comparar la optimizacion con el mismo algoritmo en secuencial (con 1 hilo/nucleo)
## Pasos para ejecutar el programa
Sigue estos pasos para compilar y ejecutar las version secuencial o paralela del algoritmo K-Means Clustering:
Nota: Este código fue pensado para compilarse y ejecutarse en un sistema operativo Windows con el compilador MinGW-w64 (la versión x86_64 para 64 bits) a través del entorno de desarrollo y terminal MSYS2.
### Compilación
`mingw32-make`
### Ejecucion de la version secuencial
`.\bin\secuencial.exe`
### Seleccion de Schedule
Para la seleccion del tipo de Schedule se designo una variable de entorno, solo uno de estos
comandos debe ejecutarse antes de ejecutar la version paralela para seleccionar el tipo de Schedule:
Schedule Static:
`$env:OMP_SCHEDULE="static"`
Schedule dynamic:
`$env:OMP_SCHEDULE="dynamic"`
Schedule Guided:
`$env:OMP_SCHEDULE="guided"`
Nota: si se desea cambiar de tipo de Schedule solo debe ejecutar el comando correspondiente
### Ejecucion de la version con paralelismo
`.\bin\paralelo.exe`
