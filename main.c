#include <stdio.h>
#include <stdlib.h>

#include "./polynominal_interpolation.h"

/*
 Utils
*/

int min(int a, int b)
{
    return (a + b - abs(a - b)) / 2;
}

int max(int a, int b)
{
    return (a + b + abs(a - b)) / 2;
}

/*
 Array utils
*/

arr *init(int n)
{
    arr *a = (arr *)malloc(sizeof(arr));

    a->size = n;

    a->p = (double *)malloc(sizeof(double) * n);
    for (int i = 0; i < n; i++)
        set(a, i, 0);

    return a;
}

arr *resize(arr *a, int new_size)
{
    if (a->size == new_size)
        return a;

    double *new_p = (double *)malloc(sizeof(double) * new_size);
    for (int i = 0; i < min(new_size, a->size); i++)
        new_p[i] = get(a, i);

    free(a->p);

    for (int i = a->size; i < new_size; i++)
        new_p = 0;

    a->p = new_p;
    a->size = new_size;

    return a;
}

int convert_addr(arr *a, int pos)
{
    pos = pos % a->size;
    if (pos < 0)
        pos = a->size + pos;

    return pos;
}

double get(arr *a, int pos)
{
    pos = convert_addr(a, pos);

    return a->p[pos];
}

void set(arr *a, int pos, double val)
{
    pos = convert_addr(a, pos);

    a->p[pos] = val;

    // printa(a, 1);
}

arr *add(arr *a, arr *b)
{
    for (int i = 0; i < a->size; i++)
        set(a, i, a->p[i] + b->p[i]);

    return a;
}

arr *mult(arr *a, double mul)
{
    arr *res = init(a->size);

    for (int i = 0; i < a->size; i++)
        set(res, i, a->p[i] * mul);

    return res;
}

void printa(arr *a, int q)
{
    if (q)
    {
        for (int i = 0; i < a->size; i++)
            printf("%f ", get(a, i));
        printf("\n");

        return;
    }

    printf("Array of size %d:\n", a->size);

    for (int i = 0; i < a->size; i++)
        printf("%5d ", i + 1);
    printf("\n");

    for (int i = 0; i < a->size; i++)
        printf("%5.2f ", get(a, i));
    printf("\n");
}

arr *arr_without_el(arr *a, int ex_pos)
{
    arr *res = init(a->size - 1);
    for (int i = 0, pos = 0; i < a->size; i++)
    {
        if (i == ex_pos)
            continue;
        set(res, pos, a->p[i]);
        pos++;
    }

    return res;
}

arr *reverse(arr *a)
{
    arr *res = init(a->size);
    for (int i = 0; i < a->size; i++)
        set(res, i, a->p[a->size - 1 - i]);

    return res;
}

void free_arr(arr *a)
{
    free(a->p);
    free(a);
}

/*
 Business logic
*/

int has_comb(int *arr, int n, int k)
{
    if (n == k)
        return 0;

    int pos = k - 1;

    if (arr[pos] == n - 1)
    {
        if (k == 1)
            return 0;

        while ((pos > 0) && arr[pos] == n - 1)
        {
            pos--;
            arr[pos]++;
        }

        for (int i = pos + 1; i < k; i++)
            arr[i] = arr[i - 1] + 1;

        if (arr[0] > n - k)
            return 0;
    }
    else
        arr[pos]++;

    return 1;
}

int mult_by_index(arr *a, int *coords, int n)
{
    double res = 1;
    for (int i = 0; i < n; i++)
        res = res * get(a, coords[i]);

    return res;
}

int sum_of_mult_of_n_combinations(arr *a, int n)
{
    if (n == 0)
        return 1;

    if (a->size == 1)
    {
        return a->p[0];
    }

    double acc = 0;

    int coords[n];
    for (int i = 0; i < n; i++)
        coords[i] = i;

    acc += mult_by_index(a, coords, n);
    while (has_comb(coords, a->size, n))
        acc += mult_by_index(a, coords, n);

    return acc;
}

int compose_denominator(arr *a, int pos)
{
    double res = 1;
    for (int i = 0; i < a->size; i++)
    {
        if (i == pos)
            continue;

        res = res * (get(a, pos) - get(a, i));
    }
    return res;
}

arr *compose_interpolation_polynomial(arr *xes, arr *ys)
{
    arr *res = init(xes->size);

    arr *jcoef = init(xes->size);
    for (int j = 0; j < xes->size; j++)
    {
        int minus = (!(xes->size % 2) ? -1 : 1);
        double denominator = compose_denominator(xes, j);
        double multiplicator = get(ys, j);

        arr *xis = arr_without_el(xes, j);

        for (int i = 0; i < xes->size; i++)
        {
            double k_sum = sum_of_mult_of_n_combinations(xis, xes->size - 1 - i);
            set(jcoef, i, minus * (multiplicator * k_sum) / denominator);
            minus = -minus;
        }

        res = add(res, jcoef);

        free_arr(xis);
    }

    free_arr(jcoef);

    return res;
}

int main(int argc, char *argv[])
{
    int quiet_mode = 0;
    if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'q')
        quiet_mode = 1;

    if (!quiet_mode)
        printf("Insert number of dots: ");
    int n = 6;
    scanf("%d", &n);

    if (!quiet_mode)
        printf("Insert dots coordinates in the following format:\n<x> (space) <y>\nEach dot on new line\n");

    arr *xes = init(n);
    arr *ys = init(n);

    // set(xes, 0, 1);
    // set(ys, 0, 1);
    // set(xes, 1, 2);
    // set(ys, 1, 2);
    // set(xes, 2, 3);
    // set(ys, 2, 3);
    // set(xes, 3, 4);
    // set(ys, 3, 4);
    // set(xes, 4, 5);
    // set(ys, 4, 5);
    // set(xes, 5, 6);
    // set(ys, 5, 6);

    for (int i = 0; i < n; i++)
    {
        double x, y;
        scanf("%lf %lf", &x, &y);

        set(xes, i, x);
        set(ys, i, y);
    }

    if (!quiet_mode)
    {
        printf("Inserted the following doths:\n");
        printa(xes, 0);
        printa(ys, 0);
    }

    arr *res = compose_interpolation_polynomial(xes, ys);

    if (!quiet_mode)
        printf("Resulting polynomial will have such coeficients:\n");
    arr *reversed = reverse(res);
    printa(reversed, quiet_mode);

    free_arr(reversed);
    free_arr(res);
    free_arr(xes);
    free_arr(ys);

    return 0;
}