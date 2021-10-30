#ifndef POLYNOMIAL_INTERPOLATION_H
#define POLYNOMIAL_INTERPOLATION_H

/*
 Business logic
*/

double div_diff(double *y, double *x, int i, int d);
double *div_diff_es(double *x, double *y, int n);
void print_newton_poly(double *f, double *x, int n);

#endif