#include <stdio.h>
#include <stdlib.h>
#include <math.h>

FILE *arq;

double *retroSubstituicao(double **A, double *b, int n)
{
    double *x;
    x = (double *)malloc(n * sizeof(double));

    x[n - 1] = b[n - 1] / A[n - 1][n - 1];

    for (int i = n - 2; i >= 0; i--)
    {
        double soma = 0;
        for (int j = i + 1; j < n; j++)
            soma += A[i][j] * x[j];
        x[i] = (b[i] - soma) / A[i][i];
    }

    return x;
}

double *eliminacaoGauss(double **A, double *b, int n)
{
    double *x;
    x = (double *)malloc(n * sizeof(double));

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
                double temp = A[k][j];
                A[k][j] = A[r][j];
                A[r][j] = temp;
            }
            double temp = b[k];
            b[k] = b[r];
            b[r] = temp;
        }

        for (int i = k + 1; i < n; i++) /* Linhas abaixo da k-ésima */
        {
            double m = A[i][k] / A[k][k];
            for (int j = k; j < n; j++) /* Colunas */
                A[i][j] = A[i][j] - m * A[k][j];
            b[i] = b[i] - m * b[k];
        }
    }

    x = retroSubstituicao(A, b, n); /* Resolve o sistema */

    return x;
}

void imprimeSolucaoDireta(double *x, int N)
{
    printf("Solução direta por eliminação de Gauss com pivotamento parcial: x = [ ");
    for (int k = 0; k < N; k++)
        printf("%lf ", x[k]);
    printf("].\n");
}

// Método de Jacobi

double maximo(double *v, int N)
{
    double maximo = 0.0;
    for (int i = 0; i < N; i++)
    {
        double valor = fabs(v[i]);
        if (valor > maximo)
            maximo = valor;
    }

    return maximo;
}

double norma(double *anterior, double *atual, int N)
{
    double *vetor_diff;
    double norma_v = 0;
    vetor_diff = (double *)malloc(N * sizeof(double));

    for (int i = 0; i < N; i++)
        vetor_diff[i] = atual[i] - anterior[i];

    norma_v = maximo(vetor_diff, N) / maximo(atual, N);

    return norma_v;
}

double *metodo_de_jacobi(double **A, double *b, double *x_0, int k_max, double tol, int N)
{
    double *x;
    x = (double *)malloc(N * sizeof(double));

    int k = 1;

    while (k <= k_max)
    {
        for (int i = 0; i < N; i++)
        {
            double soma = 0.0;
            for (int j = 0; j < N; j++)
                if (j != i)
                    soma += A[i][j] * x_0[j];
            x[i] = (b[i] - soma) / A[i][i];
        }
        if (norma(x_0, x, N) < tol)
            return x;
        // printf("Tolerância: %lf\n", norma(x_0, x, N));
        k = k + 1;
        for (int i = 0; i < N; i++)
            x_0[i] = x[i];
    }
    printf("Número máximo de iterações excedido.\n");
    return x;
}

void imprimeSolucaoIterativa(double *x, int n)
{
    printf("Solução iterativa (Método de Jacobi): x = [ ");
    for (int i = 0; i < n; i++)
        printf("%f ", x[i]);
    printf("]\n");
}

//

double norma_diferenca(double *x, double *y, int n)
{
    double vet_diff[n];
    double valor_diff;

    for (int i = 0; i < n; i++)
        vet_diff[i] = x[i] - y[i];

    valor_diff = maximo(vet_diff, n);

    return valor_diff;
}

// Função principal

int main(void)
{
    int dim[] = {4, 6, 8, 10};
    double **A;
    double *b;
    double *x;
    double x_0[] = {0.0000000000, 0.0000000000, 0.0000000000, 0.0000000000};
    char coeficientes[10], coluna[10];
    // Solução esperada
    double *x_esp;

    // Resolvendo os Sistemas
    for (int p = 0; p < 4; p++)
    {
        printf("Resolvendo Matriz (A-%d)X = b-%d.", dim[p], dim[p]);
        // Dimensionando a matriz de coeficientes
        A = (double **)malloc(dim[p] * sizeof(double *));
        for (int i = 0; i < dim[p]; i++)
            A[i] = (double *)malloc(dim[p] * sizeof(double));

        // Dimensionando o vetor b
        b = (double *)malloc(dim[p] * sizeof(double));

        // Dimensionando o vetor com a solução esperada
        x_esp = (double *)malloc(dim[p] * sizeof(double));

        // Preenchendo o vetor x_esp com a solução esperada
        for (int k = 0; k < dim[p]; k++)
            x_esp[p] = 199.0;

        sprintf(coeficientes, "A-%d.dat", dim[p]);
        sprintf(coluna, "b-%d.dat", dim[p]);

        arq = fopen(coeficientes, "r");

        // Preenchendo a matriz de coeficientes A
        for (int i = 0; i < dim[p]; i++)
        {
            for (int j = 0; j < dim[p]; j++)
            {
                fscanf(arq, "%lf ", &A[i][j]);
            }
        }

        fclose(arq);

        arq = fopen(coluna, "r");

        // Prenchendo o vetor b
        for (int i = 0; i < dim[p]; i++)
        {
            fscanf(arq, "%lf", &b[i]);
        }

        fclose(arq);

        printf("\n");

        x = eliminacaoGauss(A, b, dim[p]);

        imprimeSolucaoDireta(x, dim[p]);
        printf("Diferença em norma infinito da solução direta obtida com a solução esperada: %lf.\n", norma_diferenca(x, x_esp, dim[p]));

        x = metodo_de_jacobi(A, b, x_0, 1000, 0.001, dim[p]);

        imprimeSolucaoIterativa(x, dim[p]);
        printf("Diferença em norma infinito da solução iterativa obtida com a solução esperada: %lf.\n", norma_diferenca(x, x_esp, dim[p]));

        printf("\n");

        for (int e = 0; e < dim[p]; e++)
            free(A[e]);
        free(A);
        free(b);
        free(x);
        free(x_esp);
    }

    return 0;
}
