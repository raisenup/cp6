#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "common.h"

#define MIN_S 2
#define MAX_S 10
#define MIN_E 1e-3
#define MAX_E 1e-15

#define RESET   "\x1b[0m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define CYAN    "\x1b[36m"

int main(void) {
    srand(time(NULL));

    printf("This application calculates SLAE.\n");
    do {
        ushort size = 0;
        do {
            printf("Input size of the array [%d, %d]: ", MIN_S, MAX_S);
            if(scanf("%hu", &size) != 1) {
                printf("Error: wrong input.\n");
            } else if (size < MIN_S || size > MAX_S) {
                printf("Error: size must be in [%d, %d].\n", MIN_S, MAX_S);
            }
            while (getchar() != '\n'){};
        } while (size < MIN_S || size > MAX_S);

        double epsilon = 0.0;
        do {
            printf("Input precision in exponential form [%.0e, %.0e]: ", MIN_E, MAX_E);
            if(scanf("%lf", &epsilon) != 1) {
                printf("Error: wrong input.\n");
            } else if (epsilon > MIN_E || epsilon < MAX_E) {
                printf("Error: precision must be between [%.0e, %.0e].\n", MIN_E, MAX_E);
            }
            while (getchar() != '\n'){};
        } while (epsilon > MIN_E || epsilon < MAX_E);

        double **a = init_matrix(size);
        double *b = init_array(size);
        double *x = init_array(size);
        double *xp = init_array(size);
        if(a != NULL && b != NULL && x != NULL && xp != NULL) {
            printf("To input SLAE manually press ENTER, to get random input press any other key.\n");
            if(getch() == 13) {
                input_slae(a, b, size);
            } else {
                randomize_slae(a, b, size);
            }

            printf(CYAN);
            print_init_slae(a, b, size);
            printf(RESET);

            if(!is_diagonally_dominant(a,size)) {
                printf("Error: SLAE has either infinite or no solutions (matrix is not diagonally dominant).");
            } else {
                solve_slae(a, b, x, xp, size, epsilon);

                const int precision = (int)-log10(epsilon);
                printf(YELLOW"| ");
                for (int i = 0; i < size; i++) {
                    printf("x%d = %.*lf | ", i+1, precision,  x[i]);
                }
                printf(RESET"\n");

                printf(GREEN);
                print_rslt_slae(a, b, x, size, precision);
                printf(RESET);
            }

            for (int i = 0; i < size; ++i) {
                free(a[i]);
            }
            free(a);
            free(b);
            free(x);
            free(xp);
        }

        printf("\nPress ENTER to restart, or any other key to exit.\n");
    } while (getch() == 13);

    return 0;
}
