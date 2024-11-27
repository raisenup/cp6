#include "common.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define BR ">>------===#===------===#===------===#===------===#===------<<\n"

double **init_matrix(const ushort size) {
    double **array = malloc(size * sizeof(double*));
    for (int i = 0; i < size; i++) {
        array[i] = malloc(size * sizeof(double));
        if (array[i] == NULL) {
            printf("Error allocating memory.\n");
            return NULL;
        }
    }
    return array;
}

double *init_array(const ushort size) {
    double *array = malloc(size * sizeof(double*));
    if (array == NULL) {
        printf("Error allocating memory.\n");
        return NULL;
    }
    return array;
}

bool is_diagonally_dominant(double **a, const int size) {
    for (int i = 0; i < size; i++) {
        double sum = 0.0;
        for (int j = 0; j < size; j++) {
            if (i != j) {
                sum += fabs(a[i][j]);
            }
        }
        if (fabs(a[i][i]) <= sum) {
            return false;
        }
    }
    return true;
}

void input_slae(double **a, double *b, const ushort size) {
    printf("WARNING: Matrix of a elements should be diagonally dominant,\nif not the simple iteration method might produce errors.\n");
    printf("Input SLAE elements :\n");
    double tmp_a = 0.0, tmp_b = 0.0;
    ushort input_a = 0, input_b = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            do {
                printf("a%d%d = ", i+1, j+1);
                input_a = scanf("%lf", &tmp_a);
                if(input_a != 1) {
                    printf("Error: wrong input.\n");
                }
                while (getchar() != '\n'){};
            } while (input_a != 1);
            a[i][j] = tmp_a;
        }
        do {
            printf("b%d = ", i+1);
            input_b = scanf("%lf", &tmp_b);
            if(input_b != 1) {
                printf("Error: wrong input.\n");
            }
            while (getchar() != '\n'){};
        } while (input_b != 1);
        b[i] = tmp_b;
    }
}

void randomize_slae(double **a, double *b, const ushort size) {
    for (ushort i = 0; i < size; i++) {
        double row_sum = 0.0;
        for (ushort j = 0; j < size; j++) {
            if (i != j) {
                a[i][j] = (rand() % 200 - 100) / 10.0;
                row_sum += fabs(a[i][j]);
            }
        }
        a[i][i] = row_sum + (rand() % 50) / 10.0 + 1.0;
        b[i] = (rand() % 200 - 100) / 10.0;
    }
}

void solve_slae(double **a, const double *b, double *x, double *xp, const ushort size, const double epsilon) {
    int iter = 0;
    double max_delta;
    do {
        iter++;

        for(int i = 0; i < size; i++){
            xp[i] = 0.0;
            for(int j = 0; j < size; j++){
                if(i != j){
                    xp[i] = xp[i] + (a[i][j] * x[j]);
                }
            }
            xp[i] = (b[i] - xp[i]) / a[i][i];
        }

        max_delta = 0;

        for(int i = 0; i < size; i++){
            if(fabs(x[i] - xp[i]) > max_delta){
                max_delta = fabs(x[i] - xp[i]);
            }
            x[i] = xp[i];
        }
    } while (max_delta > epsilon);
    printf("Iterations: %d\n", iter);
}

void print_init_slae(double **a, const double *b, const ushort size) {
    printf("Initial SLAE:\n");
    printf(BR);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if(j == 0) {
                printf(" %.1lf*x%d", a[i][j], j+1);
            } else {
                printf(" %+.1lf*x%d", a[i][j], j+1);
            }
        }
        printf(" = %.1lf\n", b[i]);
    }
    printf(BR);
}

void print_rslt_slae(double **a, const double *b, const double *x, const ushort size, const int precision) {
    printf("Result SLAE:\n");
    printf(BR);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if(j == 0) {
                printf(" %.1lf*%.*lf", a[i][j], precision, x[j]);
            } else {
                printf(" %+.1lf*%.*lf", a[i][j],precision, x[j]);
            }
        }
        printf(" = %.1lf\n", b[i]);
    }
    printf(BR);
}
