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

double div_diff(double *y, double *x, unsigned int i, unsigned int d);
double *div_diff_es(double *x, double *y, unsigned int n);

/*
 User interface
*/

unsigned int insert_n();
void print_newton_poly(double *f, double *x, unsigned int n);
void insert_coords(double *x, double *y, unsigned int n);
void print_array(double *arr, unsigned int n);
void print_poly(double *coef, unsigned int n);

/*
 Coeficients of simplified polynomial computation
*/

void simplify_polynomial(double *res, double *el_coef, double *x, unsigned int n);
void mult_by_root(double *res, double root, unsigned int step);

#endif