#ifndef PATTERNSEARCH_H_INCLUDED
#define PATTERNSEARCH_H_INCLUDED
#include"Solution.h"

bool Exploratory_Moves(double *pattern, double delta, Individual *sample, int size, int number_function, double *lb, double *ub);
bool Exploratory_Moves(double *pattern, double delta, double *x_iteration, int size, int number_function, double *lb, double *ub);

#endif // PATTERNSEARCH_H_INCLUDED
