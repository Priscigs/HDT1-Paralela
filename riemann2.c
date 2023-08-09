/*----------------------------------------------
* riemann.c - calculo de area bajo la curva
*----------------------------------------------
* Sumas de Riemann para calcular la integral f(x)
*
* Date: 2021-09-22
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define A 1
#define B 40
#define N 10000000

double f(double x);
double trapezoides(double a, double b, int n);

int main(int argc, char* argv[]) {
    double integral;
    double a = A, b = B;
    int n = N;

    if (argc > 1) {
        a = strtol(argv[1], NULL, 10);
        b = strtol(argv[2], NULL, 10);
        n = strtol(argv[3], NULL, 10);
    }

    integral = trapezoides(a, b, n);
    printf("Con n = %d trapezoides, nuestra aproximacion \n", n);
    printf("de la integral de %f a %f es = %.10f\n", a, b, integral);
    return 0;
}

double trapezoides(double a, double b, int n) {
    double integral = 0.0;
    int k;
    
    #pragma omp parallel
    {
        int n_local = n;
        double a_local = a;
        double b_local = b;
        int num_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        
        double h = (b_local - a_local) / n_local;
        double local_integral = (f(a_local) + f(b_local)) / 2.0;

        #pragma omp for reduction(+:integral)
        for (k = 1; k <= n_local - 1; k++) {
            local_integral += f(a_local + k * h);
        }
        
        local_integral *= h;
        integral += local_integral;

        printf("Thread ID: %d, Num Threads: %d\n", thread_id, num_threads);
    }

    return integral;
}

double f(double x) {
    return x * x;
}
