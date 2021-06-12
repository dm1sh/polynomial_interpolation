#ifndef POLYNOMIAL_INTERPOLATION_H
#define POLYNOMIAL_INTERPOLATION_H

/*
 Utils
*/

int min(int a, int b);
int max(int a, int b);

/*
 Array utils
*/

typedef struct
{
    int size;
    float *p;
} arr;

arr *init(int n);
arr *resize(arr *a, int new_size);
void insert(arr *a, int pos, float val);
arr *add(arr *a, arr *b);
arr *mult(arr *a, float mul);
void printa(arr *a);
arr *arr_without_el(arr *a, int ex_pos);
arr *reverse(arr *a);

/*
 Business logic
*/

int has_comb(int *arr, int n, int k);
int mult_by_index(arr *a, int *coords, int n);
int sum_of_mult_of_n_combinations(arr *a, int n);
int compose_denominator(arr *a, int pos);
arr *compose_interpolation_polynomial(arr *xes, arr *ys);

#endif