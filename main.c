#include <stdio.h>
#include <stdlib.h>

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

typedef struct
{
    int size;
    float *p;
} arr;

arr *init(int n)
{
    arr *a = (arr *)malloc(sizeof(arr));

    a->size = n;

    a->p = (float *)malloc(sizeof(float) * n);
    for (int i = 0; i < n; i++)
        a->p[i] = 0;

    return a;
}

arr *resize(arr *a, int new_size)
{
    if (a->size == new_size)
        return a;

    float *new_p = (float *)malloc(sizeof(float) * new_size);
    for (int i = 0; i < min(new_size, a->size); i++)
        new_p[i] = a->p[i];

    free(a->p);

    for (int i = a->size; i < new_size; i++)
        new_p = 0;

    a->p = new_p;
    a->size = new_size;

    return a;
}

void insert(arr *a, int pos, float val)
{
    pos = pos % a->size;
    if (pos < 0)
        pos = a->size + pos;

    a->p[pos] = val;
}

arr *add(arr *a, arr *b)
{
    for (int i = 0; i < a->size; i++)
        a->p[i] = a->p[i] + b->p[i];

    return a;
}

arr *mult(arr *a, float mul)
{
    arr *res = init(a->size);

    for (int i = 0; i < a->size; i++)
        res->p[i] = a->p[i] * mul;

    return res;
}

void printa(arr *a)
{
    printf("Array of size %d:\n", a->size);

    for (int i = 0; i < a->size; i++)
        printf("%5d ", i + 1);
    printf("\n");

    for (int i = 0; i < a->size; i++)
        printf("%5.2f ", a->p[i]);
    printf("\n");
}

arr *arr_without_el(arr *a, int ex_pos)
{
    arr *res = init(a->size - 1);
    for (int i = 0, pos = 0; i < a->size; i++)
    {
        if (i == ex_pos)
            continue;
        res->p[pos] = a->p[i];
        pos++;
    }

    return res;
}

arr *reverse(arr *a)
{
    arr *res = init(a->size);
    for (int i = 0; i < a->size; i++)
        res->p[i] = a->p[a->size - 1 - i];

    return res;
}

/*
 Buisness logic
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
    float res = 1;
    for (int i = 0; i < n; i++)
        res = res * a->p[coords[i]];

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

    float acc = 0;

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
    float res = 1;
    for (int i = 0; i < a->size; i++)
    {
        if (i == pos)
            continue;

        res = res * (a->p[pos] - a->p[i]);
    }
    return res;
}

arr *compose_interpolation_polynomial(arr *xes, arr *ys)
{
    arr *res = init(xes->size);

    arr *jcoef = init(xes->size - 1);
    for (int j = 0; j < xes->size; j++)
    {
        int minus = !(xes->size % 2);
        float denominator = compose_denominator(xes, j);
        float multiplicator = ys->p[j];

        arr *xis = arr_without_el(xes, j);

        for (int i = 0; i < xes->size; i++)
        {
            float k_sum = sum_of_mult_of_n_combinations(xis, xes->size - 1 - i);
            jcoef->p[i] = (minus ? -1 : 1) * (multiplicator * k_sum) / denominator;
            minus = !minus;
        }

        res = add(res, jcoef);
    }

    free(jcoef);

    return res;
}

int main()
{
    printf("Insert number of dots: ");
    int n = 0;
    scanf("%d", &n);

    printf("Insert dots coordinates in the following format:\n<x> (space) <y>\nEach dot on new line\n");

    arr *xes = init(n);
    arr *ys = init(n);

    for (int i = 0; i < n; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);

        insert(xes, i, x);
        insert(ys, i, y);
    }

    printf("Inserted the following doths:\n");
    printa(xes);
    printa(ys);

    arr *res = compose_interpolation_polynomial(xes, ys);

    printf("Resulting polynomial will have such coeficients:\n");
    printa(reverse(res));

    return 0;
}