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
    double integral, h;
    int k;

    h = (b - a) / n;
    integral = (f(a) + f(b)) / 2.0;

    #pragma omp parallel for reduction(+:integral)
    for (k = 1; k <= n - 1; k++) {
        integral += f(a + k * h);
    }
    
    integral = integral * h;
    return integral;
}

double f(double x) {
    return x * x;
}


/*
COMENTARIO EN PAREJA DEL FUNCIONAMIENTO:

- Se trata acerca del algoritmo de Riemann pero a base de trapezoides
- Se define la función f(x) que representa la función a integrar. En este caso, es f(x) = x*x.
- El programa define los valores de A y B que representan los extremos del intervalo en el que 
se desea calcular la integral, y N que representa la cantidad de trapezoides utilizados en la aproximación.
- En la función trapezoides(a, b, n), se calcula el ancho de cada trapezoide (h) y se inicia la aproximación
de la integral con el valor promedio de f(a) y f(b) (extremos del intervalo).
- Luego, se realiza un bucle para calcular la suma de f(x) en los puntos interiores del intervalo utilizando 
la fórmula del método de los trapezoides.
- Finalmente, se multiplica la suma acumulada por el ancho de los trapezoides (h) para obtener la aproximación de la integral.

*/