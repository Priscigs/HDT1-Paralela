// EJERCICIO 1 Y 2
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void openmp_hello(void);

int main(int argc, char* argv[]) {
    int thread_count = strtol(argv[1], NULL, 10);

    #pragma omp parallel num_threads(thread_count)
    {
        int id = omp_get_thread_num();
        if (id % 2 != 0) {
            printf("HILO_ID: %d, HILOS_NUM: %d\n", id, thread_count);
            printf("Feliz cumpleaños número %d !\n", id);
        } else {
            printf("HILO_ID: %d, HILOS_NUM: %d\n", id, thread_count);
            printf("Saludos del hilo %d\n", id);
        }
        openmp_hello();
    }
    return 0;
}

void openmp_hello(void) {
    printf("Hola mundo\n");
}
