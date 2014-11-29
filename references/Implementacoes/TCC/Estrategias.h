#ifndef ESTRATEGIAS_H_INCLUDED
#define ESTRATEGIAS_H_INCLUDED
#include "Solution.h"

bool Exploratory_Moves(double *pattern, double delta, Individual *sample, int size, int number_function, double *lb, double *ub);
bool Exploratory_Moves(double *pattern, double delta, double *x_iteration, int size, int number_function, double *lb, double *ub);


double Normal_distribution(double mean, double desvio_padrao);

void Evolutionary_Strategy4(int seed, double expected_mean, int dimension, int number_function, double delta, double *x);
void Evolutionary_Strategy3(int seed, double expected_mean, int dimension, int number_function, double delta, double *x);
void Selection(Individual **progenitor, Individual **progeny, int dimension);
void QuickSort(Individual **sample, int left, int right, int dimension);
void Partition(Individual **sample, int left, int right, int *i, int *j, int dimension);

void Evolutionary_Strategy2(int seed, double expected_mean, int dimension, int number_function, double delta, double *x);
void Evolutionary_Strategy1(int seed, double expected_mean, int dimension, int number_function, double delta, double *x);


void PSwarm(int dimension, int seed, double delta_initial, int number_function, double* position_global);


bool VerificadorSolucao(double *x, int dimension, int number_function);




#endif // ESTRATEGIAS_H_INCLUDED
