#include "./polynominal_interpolation.h"

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

void simplify_polynomial(double *res, double *rev_el_coef, double *x, unsigned int n)
{
  for (int i = 0; i < n; i++)
    if (rev_el_coef[i])
      for (int j = 0; j <= i; j++)
        res[i - j] += (j % 2 ? -1 : 1) * rev_el_coef[i] * compute_sum_of_multiplications_of_k(x, j, i);
}

double compute_sum_of_multiplications_of_k(double *arr, unsigned int k, unsigned int n)
{
  if (k == 0)
    return 1;

  if (k == 1 && n == 1)
    return arr[0];

  unsigned int *selected = (unsigned int *)malloc(sizeof(unsigned int) * k); // Indexes of selected for multiplication elements

  int i = 0, // index of `arr` array
      j = 0; // index of `selected` array

  double sum = 0;

  while (j >= 0)
  {
    if (i <= (n + (j - k)))
    {
      selected[j] = i;

      if (j == k - 1)
      {
        sum += mult_by_indexes(arr, selected, k);
        i++;
      }
      else
      {
        i = selected[j] + 1;
        j++;
      }
    }
    else
    {
      j--;
      if (j >= 0)
        i = selected[j] + 1;
    }
  }

  free(selected);

  return sum;
}

double mult_by_indexes(double *arr, unsigned int *indexes, unsigned int size)
{
  double res = 1;
  for (int i = 0; i < size; i++)
    res *= arr[indexes[i]];

  return res;
}

/*
 User Interface 
*/

/* Prints interpolation polynomial in Newton notation */
void print_newton_poly(double *f, double *x, unsigned int n)
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
  for (int i = 0; i < n; i++)
    printf("%lf ", arr[i]);

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

  double *coeficients = (double *)malloc(sizeof(double) * n);

  simplify_polynomial(coeficients, f, x, n);

  print_array(coeficients, n);

  return 0;
}