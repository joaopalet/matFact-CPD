// Serial Implementation - Group 5

#include <stdio.h>
#include <stdlib.h>

#define RAND01 ((double) random() / (double) RAND_MAX)



// Global Variables

int iter, nF, nU, nI, nnonzero;
int **A;
double **L, **R, **RT, **B;
double alpha;



// Auxiliary Functions

void print_matrix_int(int **M, int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++)
            printf("%d ", M[i][j]);
        printf("\n");
    }

    printf("\n");
}



void print_matrix_double(double **M, int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++)
            printf("%f ", M[i][j]);
        printf("\n");
    }

    printf("\n");
}



int **create_matrix_int(int r, int c) {
    int **M = (int **)malloc(r * sizeof(int *)); 

    for (int i= 0; i < r; i++) 
         M[i] = (int *) calloc(c, sizeof(int));

    return M;
}



double **create_matrix_double(int r, int c) {
    double **M = (double **)malloc(r * sizeof(double *)); 

    for (int i= 0; i < r; i++) 
         M[i] = (double *) calloc(c, sizeof(double));

    return M;
}



void random_fill_LR() {
    srandom(0);

    for (int i = 0; i < nU; i++)
        for (int j = 0; j < nF; j++)
            L[i][j] = RAND01 / (double) nF;

    for (int i = 0; i < nF; i++)
        for (int j = 0; j < nI; j++)
            R[i][j] = RAND01 / (double) nF;
}



double **transpose_matrix(double **M, int n, int m) {
    double **MT = create_matrix_double(m, n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            MT[j][i] = M[i][j];

    return MT;
}



void matrix_mult(double **X, double **Y, double **Z, int n, int m, int p) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            Z[i][j] = 0;
            for (int k = 0; k < p; k++)
                Z[i][j] += X[i][k] * Y[j][k]; 
        }
    }
}



// Main

int main() {
    scanf("%d", &iter);
    scanf("%lf", &alpha);
    scanf("%d", &nF);
    scanf("%d", &nU);
    scanf("%d", &nI);
    scanf("%d", &nnonzero);

    A = create_matrix_int(nU, nI);
    B = create_matrix_double(nU, nI);
    L = create_matrix_double(nU, nF);
    R = create_matrix_double(nF, nI);
    random_fill_LR();
    RT = transpose_matrix(R, nF, nI);

    for (int i = 0; i < nnonzero; i++) {
        int n, m;
        double v;

        scanf("%d", &n);
        scanf("%d", &m);
        scanf("%lf", &v);

        A[n][m] = v;
    }

    matrix_mult(L, RT, B, nU, nI, nF);

    print_matrix_int(A, nU, nI);
    print_matrix_double(L, nU, nF);
    print_matrix_double(R, nF, nI);
    print_matrix_double(RT, nI, nF);
    print_matrix_double(B, nU, nI);

    return 0;
}