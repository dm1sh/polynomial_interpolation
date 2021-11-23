#ifndef POLYNOMIAL_INTERPOLATION_H
#define POLYNOMIAL_INTERPOLATION_H

#include <stdio.h>
#include <stdlib.h>

/*
 Utils
*/
double fabs(double x);

/*
 Business logic
*/

double div_diff(double *y, double *x, unsigned i, unsigned d);
double *div_diff_es(double *x, double *y, unsigned n);

/*
 User interface
*/

unsigned insert_n();
void print_newton_poly(double *f, double *x, unsigned n);
void insert_coords(double *x, double *y, unsigned n);
void print_array(double *arr, unsigned n);
void print_poly(double *coef, unsigned n);

/*
 Coeficients of simplified polynomial computation
*/

void simplify_polynomial(double *res, double *el_coef, double *x, unsigned n);
void mult_by_root(double *res, double root, unsigned step);

#endif