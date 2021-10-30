#ifndef POLYNOMIAL_INTERPOLATION_H
#define POLYNOMIAL_INTERPOLATION_H

#include <stdio.h>
#include <stdlib.h>

/*
 Business logic
*/

double div_diff(double *y, double *x, int i, int d);
double *div_diff_es(double *x, double *y, int n);

/*
 User interface
*/

unsigned int insert_n();
void print_newton_poly(double *f, double *x, int n);
void insert_coords(double *x, double *y, unsigned int n);

#endif