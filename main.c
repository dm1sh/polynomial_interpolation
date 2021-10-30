#include "./polynominal_interpolation.h"

/* Divided difference is evaluated for:
   array y stands for f(x)
   array x stands for x
   number i stands for index of evaluated difference (from 0)
   number d stands for order of difference (from 0)
   example: https://shorturl.at/tBCPS */
double div_diff(double *y, double *x, int i, int d)
{
  return (y[i] - y[i - 1]) / (x[i] - x[i - d]);
}

/* Evaluates divided differences of n values - array of some kind of derivatives with big enough dx
   Example: https://shorturl.at/tBCPS
   Warning: result is evaluated in `double *y` array */
double *div_diff_es(double *x, double *y, int n)
{
  for (int i = 1; i < n; i++)        // first element remains unchanged
    for (int j = n - 1; j >= i; j--) // evaluate from the end of array, decreacing number of step every repeation
      y[j] = div_diff(y, x, j, i);

  return y;
}

/* Prints interpolation polynomial in Newton notation */
void print_newton_poly(double *f, double *x, int n)
{
  for (int i = 0; i < n; i++)
  {
    printf("(%lf)", f[i]);
    for (int j = 0; j < i; j++)
      printf("*(x-(%lf))", x[j]);

    if (i != n - 1)
      printf("+");
  }
}

int main()
{
  double x[] = {0, 1, 2, 3},
         y[] = {-2, -5, 0, -4};

  print_newton_poly(div_diff_es(x, y, 4), x, 4);
}