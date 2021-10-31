#include "./polynominal_interpolation.h"

/* Utils */

double fabs(double x)
{
  return x > 0 ? x : -x;
}

/*
 Newton interpolation polynomial
*/

/* Divided difference is evaluated for:
   array y stands for f(x)
   array x stands for x
   number i stands for index of evaluated difference (from 0)
   number d stands for order of difference (from 0)
   example: https://shorturl.at/tBCPS */
double div_diff(double *y, double *x, unsigned int i, unsigned int d)
{
  return (y[i] - y[i - 1]) / (x[i] - x[i - d]);
}

/* Evaluates divided differences of n values - array of some kind of derivatives with big enough dx
   Example: https://shorturl.at/tBCPS
   Warning: result is evaluated in `double *y` array */
double *div_diff_es(double *x, double *y, unsigned int n)
{
  for (int i = 1; i < n; i++)        // first element remains unchanged
    for (int j = n - 1; j >= i; j--) // evaluate from the end of array, decreacing number of step every repeation
      y[j] = div_diff(y, x, j, i);

  return y;
}

/*
 Coeficients of simplified polynomial computation
*/

/* Simplifies Newton polynomial with `el_coef` array of divided differences,
   and `x` as array of x coordinates of dots,
   and `n` is number of elements of this sum */
void simplify_polynomial(double *res, double *el_coef, double *x, unsigned int n)
{
  double *tmp_polynomial // Temporary array for storage of coefficients of multiplication of (x-x_i) polynomial
      = (double *)malloc(sizeof(double) * n);
  tmp_polynomial[0] = 1; // Set polynomial to 1 to start multiplication with it

  for (int i = 0; i < n; i++) // For each elemnt of sum
  {
    if (i > 0) // Start multiplication from second element of sum
      mult_by_root(tmp_polynomial, x[i - 1], i - 1);

    for (int j = 0; j <= i; j++)                // For each cumputed coefficient of i'th polynomial of sum
      res[j] += el_coef[i] * tmp_polynomial[j]; // Add it, multiplied with divided difference, to sum
  }
}

/* `res` is an array of coefficients of polynomial which is multiplied with (x - `root`) polynomial
   `power` is the power of `res` polynomial */
void mult_by_root(double *res, double root, unsigned int power)
{
  for (int j = power + 1; j >= 0; j--)
    res[j] = (j ? res[j - 1] : 0) - (root * res[j]); // coefficient is k_i-1 - root * k_i
}

/*
 User Interface 
*/

/* Prints interpolation polynomial in Newton notation */
void print_newton_poly(double *f, double *x, unsigned int n)
{
  printf("Newton polynomial form:\n");
  for (int i = 0; i < n; i++)
  {
    if (f[i]) // If coefficient != 0
    {
      /* Coefficient sign and sum symbol */
      if (i > 0 && f[i - 1]) // If it's not the first summond
      {
        if (f[i] > 0)
          printf("+ ");
        else
          printf("- ");
      }
      else if (f[i] < 0) // If it is the first summond and coefficient is below zero
        printf("-");

      printf("%lf", fabs(f[i])); // Print coefficient without sign

      for (int j = 0; j < i; j++) // For each (x-xi) bracket
      {
        if (x[j]) // If summond is not zero, print it
        {
          if (x[j] > 0)
            printf("*(x-%lf)", x[j]);
          else
            printf("*(x+%lf)", -x[j]);
        }
        else
          printf("*x");
      }

      printf(" ");
    }
  }

  printf("\n");
}

unsigned int insert_n()
{
  printf("Insert number of dots: ");
  unsigned int n = 0;
  scanf("%u", &n);

  return n;
}

void insert_coords(double *xes, double *yes, unsigned int n)
{
  printf("Insert dots coordinates in the following format:\n<x> (space) <y>\nEach dot on new line\n");

  for (int i = 0; i < n; i++)
  {
    double x, y;
    scanf("%lf %lf", &x, &y);

    xes[i] = x;
    yes[i] = y;
  }
}

void print_array(double *arr, unsigned int n)
{
  printf("Simplified coefficients array (starting from 0 upto n-1 power):\n");

  for (int i = 0; i < n; i++)
    printf("%lf ", arr[i]);

  printf("\n");
}

void print_poly(double *coef, unsigned int n)
{
  printf("Simplified polynom:\n");

  for (int i = 0; i < n; i++)
  {
    if (coef[i])
    {
      if (i > 0 && coef[i - 1])
        if (coef[i] > 0)
          printf("+ ");
        else
          printf("- ");
      else
        printf("-");

      printf("%lf", fabs(coef[i]));
      if (i > 0)
        printf("*x");
      if (i > 1)
        printf("^%d ", i);
      else
        printf(" ");
    }
  }

  printf("\n");
}

/* 
 Main
*/

int main()
{
  unsigned n = insert_n();

  double *x = (double *)malloc(sizeof(double) * n),
         *y = (double *)malloc(sizeof(double) * n);

  insert_coords(x, y, n);

  double *f = div_diff_es(x, y, n);

  print_newton_poly(f, x, n);

  double *coefficients = (double *)malloc(sizeof(double) * n);

  simplify_polynomial(coefficients, f, x, n);

  print_array(coefficients, n);

  print_poly(coefficients, n);

  return 0;
}