#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

void printSolution(float *x)
{
    printf("Solução: x = [ ");
    for (int k = 0; k < N; k++)
    {
        if (k % N != 0)
            printf(", ");
        printf("%.2f", x[k]);
    }
    printf(" ].\n");
}

int main(void)
{
    double pi_value = M_PI;
    double alpha = sin(pi_value / 4);
    float A[][N] = {{-alpha, 0, 0, 1, alpha, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {-alpha, 0, -1, 0, -alpha, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, -1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, -1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, -alpha, -1, 0, 0, alpha, 1, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, alpha, 0, 1, 0, alpha, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, -1, -alpha, 0, 0, 1, alpha, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, -alpha, 0, -1, 0, -alpha, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 1, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, alpha, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -alpha, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -alpha, -1, 0, 0, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, alpha, 0, 1, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -alpha, -1}};
    float b[] = {0, 0, 0, 10, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 10, 0};
    float *x;

    x = gaussElimination(A, b, N);

    printSolution(x);

    return 0;
}
