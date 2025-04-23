#ifndef MATRIX_H
#define MATRIX_H
#define N 17

float *retroSubstitution(float (*A)[N], float *b, int n);
float *gaussElimination(float (*A)[N], float *b, int n);

#endif
