#ifndef ES_PS3_H_INCLUDED
#define ES_PS3_H_INCLUDED
#include"Solution.h"

void Evolutionary_Strategy3(int seed, double expected_mean, int dimension, int number_function, double delta, double *x);
void Selection(Individual **progenitor, Individual **progeny, int dimension);
void QuickSort(Individual **sample, int left, int right, int dimension);
void Partition(Individual **sample, int left, int right, int *i, int *j, int dimension);

#endif // ES_PS3_H_INCLUDED
