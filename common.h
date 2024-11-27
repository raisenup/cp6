#pragma once
#include <stdbool.h>

typedef unsigned short ushort;

double **init_matrix(const ushort size);

double *init_array(const ushort size);

bool is_diagonally_dominant(double **a, const int size);

void input_slae(double **a, double *b, const ushort size);

void randomize_slae(double **a, double *b, const ushort size);

void solve_slae(double **a, const double *b, double *x, double *xp, const ushort size, const double epsilon);

void print_init_slae(double **a, const double *b, const ushort size);

void print_rslt_slae(double **a, const double *b, const double *x, const ushort size, const int precision);
