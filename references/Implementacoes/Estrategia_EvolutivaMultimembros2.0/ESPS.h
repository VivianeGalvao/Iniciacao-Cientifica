#ifndef ESPS_H_INCLUDED
#define ESPS_H_INCLUDED
#include"Solution.h"

bool Exploratory_Moves(double *pattern, double delta, Individual *sample, int size, int number_function, double *lb, double *ub);
double Normal_distribution(double mean, double desvio_padrao);
void Evolutionary_Strategy(int seed, double expected_mean, int dimension, int number_function, double delta, double *x);
void VerificadorSolucao(double *x, int dimension, int number_function);
void Selection(Individual **progenitor, Individual **progeny, int dimension);
void QuickSort(Individual **sample, int left, int right, int dimension);
void Partition(Individual **sample, int left, int right, int *i, int *j, int dimension);



#endif // ESPS_H_INCLUDED
