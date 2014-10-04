#ifndef GENERALPATTERNSEARCH_H_INCLUDED
#define GENERALPATTERNSEARCH_H_INCLUDED
#include "Avaliation_Function.h"

bool Exploratory_Moves(double *pattern, double delta, double *x_iteration, int size);
double GeneralPatternSearch(double delta_initial, double *x_best, double **Pattern_initial, int size_problem, double criterion_stop);


#endif // GENERALPATTERNSEARCH_H_INCLUDED
