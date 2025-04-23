#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 4

float *retroSubstituicao(float (*A)[N], float *b, int n)
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

float *eliminacaoGauss(float (*A)[N], float *b, int n)
{
    float *x;
    x = (float *)malloc(n * sizeof(float));

    for (int k = 0; k <= n - 2; k++) /* Para cada passo */
    {
        /* Procurando por r tal que |a_{rk}| = max_{i \in [k, n]} |a_{ik}| */
        int r = k;
        for (int i = k + 1; i < n; i++)
        {
            if (fabs(A[i][k]) > fabs(A[r][k]))
                r = i;
        }

        /* Troca as linhas k e r, se necessário */
        if (r != k)
        {
            for (int j = 0; j < n; j++)
            {
                float temp = A[k][j];
                A[k][j] = A[r][j];
                A[r][j] = temp;
            }
            float temp = b[k];
            b[k] = b[r];
            b[r] = temp;
        }

        for (int i = k + 1; i < n; i++) /* Linhas abaixo da k-ésima */
        {
            float m = A[i][k] / A[k][k];
            for (int j = k; j < n; j++) /* Colunas */
                A[i][j] = A[i][j] - m * A[k][j];
            b[i] = b[i] - m * b[k];
        }
    }

    x = retroSubstituicao(A, b, n); /* Resolve o sistema */

    return x;
}

void imprimeSolucao(float *x)
{
    printf("Posições: ");
    for (int k = 0; k < N; k++)
    {
        if (k % N != 0)
            printf(", ");
        printf("x[%d] = %f", k + 1, x[k]);
    }
    printf("\n");
}

int main(void)
{
    float A[][N] = {{-200.0, 50.0, 0.0, 0.0},
                    {50.0, -125.0, 75.0, 0.0},
                    {0.0, 75.0, -300.0, 225.0},
                    {0.0, 0.0, -225.0, 225.0}};
    float b[] = {0, 0, 0, 2000.0};
    float *x;

    x = eliminacaoGauss(A, b, N);

    imprimeSolucao(x);

    return 0;
}
