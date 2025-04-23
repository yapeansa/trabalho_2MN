#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 17

int min(int a, int b)
{
    if (a >= b)
        return a;
    else
        return b;
}

float *retroSubstitution(float (*A)[N], float *b, int n)
{
    float *x;
    x = (float *)malloc(n * sizeof(float));

    x[n - 1] = b[n - 1] / A[n - 1][n - 1];

    for (int i = n - 2; i >= 0; i--)
    {
        float soma = 0;
        for (int j = i + 1; j < n; j++)
            soma += A[i][j] * x[j];
        x[i] = (b[i] - soma) / A[i][i];
    }

    return x;
}

// Para a adaptação do método, consideramos a banda superior q = 4
// e a banda inferior como p = 3
float *gaussElimination(float (*A)[N], float *b, int n)
{
    float *x;
    x = (float *)malloc(n * sizeof(float));

    for (int k = 0; k <= n - 2; k++) /* Para cada passo */
    {
        /* Procurando por r tal que |a_{rk}| = max_{i \in [k, n]} |a_{ik}| */
        int r = k;
        for (int i = k + 1; i < min(n, k + 3); i++)
        {
            if (fabs(A[i][k]) > fabs(A[r][k]))
                r = i;
        }

        /* Troca as linhas k e r, se necessário */
        if (r != k)
        {
            for (int j = 0; j < min(n, k + 4); j++)
            {
                float temp = A[k][j];
                A[k][j] = A[r][j];
                A[r][j] = temp;
            }
            float temp = b[k];
            b[k] = b[r];
            b[r] = temp;
        }

        for (int i = k + 1; i < min(n, k + 3); i++) /* Linhas abaixo da k-ésima */
        {
            float m = A[i][k] / A[k][k];
            for (int j = k; j < n; j++) /* Colunas */
                A[i][j] = A[i][j] - m * A[k][j];
            b[i] = b[i] - m * b[k];
        }
    }

    x = retroSubstitution(A, b, n); /* Resolve o sistema */

    return x;
}

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
